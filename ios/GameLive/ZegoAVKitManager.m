//
//  ZegoAVKitManager.m
//  LiveDemo
//
//  Copyright © 2015年 Zego. All rights reserved.
//

#include "ZegoAVKitManager.h"

NSString *kZegoDemoAppTypeKey          = @"apptype";
NSString *kZegoDemoAppIDKey            = @"appid";
NSString *kZegoDemoAppSignKey          = @"appsign";

static Byte toByte(NSString* c);
static ZegoAVKitManager *avkitManager;

@interface ZegoAVKitManager () <ZegoRoomDelegate, ZegoLivePublisherDelegate>

@property (nonatomic, strong, readonly) ZegoLiveRoomApi *zegoLiveApi;

@property (nonatomic, copy) NSString *liveTitle;
@property (nonatomic, assign) BOOL requiredHardwareAccelerate;
@property (nonatomic, assign) BOOL testEnvironment;

@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *userName;

@property (nonatomic, assign) ZegoAppType appType;
@property (nonatomic, assign) uint32_t appID;
@property (nonatomic, strong) NSData *appSign;

@property (nonatomic, copy) NSString *liveChannel;
@property (nonatomic, copy) NSString *streamID;

@property (nonatomic, assign) CGSize videoSize;

@end

@implementation ZegoAVKitManager

#pragma mark - Init

+ (instancetype)sharedInstance
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        avkitManager = [[ZegoAVKitManager alloc] init];
    });
    
    return avkitManager;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        _requiredHardwareAccelerate = YES;
        _testEnvironment = NO;
        
        NSUserDefaults *sharedDefaults = [[NSUserDefaults alloc] initWithSuiteName:@"group.liveDemo5"];
        self.userID = [sharedDefaults stringForKey:@"userid"];
        self.userName = [sharedDefaults stringForKey:@"username"];
        if (self.userID.length == 0)
        {
            srand((unsigned)time(0));
            _userID = [NSString stringWithFormat:@"%u", (unsigned)rand()];
            [sharedDefaults setObject:_userID forKey:@"userid"];
            
#if TARGET_OS_SIMULATOR
            _userName = [NSString stringWithFormat:@"simulator-%@", _userID];
#else
            _userName = [NSString stringWithFormat:@"iphone-%@", _userID];
#endif
            [sharedDefaults setObject:_userName forKey:@"username"];
            
            NSLog(@"assign userID");
        }
        
        NSLog(@"[LiveDemo5-GameLive] userID %@, userName: %@", self.userID, self.userName);
        
        [self initZegoLiveApi];
    }
    
    return self;
}

- (void)initZegoLiveApi
{
    if (self.zegoLiveApi != nil)
        return;
    
    [ZegoLiveRoomApi setUseTestEnv:self.testEnvironment];
    [ZegoLiveRoomApi prepareReplayLiveCapture];
    
    self.appSign = [self getZegoAppSign];
    self.appID = [self getAppID];
    
    [ZegoLiveRoomApi setUserID:self.userID userName:self.userName];
    
    _zegoLiveApi = [[ZegoLiveRoomApi alloc] initWithAppID:self.appID appSignature:self.appSign];
    
    [ZegoLiveRoomApi requireHardwareDecoder:self.requiredHardwareAccelerate];
    [ZegoLiveRoomApi requireHardwareEncoder:self.requiredHardwareAccelerate];
    
    [[NSNotificationCenter defaultCenter] addObserverForName:UIApplicationDidReceiveMemoryWarningNotification object:nil queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification * _Nonnull note) {
        NSLog(@"[LiveDemo5-GameLive] Received Memory Warning");
    }];
}

#pragma mark - AppID & AppSign

- (ZegoAppType)appType {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSUInteger type = [ud integerForKey:kZegoDemoAppTypeKey];
    return (ZegoAppType)type;
}

- (uint32_t)getAppID
{
    switch (self.appType) {
        case ZegoAppTypeUDP:
            return 1739272706;  // UDP版
            break;
        case ZegoAppTypeI18N:
            return 3322882036;  // 国际版
            break;
        case ZegoAppTypeCustom:
        {
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            uint32_t appID = [[ud objectForKey:kZegoDemoAppIDKey] unsignedIntValue];
            
            if (appID != 0) {
                return appID;
            } else {
                return 0;
            }
        }
            break;
    }
}

- (NSData *)getZegoAppSign
{
    //!! Demo 暂时把 signKey 硬编码到代码中，该用法不规范
    //!! 规范用法：signKey 需要从 server 下发到 App，避免在 App 中存储，防止盗用
    
    switch (self.appType) {
        case ZegoAppTypeUDP:
        {
            Byte signkey[] = {0x1e,0xc3,0xf8,0x5c,0xb2 ,0xf2,0x13,0x70,0x26,0x4e,0xb3,0x71,0xc8,0xc6,0x5c,0xa3,0x7f,0xa3,0x3b,0x9d,0xef,0xef,0x2a,0x85,0xe0,0xc8,0x99,0xae,0x82,0xc0,0xf6,0xf8};
            return [NSData dataWithBytes:signkey length:32];
        }
            break;
        case ZegoAppTypeI18N:
        {
            Byte signkey[] = {0x5d,0xe6,0x83,0xac,0xa4,0xe5,0xad,0x43,0xe5,0xea,0xe3,0x70,0x6b,0xe0,0x77,0xa4,0x18,0x79,0x38,0x31,0x2e,0xcc,0x17,0x19,0x32,0xd2,0xfe,0x22,0x5b,0x6b,0x2b,0x2f};
            return [NSData dataWithBytes:signkey length:32];
        }
            break;
        case ZegoAppTypeCustom:
        {
            // 自定义模式下从本地持久化文件中加载
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            NSString *appSign = [ud objectForKey:kZegoDemoAppSignKey];
            if (appSign) {
                return ConvertStringToSign(appSign);
            } else {
                return nil;
            }
        }
            break;
    }
}

NSData* ConvertStringToSign(NSString* strSign)
{
    if(strSign == nil || strSign.length == 0)
        return nil;
    strSign = [strSign lowercaseString];
    strSign = [strSign stringByReplacingOccurrencesOfString:@" " withString:@""];
    strSign = [strSign stringByReplacingOccurrencesOfString:@"0x" withString:@""];
    NSArray* szStr = [strSign componentsSeparatedByString:@","];
    int nLen = (int)[szStr count];
    Byte szSign[32];
    for(int i = 0; i < nLen; i++)
    {
        NSString *strTmp = [szStr objectAtIndex:i];
        if(strTmp.length == 1)
            szSign[i] = toByte(strTmp);
        else
        {
            szSign[i] = toByte([strTmp substringWithRange:NSMakeRange(0, 1)]) << 4 | toByte([strTmp substringWithRange:NSMakeRange(1, 1)]);
        }
        NSLog(@"%x,", szSign[i]);
    }
    
    NSData *sign = [NSData dataWithBytes:szSign length:32];
    return sign;
}

Byte toByte(NSString* c)
{
    NSString *str = @"0123456789abcdef";
    Byte b = [str rangeOfString:c].location;
    return b;
}


#pragma mark - Sample buffer

- (void)handleVideoInputSampleBuffer:(CMSampleBufferRef)sampleBuffer
{
    [self.zegoLiveApi handleVideoInputSampleBuffer:sampleBuffer];
}

- (void)handleAudioInputSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType
{
    [self.zegoLiveApi handleAudioInputSampleBuffer:sampleBuffer withType:sampleBufferType];
}

#pragma mark - Start and stop live

- (void)startLiveWithTitle:(NSString *)liveTitle videoSize:(CGSize)videoSize
{
    if (liveTitle.length == 0)
        self.liveTitle = [NSString stringWithFormat:@"Hello-%@", self.userName];
    else
        self.liveTitle = liveTitle;
    
    self.videoSize = videoSize;
    NSLog(@"[LiveDemo5-GameLive] videoSize at start: %@", NSStringFromCGSize(videoSize));
    
    [self.zegoLiveApi setPublisherDelegate:self];
    
//    [ZegoLiveRoomApi uploadLog];
    
    [self loginChatRoom];
}

- (void)stopLive
{
    [self.zegoLiveApi stopPublishing];
    [self.zegoLiveApi logoutRoom];
}

- (void)loginChatRoom
{
    NSString *roomID = [NSString stringWithFormat:@"#d-%@", self.userID];
    [self.zegoLiveApi loginRoom:roomID role:ZEGO_ANCHOR withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        if (errorCode != 0)
            NSLog(@"[LiveDemo5-GameLive] login room error %d", errorCode);
        else
        {
            ZegoAVConfig *config = [ZegoAVConfig new];
//            config.videoEncodeResolution = CGSizeMake(640, 368);
            config.videoEncodeResolution = self.videoSize;
            config.fps = 25;
            config.bitrate = 800000;
            [self.zegoLiveApi setAVConfig:config];
            
            unsigned long currentTime = (unsigned long)[[NSDate date] timeIntervalSince1970];
            self.streamID = [NSString stringWithFormat:@"s-%@-%lu", self.userID, currentTime];
            
            [self.zegoLiveApi startPublishing:self.streamID title:@"1234567890qwertyuiop" flag:ZEGOAPI_JOIN_PUBLISH];
        }
    }];
    
    NSLog(@"[LiveDemo5-GameLive] login Room %@", self.userName);
}


#pragma mark - ZegoLivePublisherDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    if (stateCode == 0)
        NSLog(@"[LiveDemo5-GameLive] publish success，streamID：%@", streamID);
    else
        NSLog(@"[LiveDemo5-GameLive] publish failed %d", stateCode);
}

- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality {

}


@end
