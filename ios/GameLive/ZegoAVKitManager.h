//
//  ZegoAVKitManager.h
//  LiveDemo
//
//  Copyright © 2015年 Zego. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <ZegoLiveRoom/ZegoLiveRoom.h>
#import <ZegoLiveRoom/ZegoLiveRoomApi-ReplayLive.h>

typedef enum : NSUInteger {
    ZegoAppTypeUDP      = 0,    // 国内版
    ZegoAppTypeI18N     = 1,    // 国际版
    ZegoAppTypeCustom   = 2,    // 自定义
} ZegoAppType;

@interface ZegoAVKitManager : NSObject

+ (instancetype)sharedInstance;

- (void)handleVideoInputSampleBuffer:(CMSampleBufferRef)sampleBuffer;
- (void)handleAudioInputSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

- (void)startLiveWithTitle:(NSString *)liveTitle videoSize:(CGSize)videoSize;
- (void)stopLive;

@end
