//
//  video_capture_external_demo.h
//  ve_demo
//
//  Created by robotding on 16/5/30.
//  Copyright © 2016年 jjams. All rights reserved.
//

#ifndef video_capture_encoder_h
#define video_capture_encoder_h

#include <string>
#include <VideoToolbox/VideoToolbox.h>
#include <ZegoLiveRoom/ZegoVideoCapture.h>
#include "video_capture.h"

namespace demo {
    
class VideoEncoder {
public:
    VideoEncoder(AVE::VideoCaptureEncodedFrameCallback* callback);
    virtual ~VideoEncoder();
    
    int32_t Encode(CVPixelBufferRef pixel_buffer, double timestamp_ms, bool is_keyframe_required = false);
    int32_t SetConfig(int bitrate, int framerate);
protected:
    static void CompressionCallback(void* encoder_opaque,
                                    void* request_opaque,
                                    OSStatus status,
                                    VTEncodeInfoFlags info,
                                    CMSampleBufferRef sampleBuffer);
    static void H264CMSampleBufferToAnnexBBuffer(CMSampleBufferRef sbuf, std::string* output_buffer, bool keyframe);
    static void H264CMSampleBufferToAvccBuffer(CMSampleBufferRef sampleBuffer, std::string* output_buffer, bool keyframe);
    
    bool SetSessionProperty(CFStringRef key, int32_t value);
    bool SetSessionProperty(CFStringRef key, bool value);
    bool SetSessionProperty(CFStringRef key, CFStringRef value);
    
    int ResetCompressionSession();
    void ConfigureCompressionSession();
    void EmitFrames();
    void DestroyCompressionSession();
    void DoCallback(CMSampleBufferRef sbuf, double timestamp_ms);

protected:
    AVE::VideoCaptureEncodedFrameCallback* callback_;
    AVE::VideoCodecConfig codec_config_;
    
    VTCompressionSessionRef m_oEncSession;
    bool b_annexb_;
    int frame_id_;
    
    int width_;
    int height_;
    int32_t color_format_;
    int32_t bitrate_;
    int32_t framerate_;

    // Internal state of the encoder.
    enum State {
        kEncoding,            // Ready to encode from any point.
        kError,               // Error in encode, can't continue.
    };
    // Encoder state.
    State state_;
    
    uint64_t encoder_counter_ = 0;
    std::string output_buffer_;
};

}
#endif /* video_capture_encoder_h */
