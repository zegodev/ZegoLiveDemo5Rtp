//
//  zego-api-external-audio-capture.h
//  zegoavkit
//
//  Created by lizhanpeng on 2018/1/2.
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_external_audio_device_h
#define zego_api_external_audio_device_h

#include "audio_in_output.h"

namespace ZEGO
{
    namespace AUDIODEVICE
    {
        /**
		设置外部音频设备，包括外部音频采集和外部音频渲染

		@param enable true 开启，false 关闭
		@discussion 必须在InitSDK之前设置；
		@discussion 开发者采用外部采集和渲染后，SDK 内部不负责声音增强、噪音抑制、回音消除等功能，需要用户自己实现。
		*/
		ZEGOAVKIT_API void EnableExternalAudioDevice(bool bEnable);

		/**
		获取 IAudioDataInOutput 对象

		@return IAudioDataInOutput 对象，参考 IAudioDataInOutput 类型
        @discussion 必须在InitSDK之后调用。
		*/
		ZEGOAVKIT_API AVE::IAudioDataInOutput* GetIAudioDataInOutput();
        
    }
}

#endif /* zego_api_external_audio_capture_h */
