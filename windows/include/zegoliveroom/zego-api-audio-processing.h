#ifndef zego_api_audio_processing_h
#define zego_api_audio_processing_h

namespace ZEGO
{
    namespace AUDIOPROCESSING
    {
        /** 音频混响模式 */
        enum ZegoAVAPIAudioReverbMode
        {
            ZEGO_AUDIO_REVERB_MODE_SOFT_ROOM = 0,
            ZEGO_AUDIO_REVERB_MODE_WARM_CLUB = 1,
            ZEGO_AUDIO_REVERB_MODE_CONCERT_HALL = 2,
            ZEGO_AUDIO_REVERB_MODE_LARGE_AUDITORIUM = 3,
        };

        /** 无变声音效 值: 0.0 */
        extern const float ZEGO_VOICE_CHANGER_NONE;
        
        /** 女声变男声 值: -3.0 */
        extern const float ZEGO_VOICE_CHANGER_WOMEN_TO_MEN;
        /** 男声变女声 值: 4.0 */
        extern const float ZEGO_VOICE_CHANGER_MEN_TO_WOMEN;
        /** 女声变童声 值: 6.0 */
        extern const float ZEGO_VOICE_CHANGER_WOMEN_TO_CHILD;
        /** 男声变童声 值: 8.0 */
        extern const float ZEGO_VOICE_CHANGER_MEN_TO_CHILD;
        
        /**
         音频混响参数
         */
        struct ZegoAVAPIReverbParams
        {
            /** 房间大小，取值范围[0.0, 1.0]，用于控制产生混响"房间"的大小，房间越大，混响越强 */
            float roomSize;
            
            /** 余响，取值范围[0.0, 0.5]，用于控制混响的拖尾长度 */
            float reverberance;
            
            /** 混响阻尼， 取值范围[0.0， 2.0]，控制混响的衰减程度，阻尼越大，衰减越大 */
            float damping;
            
            /** 干湿比，取值范围 >= 0.0。 控制混响与直达声和早期反射声之间的比例，干(dry)的部分默认定为1，当干湿比设为较小时，湿(wet)的比例较大，此时混响较强 */
            float dryWetRatio;
        };
        
        /**
         设置虚拟立体声
         
         @param enable true 开启，false 关闭
         @param angle 虚拟立体声中声源的角度，范围为0～180，90为正前方，0和180分别对应最右边和最左边
         @return true 成功，false 失败
         @discussion  必须在初始化 SDK 后调用，并且需要设置双声道 ZEGO::LIVEROOM::SetAudioChannelCount,
                      推流成功后动态设置不同的 angle 都会生效
         */
        ZEGOAVKIT_API bool EnableVirtualStereo(bool bEnable, int angle);
    
        /**
         设置音频混响
         
         @param enable true 开启，false 关闭
         @param mode 混响模式，参考 ZegoAVAPIAudioReverbMode
         @return true 成功，false 失败
         @discussion 必须在初始化 SDK 后调用，推流成功后动态设置不同的 mode 都会生效
         */
        ZEGOAVKIT_API bool EnableReverb(bool bEnable, ZegoAVAPIAudioReverbMode mode);
        
        /**
         设置音频混响参数

         @param roomSize 房间大小，取值范围 0.0 ~ 1.0。 值越大说明混响时间越长，产生的混响拖尾效应越大
         @param dryWetRatio 干湿比，取值范围 >= 0.0。 干湿比的值越小，wet的值越大，产生的混响效果越大
         @return true 成功，false 失败
         @discussion 任意一个参数设置为0.0时，混响关闭
         @discussion 必须在初始化 SDK 后调用，推流成功后动态设置不同的 mode 都会生效
         */
        ZEGOAVKIT_API bool SetReverbParam(float roomSize, float dryWetRatio);
        
        
        /**
         设置音频混响参数

         @param params 混响参数，各个参数含义参考 ZegoAVAPIReverbParams 的定义
         @return true 成功，false 失败
         @discussion 必须在初始化 SDK 后调用，推流成功后动态设置不同的 mode 都会生效
         */
        ZEGOAVKIT_API bool SetReverbParam(ZegoAVAPIReverbParams params);
        
        /**
         设置变声器参数

         @param param 变声器参数
         @return true 成功，false 失败
         @discussion 必须在初始化 SDK 后调用
         @discussion 变声音效只针对采集的声音有效
         @discussion 取值[-8.0, 8.0]，几种典型的变声音效(男变女，女变男等)定义见上文
         */
        ZEGOAVKIT_API bool SetVoiceChangerParam(float param);
    
    }
}

#endif /* zego_api_audio_processing_h */
