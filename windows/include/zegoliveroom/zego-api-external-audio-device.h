//
//  zego-api-external-audio-device.h
//  zegoavkit
//
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_external_audio_device_h
#define zego_api_external_audio_device_h

#include <zego-api-defines.h>

#include "audio_in_output.h"
#include "zego-api-audio-frame.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /** 辅助推流通道音频采集源类别 */
    typedef enum ZegoAuxPublishChannelAudioSrcType
    {
        kZegoAuxPublishChannelAudioSrcTypeNone                      = -1,   /**< 无声 */
        kZegoAuxPublishChannelAudioSrcTypeSameAsMainPublishChannel  = 0,    /**< 和主推流通道一样 */
        kZegoAuxPublishChannelAudioSrcTypeExternalCapture           = 1,    /*** 使用外部采集 */
    } ZegoAuxPublishChannelAudioSrcType;
    
    /**
     主推流通道外部音频采集开关

     @param enable 是否启用外部音频采集
     @return 详见 enum ZegoErrorCode
     @note 必须在InitSDK之前设置；
     @discussion 开发者采用外部采集和渲染后，SDK 内部不负责声音增强、噪音抑制、回音消除等功能，需要用户自己实现。
     */
    ZEGOAVKIT_API int zego_external_audio_device_enable(bool enable);
    
    /**
     选择辅助推流通道的音频采集源
     
     @param type 辅助推流通道音频采集源类别，参考 enum ZegoAuxPublishChannelAudioSrcType
     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_set_audio_src_for_auxiliary_publish_channel(enum ZegoAuxPublishChannelAudioSrcType type);
    
    /**
     开始外部音频采集（通知 SDK）

     @param publish_channel_index 选定推流通道
     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_start_capture(int publish_channel_index);
    
    /**
     结束外部音频采集（通知 SDK）

     @param publish_channel_index 选定推流通道
     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_stop_capture(int publish_channel_index);
    
    /**
     把采集到的音频数据塞进 SDK

     @param publish_channel_index 选定推流通道
     @param audio_frame 采集到的音频帧
     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_on_record_audio_frame(int publish_channel_index, struct ZegoAudioFrame* audio_frame);
    
    /**
     开始外部音频播放（通知 SDK）

     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_start_render();
    
    /**
     结束外部音频播放（通知 SDK）

     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_stop_render();
    
    /**
     从 SDK 取音频渲染数据

     @param audio_frame 得到的音频数据
     @return 详见 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_external_audio_device_on_playback_audio_frame(struct ZegoAudioFrame* audio_frame);
    
#ifdef __cplusplus
} // __cplusplus defined.
#endif


namespace ZEGO { namespace AUDIODEVICE {
    
    /** 参考 zego_external_audio_device_enable */
    inline void EnableExternalAudioDevice(bool bEnable)
    { zego_external_audio_device_enable(bEnable); }
    
    /** 参考 zego_external_audio_device_set_audio_src_for_auxiliary_publish_channel */
    inline int SetAudioSrcForAuxiliaryPublishChannel(ZegoAuxPublishChannelAudioSrcType type)
    { return zego_external_audio_device_set_audio_src_for_auxiliary_publish_channel(type); }
    
    /** 参考 zego_external_audio_device_start_capture */
    inline int StartCapture(AV::PublishChannelIndex publish_channel)
    { return zego_external_audio_device_start_capture(publish_channel); }
    
    /** 参考 zego_external_audio_device_stop_capture */
    inline int StopCapture(AV::PublishChannelIndex publish_channel)
    { return zego_external_audio_device_stop_capture(publish_channel); }
    
    /** 参考 zego_external_audio_device_on_record_audio_frame */
    inline int OnRecordAudioFrame(AV::PublishChannelIndex publish_channel, ZegoAudioFrame* audio_frame)
    { return zego_external_audio_device_on_record_audio_frame(publish_channel, audio_frame); }
    
    /** 参考 zego_external_audio_device_start_render */
    inline int StartRender()
    { return zego_external_audio_device_start_render(); }
    
    /** 参考 zego_external_audio_device_stop_render */
    inline int StopRender()
    { return zego_external_audio_device_stop_render(); }
    
    /** 参考 zego_external_audio_device_on_playback_audio_frame */
    inline int OnPlaybackAudioFrame(ZegoAudioFrame* audio_frame)
    { return zego_external_audio_device_on_playback_audio_frame(audio_frame); }
    
    /**
     获取 IAudioDataInOutput 对象
     
     @return IAudioDataInOutput 对象，参考 IAudioDataInOutput 类型
     @discussion 必须在InitSDK之后调用。
     @warning Deprecated 不建议使用，请使用 zego_external_audio_device_*，或是 ZEGO::AUDIODEVICE::StartCapture 等方法。
     */
    ZEGOAVKIT_API AVE::IAudioDataInOutput* GetIAudioDataInOutput();

} } // namespace ZEGO::AUDIODEVICE

#endif /* zego_api_external_audio_capture_h */
