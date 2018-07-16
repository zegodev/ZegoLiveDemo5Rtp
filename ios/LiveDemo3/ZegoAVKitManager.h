//
//  ZegoAVKitManager.h
//  LiveDemo
//
//  Copyright © 2015年 Zego. All rights reserved.
//

#pragma once


#import <ZegoLiveRoom/ZegoLiveRoom.h>

#import "./advanced/video_capture_external_demo.h"
#import "./advanced/ZegoVideoCaptureFromImage.h"

typedef enum : NSUInteger {
    SinglePublisherRoom = 1,
    MultiPublisherRoom  = 2,
    MixStreamRoom       = 3,
    WerewolfRoom        = 4,
    WerewolfInTurnRoom  = 5,
} ZegoDemoRoomType;


typedef enum : NSUInteger {
    ZegoAppTypeUDP      = 0,    // 国内版
    ZegoAppTypeI18N     = 1,    // 国际版
    ZegoAppTypeCustom   = 2,    // 自定义
} ZegoAppType;

@interface ZegoDemoHelper : NSObject

+ (ZegoLiveRoomApi *)api;
+ (void)releaseApi;
+ (NSData *)zegoAppSignFromServer;

+ (void)setCustomAppID:(uint32_t)appid sign:(NSString *)sign;
+ (uint32_t)appID;

+ (void)setUsingTestEnv:(bool)testEnv;
+ (bool)usingTestEnv;

+ (bool)usingAlphaEnv;

+ (void)setUsingExternalCapture:(bool)bUse;
+ (bool)usingExternalCapture;

+ (void)setUsingExternalRender:(bool)bUse;
+ (bool)usingExternalRender;

+ (void)setUsingExternalFilter:(bool)bUse;
+ (bool)usingExternalFilter;

+ (void)setEnableRateControl:(bool)bEnable;
+ (bool)rateControlEnabled;

+ (void)setUsingHardwareEncode:(bool)bUse;
+ (bool)usingHardwareEncode;

+ (void)setUsingHardwareDecode:(bool)bUse;
+ (bool)usingHardwareDecode;

+ (void)setEnableReverb:(bool)bEnable;
+ (bool)reverbEnabled;

+ (void)setRecordTime:(bool)record;
+ (bool)recordTime;

+ (BOOL)useHeadSet;
+ (void)checkHeadSet;

+ (void)setUsingInternationDomain:(bool)bUse;
+ (bool)usingInternationDomain;

+ (void)setAppType:(ZegoAppType)type;
+ (ZegoAppType)appType;

+ (NSString *)customAppSign;


#if TARGET_OS_SIMULATOR
+ (ZegoVideoCaptureFactory *)getVideoCaptureFactory;
#else
+ (VideoCaptureFactoryDemo *)getVideoCaptureFactory;
#endif

#pragma mark - Biz Helper

+ (NSString *)getMyRoomID:(ZegoDemoRoomType)roomType;
+ (NSString *)getPublishStreamID;

@end

@interface ZegoDemoHelper (Alpha)
+ (void)setUsingAlphaEnv:(bool)alphaEnv;
@end

