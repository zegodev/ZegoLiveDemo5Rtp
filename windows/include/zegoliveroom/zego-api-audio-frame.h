//
//  zego-api-audio-frame.h
//  ZegoLiveRoom
//

#ifndef zego_api_audio_frame_h
#define zego_api_audio_frame_h

#include "zego-api-defines.h"

#ifdef __cplusplus
extern "C" {
#endif

    /** 音频帧类型 */
    typedef enum ZegoAudioFrameType
    {
        kZegoAudioFrameTypePCM          = 0x1001,   /** PCM 数据 */
        kZegoAudioFrameTypeAACStream    = 0x1003,   /** AAC 编码数据流 */
    } ZegoAudioFrameType;
    
    /** 音频帧结构 */
    struct ZegoAudioFrame;

    /**
     创建音频帧对象

     @return 返回创建的对象，使用完毕后必须调用 zego_audio_frame_destroy() 接口释放
     */
    ZEGOAVKIT_API struct ZegoAudioFrame* zego_audio_frame_create();
    
    /**
     释放音频帧对象

     @param audio_frame 所有释放的对象
     */
    ZEGOAVKIT_API void zego_audio_frame_destroy(struct ZegoAudioFrame* audio_frame);

    /**
     设置帧数据类型

     @param audio_frame 音频帧
     @param frame_type 帧数据类型，参考 enum ZegoAudioFrameType，默认 kZegoAudioFrameTypePCM
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_set_frame_type(struct ZegoAudioFrame* audio_frame, enum ZegoAudioFrameType frame_type);

    /**
     获取帧数据类型

     @param audio_frame 音频帧
     @param frame_type 帧数据类型，参考 enum ZegoAudioFrameType，默认 kZegoAudioFrameTypePCM
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_get_frame_type(/* in */struct ZegoAudioFrame* audio_frame, /* out */enum ZegoAudioFrameType& frame_type);
    
    /**
     设置采集/渲染配置
     
     @param audio_frame 音频帧
     @param channels 通道数，支持 1(单声道) 或 2(立体声)
     @param sample_rate 采样率
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_set_frame_config(struct ZegoAudioFrame* audio_frame, int channels, int sample_rate);

    /**
     获取采集/渲染配置
     
     @param audio_frame 音频帧
     @param channels 通道数，支持 1(单声道) 或 2(立体声)
     @param sample_rate 采样率
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_get_frame_config(/* in */struct ZegoAudioFrame* audio_frame, /* out */int& channels, /* out */int& sample_rate);

    /**
     设置采集到/待渲染的数据

     @param audio_frame 音频帧
     @param samples 采样数
     @param data 音频数据，注意：内部不会拷贝数据，需要由调用方管理其生命周期
     @return 参考 enum ZegoErrorCode
     @attention 仅支持 16 比特量化深度
     */
    ZEGOAVKIT_API int zego_audio_frame_set_frame_data(struct ZegoAudioFrame* audio_frame, int samples, unsigned char* data);
    
    /**
     获取采集到/待渲染的数据

     @param audio_frame 音频帧
     @param samples 采样数
     @param data 音频数据，注意：内部不会拷贝数据，需要由调用方管理其生命周期
     @return 参考 enum ZegoErrorCode
     @attention 仅支持 16 比特量化深度
     */
    ZEGOAVKIT_API int zego_audio_frame_get_frame_data(/* in */struct ZegoAudioFrame* audio_frame, /* out */int& samples, /* out */unsigned char** data);

    /**
     设置 AAC 编码数据属性

     @param audio_frame 音频帧
     @param timestamp 时间戳，如果数据中只有 AAC 配置信息，填 0
     @param data_length 总数据长度，注意 data_length = AAC编码结果长度 + special_config_length
     @param special_config_length AAC 配置信息长度
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_set_aac_properties(struct ZegoAudioFrame* audio_frame, double timestamp, int data_length, int special_config_length);

    /**
     获取 AAC 编码数据属性

     @param audio_frame 音频帧
     @param timestamp 时间戳，如果数据中只有 AAC 配置信息，填 0
     @param data_length 总数据长度，注意 data_length = AAC编码结果长度 + special_config_length
     @param special_config_length AAC 配置信息长度
     @return 参考 enum ZegoErrorCode
     */
    ZEGOAVKIT_API int zego_audio_frame_get_aac_properties(/* in */struct ZegoAudioFrame* audio_frame, /* out */double& timestamp, /* out */int& data_length, /* out */int& special_config_length);
    
#ifdef __cplusplus
} // __cplusplus defined.
#endif
    
#endif /* zego_api_audio_frame_h */
