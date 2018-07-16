#ifndef zego_api_mix_stream_h
#define zego_api_mix_stream_h

namespace ZEGO
{
namespace MIXSTREAM
{
    
    class IZegoMixStreamCallback
    {
    public:
        /// \brief 混流请求结果回调
        /// \param result 混流结果
        /// \param pszMixStreamID 混流 ID
        /// \param seq 请求 seq
        virtual void OnMixStream(const AV::ZegoMixStreamResult& result, const char* pszMixStreamID, int seq) = 0;
        
        virtual ~IZegoMixStreamCallback() {}
    };
    
    /** 混流中，显示发言者及音量大小的回调。每秒钟10次通知，不拉流没有通知 */
    class IZegoSoundLevelInMixedStreamCallback
    {
    public:
        virtual void OnSoundLevelInMixedPlayStream(AV::SoundLevelInfo *volume_list, int list_size) = 0;
        
        virtual ~IZegoSoundLevelInMixedStreamCallback() {}
    };
    
    ZEGOAVKIT_API bool SetMixStreamCallback(IZegoMixStreamCallback* pCB);
    
    // \brief 开始混流
    /// \param config 混流配置
    /// \param seq 请求序号，回调会带回次 seq
    /// \return true 成功，等待回调，false 失败
    /// \note 每次需要更新混流配置时，都可以调用此接口；如果需要多次调用，可以通过传入不同的 seq 区分回调
    ZEGOAVKIT_API bool MixStream(const AV::ZegoCompleteMixStreamConfig& config, int seq);
    
    
    /// \brief 设置接收混流中的音量信息的回调
    /// \param pCallback 回调
    ZEGOAVKIT_API bool SetSoundLevelInMixedStreamCallback(IZegoSoundLevelInMixedStreamCallback* pCB);
    
}
}

#endif /* zego_api_mix_stream_h */
