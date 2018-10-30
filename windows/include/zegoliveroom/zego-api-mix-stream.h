//
//  zego-api-mix-stream.h
//
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_mix_stream_h
#define zego_api_mix_stream_h

#include "./zego-api-mix-stream-defines.h"

namespace ZEGO
{
namespace MIXSTREAM
{
    /** 对应 MixStream 的回调 */
    class IZegoMixStreamCallback
    {
    public:
        /**
         混流请求结果回调
         @param result 混流结果
         @param pszMixStreamID 混流ID
         @param seq 请求 seq
         */
        virtual void OnMixStream(const AV::ZegoMixStreamResult& result, const char* pszMixStreamID, int seq) = 0;
        
        virtual ~IZegoMixStreamCallback() {}
    };
    
    /** 对应 MixStreamEx 的回调 */
    class IZegoMixStreamExCallback
    {
    public:
        /**
         混流请求结果回调
         @param result 混流结果
         @param pszMixStreamID 混流ID
         @param seq 请求 seq
         */
        virtual void OnMixStreamEx(const AV::ZegoMixStreamResultEx& result, const char* pszMixStreamID, int seq) = 0;
        
        virtual ~IZegoMixStreamExCallback() {}
    };
    
    /** 混流中，显示发言者及音量大小的回调。每秒钟10次通知，不拉流没有通知 */
    class IZegoSoundLevelInMixedStreamCallback
    {
    public:
        virtual void OnSoundLevelInMixedPlayStream(AV::SoundLevelInfo *volume_list, int list_size) = 0;
        
        virtual ~IZegoSoundLevelInMixedStreamCallback() {}
    };
    
    /**
     设置对应 MixStream 的回调
     */
    ZEGOAVKIT_API bool SetMixStreamCallback(IZegoMixStreamCallback* pCB);
    
    /**
     混流接口，支持混流单路输出。
     @param seq 请求序号，回调会带回次 seq
     @return true 成功，等待回调，false 失败
     @note 每次需要更新混流配置时，都可以调用此接口；如果需要多次调用，可以通过传入不同的 seq 区分回调
     @note Deprecated, 请使用 MixStreamEx
     */
    ZEGOAVKIT_API bool MixStream(const AV::ZegoCompleteMixStreamConfig& config, int seq);
    
    /**
     设置对应 MixStreamEx 的回调
     */
    ZEGOAVKIT_API bool SetMixStreamExCallback(IZegoMixStreamExCallback* pCB);
    
    /**
     混流接口，支持混流一路或者多路输出。
     
     @param mixStreamID 混流ID
     @param config 混流配置信息
     @return seq 如果 > 0 表示调用成功，而且这个返回值会和 OnMixStream 的参数 seq 一一匹配。
     @note 混流ID，表示混流的唯一ID，调用方应该保证 taskID 的唯一性。如果 taskID 相同，服务端就认为是更新同一个混流。
     */
    ZEGOAVKIT_API int MixStreamEx(const char* mixStreamID, const ZegoMixStreamConfig& config);
    
    /**
     设置接收混流中的音量信息的回调
     
     @param pCB 回调
     @return true 调用成功，false 调用失败
     */
    ZEGOAVKIT_API bool SetSoundLevelInMixedStreamCallback(IZegoSoundLevelInMixedStreamCallback* pCB);
    
}
}

#endif /* zego_api_mix_stream_h */
