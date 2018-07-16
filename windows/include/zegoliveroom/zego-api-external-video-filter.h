//
//  zego-api-external-video-filter.hpp
//  zegoavkit
//
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef zego_api_external_video_filter_h
#define zego_api_external_video_filter_h


namespace AVE
{
    class VideoFilterFactory;
}

namespace ZEGO
{
namespace VIDEOFILTER
{
    
    /// \brief 设置外部滤镜模块
    /// \param factory 工厂对象
    /// \note 必须在 InitSDK 前调用，并且不能置空
    ZEGOAVKIT_API void SetVideoFilterFactory(AVE::VideoFilterFactory* factory, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
    
}
}

#endif /* zego_api_external_video_filter_h */
