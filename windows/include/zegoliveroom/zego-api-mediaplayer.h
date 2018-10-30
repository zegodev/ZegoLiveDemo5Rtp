//
//  zego-api-mediaplayer.h
//  ZegoLiveRoom
//
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_mediaplayer_h
#define zego_api_mediaplayer_h

#include <memory>

#include "zego-api-defines.h"
#include "media_player.h"
#include "zego-api-mediaplayer-defines.h"


namespace ZEGO
{
namespace MEDIAPLAYER
{
    
    /**
     获取播放器 

     @param type 播放器类型（AVE::IMediaPlayer::PlayerType）
     @return 播放器指针（AVE::IMediaPlayer*）
     @note 不要删除返回的 AVE::IMediaPlayer 指针，由引擎控制其生命周期
     @note 播放器只有在引擎启动的情况下才有效，需要在 InitSDK 后再调用，且不能和 InitSDK 在同一个函数里调用。
     @warning Deprecated，请使用 ZEGO::MEDIAPLAYER::InitWithType 初始化 ZegoMediaPlayer
     */
    ZEGOAVKIT_API AVE::IMediaPlayer* GetMediaPlayer(AVE::IMediaPlayer::PlayerType type);
    
    /**
     初始化播放器
     
     @param type @see ZegoMediaPlayerType
     */
    ZEGOAVKIT_API void InitWithType(const ZegoMediaPlayerType type);
    
    /**
     设置音量
     
     @param volume 音量，范围在0到100，默认值是50
     */
    ZEGOAVKIT_API void SetVolume(const int volume);
    
    /**
     开始播放
     
     @param path 媒体文件的路径
     @param repeat 是否重复播放
     @note 只有在引擎启动的情况下才会播放
     */
    ZEGOAVKIT_API void Start(const char *path, const bool repeat);
    
    /**
     停止播放
     */
    ZEGOAVKIT_API void Stop();
    
    /**
     暂停播放
     */
    ZEGOAVKIT_API void Pause();
    
    /**
     恢复播放
     */
    ZEGOAVKIT_API void Resume();
    
    /**
     设置指定的进度进行播放
     
     @param duration 指定的进度，单位毫秒
     */
    ZEGOAVKIT_API void SeekTo(const long duration);
    
    /**
     获取整个文件的播放时长
     
     @return 文件的播放时长，单位毫秒
     */
    ZEGOAVKIT_API long GetDuration();
    
    /**
     获取当前播放的进度
     
     @return 当前播放进度，单位毫秒
     */
    ZEGOAVKIT_API long GetCurrentDuration();
    
    /**
     设置显示视频的view
     
     @param view 播放的控件
     */
#if TARGET_OS_IPHONE || TARGET_OS_OSX || defined(ANDROID)
    ZEGOAVKIT_API void SetView(std::shared_ptr<void> view);
#else
    ZEGOAVKIT_API void SetView(void *view);
#endif
    
    
    /**
     设置播放文件的音轨
     
     @param streamIndex 音轨序号，可以通过 getAudioStreamCount 接口获取音轨个数
     */
    ZEGOAVKIT_API long SetAudioStream(const long streamIndex);
    
    /**
     设置播放器类型
     
     @param type @see ZegoMediaPlayerType
     */
    ZEGOAVKIT_API void SetPlayerType(const ZegoMediaPlayerType type);
    
    /**
     获取音轨个数
     
     @return 音轨个数
     */
    ZEGOAVKIT_API long GetAudioStreamCount();
    
    /**
     设置播放器事件回调
     
     @param callback 回调
     */
    ZEGOAVKIT_API void SetEventCallback(IZegoMediaPlayerEventCallback *callback);
    
    /**
     设置视频帧数据回调
     
     @param callback 回调
     @param format 需要返回的视频帧数据格式，@see ZegoMediaPlayerVideoPixelFormat
     */
    ZEGOAVKIT_API void SetVideoDataCallback(IZegoMediaPlayerVideoDataCallback *callback, ZegoMediaPlayerVideoPixelFormat format);
    
}
}



#endif /* zego_api_mediaplayer_h */
