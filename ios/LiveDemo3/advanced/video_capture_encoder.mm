//
//  video_capture_external_demo.h
//  ve_demo
//
//  Created by robotding on 16/5/30.
//  Copyright © 2016年 jjams. All rights reserved.
//

#include "video_capture_encoder.h"
#include <CoreMedia/CMFormatDescriptionBridge.h>
#include "big_endian.h"

namespace demo {

template <typename NalSizeType>
void CopyNalsToAnnexB(char* avcc_buffer,
                      const size_t avcc_size,
                      std::string* annexb_buffer) {
    static_assert(sizeof(NalSizeType) == 1 || sizeof(NalSizeType) == 2 ||
                  sizeof(NalSizeType) == 4,
                  "NAL size type has unsupported size");
    static const char startcode_4[4] = {0, 0, 0, 1};
    //ASSERT_D(avcc_buffer);
    //ASSERT_D(annexb_buffer);
    size_t bytes_left = avcc_size;
    size_t current_size = annexb_buffer->size();
    uint8_t* offset = (uint8_t*)annexb_buffer->data() + current_size;
    
    while (bytes_left > 0) {
        NalSizeType nal_size;
        base::ReadBigEndian(avcc_buffer, &nal_size);
        bytes_left -= sizeof(NalSizeType);
        avcc_buffer += sizeof(NalSizeType);
        
        annexb_buffer->append(startcode_4, sizeof(startcode_4));
        annexb_buffer->append(avcc_buffer, nal_size);
        bytes_left -= nal_size;
        avcc_buffer += nal_size;
        
        offset += nal_size + sizeof(startcode_4);
    }
}

static int g_error_log_count = 0;
static int g_stuck_log_count = 0;

// Container for the associated data of a video frame being processed.
struct InProgressFrameEncode {
    double reference_time;
    
    InProgressFrameEncode(int64_t rt) : reference_time(rt) {
    }
    
    ~InProgressFrameEncode() {
    }
};

VideoEncoder::VideoEncoder(AVE::VideoCaptureEncodedFrameCallback* callback) :
    callback_(callback), m_oEncSession(NULL), frame_id_(0),
    bitrate_(400 * 1000), framerate_(15), width_(0), height_(0),
    b_annexb_(false) {
}

VideoEncoder::~VideoEncoder() {
    EmitFrames();
    DestroyCompressionSession();
}
 
int32_t VideoEncoder::Encode(CVPixelBufferRef pixel_buffer, double timestamp_ms, bool is_keyframe_required) {
    if (g_stuck_log_count > 0) {
        g_stuck_log_count = 0;
    }
    
    int width = (int)CVPixelBufferGetWidth(pixel_buffer);
    int height = (int)CVPixelBufferGetHeight(pixel_buffer);
    if (width_ != width || height_ != height) {
        width_ = width;
        height_ = height;
        color_format_ = kCVPixelFormatType_32BGRA;
        ResetCompressionSession();
        
        codec_config_.width = width;
        codec_config_.height = height;
        codec_config_.codec_type = b_annexb_ ? AVE::CODEC_TYPE_AVC_ANNEXB : AVE::CODEC_TYPE_AVC_AVCC;
    }
    
    if (!m_oEncSession) {
        return -1;
    }
    
    CMTime timestamp_cm = CMTimeMake(encoder_counter_, framerate_);
    InProgressFrameEncode* request = new InProgressFrameEncode(timestamp_ms);
    
    VTEncodeInfoFlags info;
    
    // 开始压缩编码，异步调用 CompressionCallback
    OSStatus status = VTCompressionSessionEncodeFrame(m_oEncSession, pixel_buffer, timestamp_cm,
                                                      kCMTimeInvalid, NULL,
                                                      reinterpret_cast<void*>(request), &info);
    
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTCompressionSessionEncodeFrame failed:%d\n", status);
        DestroyCompressionSession();
        return -1;
    }
    
    if (info & kVTEncodeInfo_FrameDropped) {
        //CLog::RT("[INFO] venc -- frame dropped \n");
    } else {
        encoder_counter_++;
    }
    
    return 0;
}

int VideoEncoder::ResetCompressionSession() {
    // If there is an existing session, finish every pending frame.
    if (m_oEncSession) {
        EmitFrames();
        DestroyCompressionSession();
    }
    
    // 初始化 VTCompressionSession，当 VTCompressionSession 被调用压缩一次后会异步调用 CompressionCallback
    VTCompressionSessionRef session;
    OSStatus status = VTCompressionSessionCreate(kCFAllocatorDefault,
                                                 width_,
                                                 height_,
                                                 kCMVideoCodecType_H264,
                                                 NULL,
                                                 NULL,
                                                 kCFAllocatorDefault,
                                                 &VideoEncoder::CompressionCallback,
                                                 reinterpret_cast<void*>(this),
                                                 &session);

    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTCompressionSessionCreate failed:%d\n", status);
        return -1;
    }
    
    m_oEncSession = session;
    
    ConfigureCompressionSession();
    SetConfig(bitrate_, framerate_);
    status = VTCompressionSessionPrepareToEncodeFrames(m_oEncSession);
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTCompressionSessionPrepareToEncodeFrames failed:%d\n", status);
        return -1;
    }
    EmitFrames();
    
    encoder_counter_ = 0;
    
    return 0;
}

int32_t VideoEncoder::SetConfig(int bitrate, int framerate) {
    bitrate_ = bitrate;
    framerate_ = framerate;
    
    if (!m_oEncSession) {
        return 0;
    }
    
    //CLog::RT("[DEBUG] venc -- SetConfig\n");
    
    SetSessionProperty(kVTCompressionPropertyKey_ExpectedFrameRate, framerate);
    SetSessionProperty(kVTCompressionPropertyKey_MaxKeyFrameInterval, framerate*2);
    SetSessionProperty(kVTCompressionPropertyKey_AverageBitRate, bitrate_); // bps

    return 0;
}

void VideoEncoder::ConfigureCompressionSession() {
    const size_t properties_size = 4;
    CFTypeRef keys[properties_size] = {
        kVTCompressionPropertyKey_ProfileLevel,
        kVTCompressionPropertyKey_RealTime,
        kVTCompressionPropertyKey_AllowFrameReordering,
        kVTCompressionPropertyKey_H264EntropyMode,
    };
    
    CFTypeRef values[properties_size] = {
        kVTProfileLevel_H264_Baseline_AutoLevel,
        kCFBooleanTrue,
        kCFBooleanFalse,
        kVTH264EntropyMode_CAVLC,
    };
    CFDictionaryRef properties = ::CFDictionaryCreate(kCFAllocatorDefault, keys, values, properties_size, nil, nil);
    
    OSStatus status = VTSessionSetProperties(m_oEncSession, properties);
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- ConfigureCompressionSession failed:%d\n", status);
        if (kVTVideoEncoderMalfunctionErr == status) {
            DestroyCompressionSession();
        }
    }
    
    CFRelease(properties);
}

bool VideoEncoder::SetSessionProperty(CFStringRef key, int32_t value) {
    CFNumberRef cfvalue = CFNumberCreate(nullptr, kCFNumberSInt32Type, &value);
    OSStatus status = VTSessionSetProperty(m_oEncSession, key,cfvalue);
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTSessionSetProperty failed:%d\n", status);
        if (kVTVideoEncoderMalfunctionErr == status) {
            DestroyCompressionSession();
        }
    }
    
    CFRelease(cfvalue);
    
    return status == noErr;
}

bool VideoEncoder::SetSessionProperty(CFStringRef key, bool value) {
    CFBooleanRef cfvalue = (value) ? kCFBooleanTrue : kCFBooleanFalse;
    OSStatus status = VTSessionSetProperty(m_oEncSession, key, cfvalue);
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTSessionSetProperty failed:%d\n", status);
        if (kVTVideoEncoderMalfunctionErr == status) {
            DestroyCompressionSession();
        }
    }
    
    return status == noErr;
}

bool VideoEncoder::SetSessionProperty(CFStringRef key, CFStringRef value) {
    OSStatus status = VTSessionSetProperty(m_oEncSession, key, value);
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTSessionSetProperty failed:%d\n", status);
        if (kVTVideoEncoderMalfunctionErr == status) {
            DestroyCompressionSession();
        }
    }
    
    return status == noErr;
}

void VideoEncoder::EmitFrames() {
    if (!m_oEncSession) return;
    
    OSStatus status = VTCompressionSessionCompleteFrames(m_oEncSession, CMTime{0, 0, 0, 0});
    if (status != noErr) {
        //CLog::RT("[ERROR] venc -- VTCompressionSessionCompleteFrames failed:%d\n", status);
    }
}

void VideoEncoder::DestroyCompressionSession() {
    // If the compression session exists, invalidate it. This blocks until all
    // pending output callbacks have returned and any internal threads have
    // joined, ensuring no output callback ever sees a dangling encoder pointer.
    
    if (m_oEncSession) {
        VTCompressionSessionInvalidate(m_oEncSession);
        CFRelease(m_oEncSession);
        m_oEncSession = NULL;
    }
}
    
void VideoEncoder::DoCallback(CMSampleBufferRef sbuf, double timestamp_ms) {
    CFDictionaryRef sample_attachments = static_cast<CFDictionaryRef>(CFArrayGetValueAtIndex(CMSampleBufferGetSampleAttachmentsArray(sbuf, true), 0));
    bool keyframe = !CFDictionaryContainsKey(sample_attachments, kCMSampleAttachmentKey_NotSync);
    
    output_buffer_.clear();
    if (!b_annexb_) {
        H264CMSampleBufferToAvccBuffer(sbuf, &output_buffer_, keyframe);
    } else {
        H264CMSampleBufferToAnnexBBuffer(sbuf, &output_buffer_, keyframe);
    }
    
    callback_->OnEncodedFrame(output_buffer_.c_str(), output_buffer_.size(), codec_config_, keyframe, timestamp_ms);
}

void VideoEncoder::CompressionCallback(void* encoder_opaque,
                                       void* request_opaque,
                                       OSStatus status,
                                       VTEncodeInfoFlags info,
                                       CMSampleBufferRef sbuf) {
    VideoEncoder* encoder = reinterpret_cast<VideoEncoder*>(encoder_opaque);
    if (status == kVTVideoEncoderMalfunctionErr) {
        //CLog::RT("[ERROR] venc -- encoding failed:%d\n", status);
        encoder->state_ = kError;
        return;
    }
    
    InProgressFrameEncode* request = reinterpret_cast<InProgressFrameEncode*>(request_opaque);
    double reference_time = request->reference_time;
    delete request;
    
    if (status != noErr) {
        if (g_error_log_count < 5) {
            //CLog::RT("[ERROR] venc -- encoding failed:%d\n", status);
            g_error_log_count++;
        } else {
            encoder->state_ = kError;
        }
        
        return;
    }
    if ((info & kVTEncodeInfo_FrameDropped)) {
        //CLog::RT("[INFO] venc -- frame dropped\n");
        return;
    }
    g_error_log_count = 0;
    
    encoder->DoCallback(sbuf, reference_time);
}
   
// Copy a H.264 frame stored in a CM sample buffer to an Annex B buffer. Copies
// parameter sets for keyframes before the frame data as well.
void VideoEncoder::H264CMSampleBufferToAnnexBBuffer(CMSampleBufferRef sbuf,
                                                    std::string* output_buffer,
                                                    bool keyframe) {
    std::string* annexb_buffer = output_buffer;
    
    // Perform two pass, one to figure out the total output size, and another to
    // copy the data after having performed a single output allocation. Note that
    // we'll allocate a bit more because we'll count 4 bytes instead of 3 for
    // video NALs.
    OSStatus status;
    // Get the sample buffer's block buffer and format description.
    CMBlockBufferRef bb = CMSampleBufferGetDataBuffer(sbuf);
    //DCHECK(bb);
    CMFormatDescriptionRef fdesc = CMSampleBufferGetFormatDescription(sbuf);
    //DCHECK(fdesc);
    size_t bb_size = CMBlockBufferGetDataLength(bb);
    size_t total_bytes = bb_size;
    
    size_t pset_count;
    int nal_size_field_bytes;
    status = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, 0, nullptr, nullptr, &pset_count, &nal_size_field_bytes);
    if (status ==
        kCMFormatDescriptionBridgeError_InvalidParameter) {
        //DLOG(WARNING) << " assuming 2 parameter sets and 4 bytes NAL length header";
        pset_count = 2;
        nal_size_field_bytes = 4;
    } else if (status != noErr) {
        //CLog::RT("CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d\n", status);
        return;
    }
    
    if (keyframe) {
        const uint8_t* pset;
        size_t pset_size;
        for (size_t pset_i = 0; pset_i < pset_count; ++pset_i) {
            status =
            CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, pset_i, &pset, &pset_size, nullptr, nullptr);
            if (status != noErr) {
                //CLog::RT("CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d\n", status);
                return;
            }
            total_bytes += pset_size + nal_size_field_bytes;
        }
    }
    annexb_buffer->reserve(total_bytes);
    const char* offset = annexb_buffer->data();
    // Copy all parameter sets before keyframes.
    if (keyframe) {
        const uint8_t* pset;
        size_t pset_size;
        uint8_t nal_unit_type;
        
        for (size_t pset_i = 0; pset_i < pset_count; ++pset_i) {
            status =
            CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, pset_i, &pset, &pset_size, nullptr, nullptr);
            if (status != noErr) {
                //CLog::RT(" CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d", status);
                return;
            }
            
            nal_unit_type = pset[0] & 0x1F;
            static const char startcode_4[4] = {0, 0, 0, 1};
            
            annexb_buffer->append(startcode_4, sizeof(startcode_4));
            annexb_buffer->append(reinterpret_cast<const char*>(pset), pset_size);
            
            offset += sizeof(startcode_4) + pset_size;
        }
    }
    // Block buffers can be composed of non-contiguous chunks. For the sake of
    // keeping this code simple, flatten non-contiguous block buffers.
    CMBlockBufferRef contiguous_bb = NULL;
    if (!CMBlockBufferIsRangeContiguous(bb, 0, 0)) {
        status = CMBlockBufferCreateContiguous(kCFAllocatorDefault, bb, kCFAllocatorDefault, NULL, 0, 0, 0,
                                               &contiguous_bb);
        if (status != noErr) {
            //CLog::RT("CMBlockBufferCreateContiguous failed:%d\n", status);
            return;
        }
    }
    // Copy all the NAL units. In the process convert them from AVCC format
    // (length header) to AnnexB format (start code).
    char* bb_data;
    status = CMBlockBufferGetDataPointer(contiguous_bb ? contiguous_bb : bb, 0, nullptr,
                                         nullptr, &bb_data);
    if (status != noErr) {
        //CLog::RT("CMBlockBufferGetDataPointer failed:%d\n", status);
        if (contiguous_bb) CFRelease(contiguous_bb);
        return;
    }
    
    if (nal_size_field_bytes == 1) {
        CopyNalsToAnnexB<uint8_t>(bb_data, bb_size, annexb_buffer);
    } else if (nal_size_field_bytes == 2) {
        CopyNalsToAnnexB<uint16_t>(bb_data, bb_size, annexb_buffer);
    } else if (nal_size_field_bytes == 4) {
        CopyNalsToAnnexB<uint32_t>(bb_data, bb_size, annexb_buffer);
    } else {
        //NOTREACHED();
    }
    if (contiguous_bb) CFRelease(contiguous_bb);
}
    
void VideoEncoder::H264CMSampleBufferToAvccBuffer(CMSampleBufferRef sbuf,
                                                  std::string* output_buffer,
                                                  bool keyframe) {
    std::string* avcc_buffer = output_buffer;
    
    // Perform two pass, one to figure out the total output size, and another to
    // copy the data after having performed a single output allocation. Note that
    // we'll allocate a bit more because we'll count 4 bytes instead of 3 for
    // video NALs.
    OSStatus status;
    // Get the sample buffer's block buffer and format description.
    CMBlockBufferRef bb = CMSampleBufferGetDataBuffer(sbuf);
    //DCHECK(bb);
    CMFormatDescriptionRef fdesc = CMSampleBufferGetFormatDescription(sbuf);
    //DCHECK(fdesc);
    size_t bb_size = CMBlockBufferGetDataLength(bb);
    size_t total_bytes = bb_size;
    size_t pset_count;
    int nal_size_field_bytes;
    status = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, 0, nullptr, nullptr, &pset_count, &nal_size_field_bytes);
    if (status ==
        kCMFormatDescriptionBridgeError_InvalidParameter) {
        //DLOG(WARNING) << " assuming 2 parameter sets and 4 bytes NAL length header";
        pset_count = 2;
        nal_size_field_bytes = 4;
    } else if (status != noErr) {
        //CLog::RT("CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d\n", status);
        return ;
    }
    
    if (keyframe) {
        const uint8_t* pset;
        size_t pset_size;
        for (size_t pset_i = 0; pset_i < pset_count; ++pset_i) {
            status =
            CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, pset_i, &pset, &pset_size, nullptr, nullptr);
            if (status != noErr) {
                //CLog::RT("CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d\n", status);
                return;
            }
            total_bytes += pset_size + nal_size_field_bytes;
        }
    }
    avcc_buffer->reserve(total_bytes);
    
    uint8_t* offset = (uint8_t*)avcc_buffer->data();
    
    // Copy all parameter sets before keyframes.
    if (keyframe) {
        const uint8_t* pset;
        size_t pset_size;
        char nalu_size_4[4] = {0, 0, 0, 0};
        off_t payload_size = 0;
        //ASSERT_D(nal_size_field_bytes == sizeof(nalu_size_4));
        int nal_unit_type = 0;
        for (size_t pset_i = 0; pset_i < pset_count; ++pset_i) {
            status =
            CMVideoFormatDescriptionGetH264ParameterSetAtIndex(fdesc, pset_i, &pset, &pset_size, nullptr, nullptr);
            if (status != noErr) {
                //CLog::RT("CMVideoFormatDescriptionGetH264ParameterSetAtIndex failed:%d\n", status);
                return;
            }
            
            payload_size = nal_size_field_bytes + pset_size;
            nal_unit_type = pset[0] & 0x1F;

            base::WriteBigEndian(nalu_size_4, (uint32_t)pset_size);
            avcc_buffer->append(nalu_size_4, sizeof(nalu_size_4));
            avcc_buffer->append(reinterpret_cast<const char*>(pset), pset_size);
            
            offset += payload_size;
        }
    }
    
    char* bb_data;
    status = CMBlockBufferGetDataPointer(bb, 0, nullptr, nullptr, &bb_data);
    if (status != noErr) {
        //CLog::RT("CMBlockBufferGetDataPointer failed:%d\n", status);
        return;
    }
    
    //ASSERT_D(nal_size_field_bytes == sizeof(uint32_t));
    
    char* nalu_data = NULL;
    int nalu_data_size = 0;
    size_t bytes_left = bb_size;
    while (bytes_left > 0) {
        nalu_data = (char*)bb_data;
        
        uint32_t nal_size;
        base::ReadBigEndian(bb_data, &nal_size);
        
        nalu_data_size = nal_size_field_bytes + nal_size;
        
        bytes_left -= nalu_data_size;
        bb_data += nalu_data_size;
        
        avcc_buffer->append(nalu_data, nalu_data_size);
    }
}
    
}

// * end of file //
