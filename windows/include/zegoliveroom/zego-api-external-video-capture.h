//
//  zego-api-external-video-capture.h
//  zegoavkit
//
//  Created by Randy Qiu on 2017/8/18.
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef zego_api_external_video_capture_h
#define zego_api_external_video_capture_h

#include "zego-api-defines.h"
#include "video_capture.h"

namespace ZEGO
{
    namespace VCAP
    {
        struct TrafficControl
        {
            TrafficControl() : video_bitrate(-1), video_framerate(-1), video_width(-1), video_height(-1)
            {
            }
            
            int video_bitrate;
            int video_framerate;
            int video_width;
            int video_height;
        };

        class IZegoTrafficControlCallback
        {
        public:
            
            /**
             外部视频采集流控回调。

             注意：不要在此回调中执行耗时操作，建议切换到其它线程再执行具体的操作。

             @param rate_control 流控参数
             @param idx 预留（通道 ID，目前只支持对主通道进行流控）
             */
            virtual void OnTrafficControlCallback(const TrafficControl& rate_control, const AV::PublishChannelIndex idx) = 0;
            
            virtual ~IZegoTrafficControlCallback() {}
        };
        
        /**
         设置外部采集设备模块
         
         @param factory 外部采集设备工厂
         @param idx 推流通道
         @attention 必须在 InitSDK 前调用，置空必须在 UninitSDK 之后
         */
        ZEGOAVKIT_API void SetVideoCaptureFactory(AVE::VideoCaptureFactory* factory, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置外部采集流控回调.

         注意：目前只支持对主通道进行流控

         @param callback 流控回调接口，当需要调整采集参数时，通过此回调通知
         @param idx 通道 ID，目前只支持对主通道进行流控
         @return true: 设置成功; false: 设置失败
         */
        ZEGOAVKIT_API bool SetTrafficControlCallback(IZegoTrafficControlCallback* callback, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
    }
}

#endif /* zego_api_external_video_capture_h */
