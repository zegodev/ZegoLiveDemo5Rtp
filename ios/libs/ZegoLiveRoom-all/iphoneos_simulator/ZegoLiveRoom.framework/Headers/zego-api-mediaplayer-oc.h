#ifndef zego_api_mediaplayer_oc_h
#define zego_api_mediaplayer_oc_h

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define ZEGOView  UIView
#define ZEGOImage UIImage
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#define ZEGOView  NSView
#define ZEGOImage NSImage
#endif

#import "zego-api-defines-oc.h"
#import "zego-api-mediaplayer-defines-oc.h"


/**
 播放器的回调接口
 */
@protocol ZegoMediaPlayerEventDelegate <NSObject>

@optional

/**
 开始播放
 */
- (void)onPlayStart;

/**
 暂停播放
 */
- (void)onPlayPause;

/**
 恢复播放
 */
- (void)onPlayResume;

/**
 播放错误

 @param code
 PLAY_ERROR_NOERROR = 0,
 PLAY_ERROR_FILE =  -1，文件格式不支持,
 PLAY_ERROR_PATH =  -2，路径不存在,
 PLAY_ERROR_CODEC = -3, 文件无法解码
 PLAY_ERROR_NO_SUPPORT_STREAM = -4,文件中没有可播放的音视频流
 PLAY_ERROR_DEMUX = -5, 文件解析过程中出现错误
 */
- (void)onPlayError:(int)code;

/**
 开始播放视频
 */
- (void)onVideoBegin;


/**
 开始播放音频
 */
- (void)onAudioBegin;


/**
 播放结束
 */
- (void)onPlayEnd;

/**
 用户停止播放的回调
 */
- (void)onPlayStop;

/**
 网络音乐资源播放不畅，开始尝试缓存数据。
 
 @warning 只有播放网络音乐资源才需要关注这个回调
 */
- (void)onBufferBegin;

/**
 网络音乐资源可以顺畅播放。
 
 @warning 只有播放网络音乐资源才需要关注这个回调
 */
- (void)onBufferEnd;

/**
 快进到指定时刻

 @param code >=0 成功，其它表示失败
 @param millisecond 实际快进的进度，单位毫秒
 */
- (void)onSeekComplete:(int)code when:(long)millisecond;

/**
 截图
 
 @param image
 */
- (void)onSnapshot:(ZEGOImage *)image;

@end


@protocol ZegoMediaPlayerVideoPlayDelegate <NSObject>


/**
 视频帧数据回调
 */
@optional

/**
 视频帧数据回调
 
 @param data 视频帧原始数据
 @param size 视频帧原始数据大小
 @param format 视频帧原始数据格式
 @note 同步回调，请不要在回调中处理数据或做其他耗时操作
 */
- (void)onPlayVideoData:(const char *)data size:(int)size format:(struct ZegoMediaPlayerVideoDataFormat)format;

/**
 视频帧数据回调
 
 @param data 视频帧原始数据
 @param size 视频帧原始数据大小
 @param format 视频帧原始数据格式
 @note 同步回调，请不要在回调中处理数据或做其他耗时操作
 @see Deprecated, 请使用 onPlayVideoData:size:format:
 */
- (void)onPlayVideoData:(const char *)data Size:(int)size Format:(struct ZegoMediaPlayerVideoDataFormat)format;

@end


/**
 播放器

 */
@interface ZegoMediaPlayer : NSObject


/**
 初始化

 @param type @see MediaPlayerType
 @return 播放器对象
 */
- (instancetype)initWithPlayerType:(MediaPlayerType)type;


/**
 释放播放器
 */
- (void)uninit;


/**
 设置播放器事件回调

 @param delegate 回调
 */
- (void)setDelegate:(id<ZegoMediaPlayerEventDelegate>)delegate;


/**
 设置视频帧数据回调

 @param delegate 回调
 @param format 需要返回的视频帧数据格式，@see ZegoMediaPlayerVideoPixelFormat
 */
- (void)setVideoPlayDelegate:(id<ZegoMediaPlayerVideoPlayDelegate>)delegate format:(ZegoMediaPlayerVideoPixelFormat)format;

/**
 开始播放
 
 @param path 媒体文件的路径
 @param repeat 是否重复播放
 @note 只有在引擎启动的情况下才会播放
 */
- (void)start:(NSString *)path repeat:(BOOL)repeat;

/**
 停止播放
 */
- (void)stop;


/**
 暂停播放
 */
- (void)pause;


/**
 恢复播放
 */
- (void)resume;


/**
 设置指定的进度进行播放

 @param millisecond 指定的进度，单位毫秒
 */
- (void)seekTo:(long)millisecond;


/**
 获取整个文件的播放时长

 @return 文件的播放时长，单位毫秒
 */
- (long)getDuration;


/**
 获取当前播放的进度

 @return 当前播放进度，单位毫秒
 */
- (long)getCurrentDuration;

#if TARGET_OS_IPHONE

/**
 设置显示视频的view

 @param view 播放的控件
 */
- (void)setView:(UIView *)view;

#elif TARGET_OS_OSX

/**
 设置显示视频的view

 @param view 播放的控件
 */
- (void)setView:(NSView *)view;

#endif

/**
 设置音量

 @param volume 音量，范围在0到100，默认值是50
 */
- (void)setVolume:(int)volume;

/**
 设置播放文件的音轨
 
 @param streamIndex 音轨序号，可以通过 getAudioStreamCount 接口获取音轨个数
 */
- (long)setAudioStream:(long)streamIndex;

/**
 设置播放器类型
 
 @param type @see MediaPlayerType
 */
- (void)setPlayerType:(MediaPlayerType)type;

/**
 获取当前播放视频的截图

 @note 只有在调用 setView 设置了显示控件，以及播放状态的情况下，才能正常截图。
 */
- (void)takeSnapshot;

/**
 获取音轨个数
 
 @return 音轨个数
 */
- (long)getAudioStreamCount;

/**
 * 设置是否重复播放
 * 
 * @param enable true:重复播放，false：不重复播放
 */
- (void)enableRepeatMode:(BOOL)enable;

@end

#endif /* zego_api_mediaplayer_oc_h */
