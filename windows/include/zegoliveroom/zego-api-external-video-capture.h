//
//  zego-api-external-video-capture.h
//  zegoavkit
//
//  Created by Randy Qiu on 2017/8/18.
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef zego_api_external_video_capture_h
#define zego_api_external_video_capture_h


namespace ZEGO
{
    namespace VCAP
    {
        
        /**
         设置外部采集设备模块
         
         @param factory 外部采集设备工厂
         @param idx 推流通道
         @attention 必须在 InitSDK 前调用，置空必须在 UninitSDK 之后
         */
        ZEGOAVKIT_API void SetVideoCaptureFactory(AVE::VideoCaptureFactory* factory, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
    }
}

#endif /* zego_api_external_video_capture_h */
