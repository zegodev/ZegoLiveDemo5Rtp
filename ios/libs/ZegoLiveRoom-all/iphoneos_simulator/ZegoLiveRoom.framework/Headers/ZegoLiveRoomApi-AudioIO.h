//
//  ZegoLiveRoomApi-AudioIO.h
//  ZegoLiveRoom
//
//  Copyright © 2017年 zego. All rights reserved.
//

#ifndef ZegoLiveRoomApi_AudioIO_h
#define ZegoLiveRoomApi_AudioIO_h

#import "ZegoLiveRoomApi.h"
#import "ZegoAudioCapture.h"

@interface ZegoLiveRoomApi (AudioIO)

#if TARGET_OS_IPHONE

/**
 启用外部音频采集
 
 @warning Deprecated，请使用 [ZegoExternalAudioDevice enableExternalAudioDevice:]
 */
+ (void)enableExternalAudioDevice:(bool)enable __attribute__ ((deprecated));

/**
 获取 IAudioDataInOutput 对象
 
 @warning Deprecated，请使用 [ZegoExternalAudioDevice getIAudioDataInOutput]
 */
- (AVE::IAudioDataInOutput *)getIAudioDataInOutput __attribute__ ((deprecated));

/**
 耳机插入状态下是否使用回声消除
 
 * 建议在初始化 SDK 后，推流前调用设置。
 
 * 注意：
 * 1.iOS 的 SDK 默认使用开启
 
 @param enable 是否启用
 */
- (void)enableAECWhenHeadsetDetected:(bool)enable;

#endif

/**
 对音频进行前处理
 
 * 当开发者需要自处理音频数据时采用此接口，一般是实现特殊功能如变声；SDK 会在 callback 参数中抛出采集的音频数据，开发者从其中获取音频数据进行变声等处理，最后将处理后的数据回传给 SDK。
 * 注意：
 * 1.此 API 必须在初始化 SDK 前调用。 
 * 2.SDK 已经针对采集的音频数据进行了回声消除、噪声抑制等处理，通常情况下，开发者无需再重复处理。
 
 @param prepSet 预处理音频数据的采样率等设置参数，详见 struct ExtPrepSet。
 @param callback 采样数据回调，inFrame 为 SDK 采集的音频数据，outFrame 为开发者处理后应该返回给 SDK 的数据。
 @warning Deprecated，请使用 [ZegoLiveRoomApi (AudioIO) setAudioPrepCallback:]
 */
+ (void)setAudioPrep2:(AVE::ExtPrepSet)prepSet dataCallback:(void(*)(const AVE::AudioFrame& inFrame, AVE::AudioFrame& outFrame))callback;

/**
 设置音频前处理函数, 并开启或关闭音频前处理

 当开发者需要自处理音频数据时采用此接口，一般是实现特殊功能如变声；SDK 会在 callback 参数中抛出采集的音频数据，开发者从其中获取音频数据进行变声等处理，最后将处理后的数据回传给 SDK。
 注意：
 1.此 API 必须在初始化 SDK 后推流前调用。 
 2.SDK 已经针对采集的音频数据进行了回声消除、噪声抑制等处理，通常情况下，开发者无需再重复处理。

 @param callback 采样数据回调，inFrame 为 SDK 采集的音频数据，outFrame 为开发者处理后应该返回给 SDK 的数据。
 @param config 预处理音频数据的采样率等设置参数，详见 struct ExtPrepSet。
 */
- (void)setAudioPrepCallback:(void(*)(const AVE::AudioFrame& inFrame, AVE::AudioFrame& outFrame))callback config:(AVE::ExtPrepSet)config;

/**
 设置音频后处理函数

 当开发者需要自处理拉取的音频数据时采用此接口，一般是实现特殊功能如变声；SDK 会在 callback 参数中抛出拉取的某路流的音频数据，开发者从其中获取音频数据进行处理，最后将处理后的数据回传给 SDK。
 注意：
 1.此 API 必须在初始化 SDK 后拉流前调用。

 @param callback 拉流音频数据回调，streamID 标明当前的音频数据属于哪路流，inFrame 为 SDK 拉取的某路流的音频数据，outFrame 为开发者处理后应该返回给 SDK 的数据。
 @param config 预处理音频数据的采样率等设置参数，详见 struct ExtPostpSet。
 @attention 当回调时，streamID 为空时，表明这是混音后的音频数据
 */
- (void)setAudioPostpCallback:(void(*)(const char* streamID, const AVE::AudioFrame& inFrame, AVE::AudioFrame& outFrame))callback config:(AVE::ExtPostpSet)config;

/**
 开启或关闭音频后处理

当开发者需要自处理拉取的音频数据时采用此接口，一般是实现特殊功能如变声；SDK 会在 callback 参数中抛出拉取的某路流的音频数据，开发者从其中获取音频数据进行处理，最后将处理后的数据回传给 SDK。
 注意：
 1.此 API 必须在拉流后调用。

 @param enable true: 开启音频后处理；false: 开关音频后处理
 @param streamID 流 ID, 当 streamID 为空串时，表明需要混音后的音频数据
 */
- (void)enableAudioPostp:(bool)enable streamID:(NSString *)streamID;


@end

#endif /* ZegoLiveRoomApi_AudioIO_h */
