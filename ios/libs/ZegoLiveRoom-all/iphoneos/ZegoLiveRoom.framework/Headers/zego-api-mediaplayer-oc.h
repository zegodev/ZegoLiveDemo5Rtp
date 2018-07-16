#ifndef zego_api_mediaplayer_oc_h
#define zego_api_mediaplayer_oc_h

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#import "zego-api-defines-oc.h"
#import "video_format.h"


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
 播放错误

 @param code
 */
- (void)onPlayError:(int)code;


/**
 视频开始播放（在支持视频播放后才生效）
 */
- (void)onVideoBegin;


/**
 音频开始播放
 */
- (void)onAudioBegin;


/**
 播放结束
 */
- (void)onPlayEnd;


/**
 完成快进到指定时刻

 @param code >=0 成功，其它表示失败
 @param millisecond 实际快进的进度
 */
- (void)onSeekComplete:(int)code when:(long)millisecond;

@end


@protocol ZegoMediaPlayerVideoPlayDelegate <NSObject>


/**
 视频帧数据回调
 */
@optional
/**
 视频帧数据回调（同步回调）
 
 @param data 视频帧原始数据
 @param size 视频帧原始数据大小
 @param format 视频帧原始数据格式
 @note 这个接口是同步回调，
 */
- (void)onPlayVideoData:(const char *)data Size:(int)size Format:(AVE::VideoDataFormat)format;

@end


/**
 播放器模式

 - MediaPlayerTypePlayer: 播放模式
 - MediaPlayerTypeAux: 播放，并且将其混入推流中
 */
typedef NS_ENUM(NSInteger, MediaPlayerType) {
    
    MediaPlayerTypePlayer,
    MediaPlayerTypeAux
};


/**
 播放器

 注意：播放器只有在引擎启动的情况下才有效，需要在 InitSDK 后再调用，且不能和 InitSDK 在同一个函数里调用。
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
 设置代理

 @param delegate 代理
 */
- (void)setDelegate:(id<ZegoMediaPlayerEventDelegate>)delegate;


/**
 设置视频帧数据代理

 @param delegate 代理
 */
- (void)setVideoPlayDelegate:(id<ZegoMediaPlayerVideoPlayDelegate>)delegate format:(AVE::VideoPixelFormat)format;

/**
 开始播放
 
 @param path 媒体文件的路径
 @param repeat 是否重复播放
 @note 只有在引擎启动的情况下才会播放
 */
- (void)start:(NSString *)path Repeat:(BOOL)repeat;;


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
 快进到指定的进度

 @param millisecond 指定的进度
 */
- (void)seekTo:(long)millisecond;


/**
 获取整个文件的播放时间

 @return 文件的播放时间，单位毫秒
 */
- (long)getDuration;


/**
 获取当前播放的进度

 @return 当前播放进度，单位毫秒
 */
- (long)getCurrentDuration;

#if TARGET_OS_IPHONE

/**
 设置显示视频的view（暂时无用，在支持播放视频后才生效）

 @param view
 */
- (void)setView:(UIView *)view;

#elif TARGET_OS_OSX

/**
 设置显示视频的view（暂时无用，在支持播放视频后才生效）

 @param view
 */
- (void)setView:(NSView *)view;

#endif




/**
 设置音量

 @param volume 音量，范围在0到100，默认值是50
 */
- (void)setVolume:(int)volume;

@end

#endif /* zego_api_mediaplayer_oc_h */
