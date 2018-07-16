//
//  ZegoSettings.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoSettings.h"
#import <sys/utsname.h>


#import "advanced/ZegoRenderAudienceViewController.h"
#import "ZegoAudienceViewController.h"
#import "ZegoMoreAudienceViewController.h"
#import "ZegoMixStreamAudienceViewController.h"
#import "ZegoWerewolfInTurnViewController.h"

NSString *kZegoDemoUserIDKey            = @"userid";
NSString *kZegoDemoUserNameKey          = @"username";
NSString *kZegoDemoChannelIDKey         = @"channelid";
NSString *kZegoDemoVideoPresetKey       = @"preset";
NSString *kZegoDemoVideoWitdhKey        = @"resolution-width";
NSString *kZegoDemoVideoHeightKey       = @"resolution-height";
NSString *kZegoDemoVideoFrameRateKey    = @"framerate";
NSString *kZegoDemoVideoBitRateKey      = @"bitrate";
NSString *kZeogDemoBeautifyFeatureKey   = @"beautify_feature";

NSString *kZegoDemoWolfResolutionKey    = @"wolfResolution";
NSString *kZegoDemoWolfModeKey          = @"wolfMode";
NSString *kZegoDemoWolfLowDelayKey      = @"wolfLowDelay";

@implementation ZegoSettings
{
    NSString *_userID;
    NSString *_userName;
    int _beautifyFeature;
}

+ (instancetype)sharedInstance {
    static ZegoSettings *s_instance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_instance = [self new];
    });
    
    return s_instance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _presetVideoQualityList = @[NSLocalizedString(@"超低质量", nil),
                                    NSLocalizedString(@"低质量", nil),
                                    NSLocalizedString(@"标准质量", nil),
                                    NSLocalizedString(@"高质量", nil),
                                    NSLocalizedString(@"超高质量", nil),
                                    NSLocalizedString(@"极高质量", nil),
                                    NSLocalizedString(@"自定义", nil)];
        
        _appTypeList = @[NSLocalizedString(@"国内版", nil),
                         NSLocalizedString(@"国际版", nil),
                         NSLocalizedString(@"自定义", nil)];
        
        [self loadConfig];
    }
    
    return self;
}

- (ZegoUser *)getZegoUser
{
    ZegoUser *user = [ZegoUser new];
    user.userId = [ZegoSettings sharedInstance].userID;
    user.userName = [ZegoSettings sharedInstance].userName;
    
    return user;
}

- (NSUserDefaults *)myUserDefaults {
    return [[NSUserDefaults alloc] initWithSuiteName:@"group.liveDemo5"];
}

#pragma mark - UserID & UserName

- (NSString *)userID {
    if (_userID.length == 0) {
        NSUserDefaults *ud = [self myUserDefaults];
        NSString *userID = [ud stringForKey:kZegoDemoUserIDKey];
        if (userID.length > 0) {
            _userID = userID;
        } else {
            srand((unsigned)time(0));
            _userID = [NSString stringWithFormat:@"%u", (unsigned)rand()];
            [ud setObject:_userID forKey:kZegoDemoUserIDKey];
        }
    }
    
    return _userID;
}


- (void)setUserID:(NSString *)userID {
    if ([_userID isEqualToString:userID]) {
        return;
    }
    
    if (userID.length > 0) {
        _userID = userID;
        NSUserDefaults *ud = [self myUserDefaults];
        [ud setObject:_userID forKey:kZegoDemoUserIDKey];
        [ZegoDemoHelper releaseApi];
    }
}

- (NSString *)userName {
    if (_userName.length == 0) {
        NSUserDefaults *ud = [self myUserDefaults];
        NSString *userName = [ud stringForKey:kZegoDemoUserNameKey];
        if (userName.length > 0) {
            _userName = userName;
        } else {
            srand((unsigned)time(0));
            
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
            NSString *systemVerion = nil;
            auto d = [UIDevice currentDevice];
            struct utsname systemInfo;
            uname(&systemInfo);
            NSString* code = [NSString stringWithCString:systemInfo.machine
                                                encoding:NSUTF8StringEncoding];
            code = [code stringByReplacingOccurrencesOfString:@"," withString:@"."];
            systemVerion = [NSString stringWithFormat:@"%@_%@_%@", d.model, code, d.systemVersion];
            _userName = [NSString stringWithFormat:@"%@-%u", systemVerion, (unsigned)rand()];
#endif
            
            [ud setObject:_userName forKey:kZegoDemoUserNameKey];
        }
    }
    
    return _userName;
}

- (void)setUserName:(NSString *)userName {
    if ([_userName isEqualToString:userName]) {
        return;
    }
    
    if (userName.length > 0) {
        _userName = userName;
        NSUserDefaults *ud = [self myUserDefaults];
        [ud setObject:_userName forKey:kZegoDemoUserNameKey];
        
        [ZegoDemoHelper releaseApi];
    }
}

#pragma mark - Video Config

- (BOOL)selectPresetQuality:(NSInteger)presetIndex {
    if (presetIndex >= self.presetVideoQualityList.count) {
        return NO;
    }
    
    _presetIndex = presetIndex;
    if (_presetIndex < self.presetVideoQualityList.count - 1) {
        _currentConfig = [ZegoAVConfig presetConfigOf:(ZegoAVConfigPreset)_presetIndex];
    }
    
    [self saveConfig];
    return YES;
}

- (void)setCurrentConfig:(ZegoAVConfig *)currentConfig {
    _presetIndex = self.presetVideoQualityList.count - 1;
    _currentConfig = currentConfig;
    
    [self saveConfig];
}

- (CGSize)currentResolution {
    return [self.currentConfig videoEncodeResolution];
}

// 从本地文件加载保存的视频配置
- (void)loadConfig {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    id preset = [ud objectForKey:kZegoDemoVideoPresetKey];
    if (preset) {
        _presetIndex = [preset integerValue];
        if (_presetIndex < _presetVideoQualityList.count - 1) {
            _currentConfig = [ZegoAVConfig presetConfigOf:(ZegoAVConfigPreset)_presetIndex];
            return ;
        }
    } else {
        _presetIndex = ZegoAVConfigPreset_High;
        _currentConfig = [ZegoAVConfig presetConfigOf:ZegoAVConfigPreset_High];
        return ;
    }
    
    _currentConfig = [ZegoAVConfig presetConfigOf:ZegoAVConfigPreset_Generic];
    
    NSInteger vWidth = [ud integerForKey:kZegoDemoVideoWitdhKey];
    NSInteger vHeight = [ud integerForKey:kZegoDemoVideoHeightKey];
    if (vWidth && vHeight) {
        CGSize r = CGSizeMake(vWidth, vHeight);
        _currentConfig.videoEncodeResolution = r;
        _currentConfig.videoCaptureResolution = r;
    }
        
    id frameRate = [ud objectForKey:kZegoDemoVideoFrameRateKey];
    if (frameRate) {
        _currentConfig.fps = (int)[frameRate integerValue];
    }
    
    id bitRate = [ud objectForKey:kZegoDemoVideoBitRateKey];
    if (bitRate) {
        _currentConfig.bitrate = (int)[bitRate integerValue];
    }
}

// 保存视频配置
- (void)saveConfig {
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@(_presetIndex) forKey:kZegoDemoVideoPresetKey];
    
    if (_presetIndex >= self.presetVideoQualityList.count - 1) {
        [ud setInteger:_currentConfig.videoEncodeResolution.width forKey:kZegoDemoVideoWitdhKey];
        [ud setInteger:_currentConfig.videoEncodeResolution.height forKey:kZegoDemoVideoHeightKey];
        [ud setObject:@([_currentConfig fps]) forKey:kZegoDemoVideoFrameRateKey];
        [ud setObject:@([_currentConfig bitrate]) forKey:kZegoDemoVideoBitRateKey];
    } else {
        [ud removeObjectForKey:kZegoDemoVideoWitdhKey];
        [ud removeObjectForKey:kZegoDemoVideoHeightKey];
        [ud removeObjectForKey:kZegoDemoVideoFrameRateKey];
        [ud removeObjectForKey:kZegoDemoVideoBitRateKey];
    }
}

#pragma mark - Beautify

- (int)beautifyFeature {
    if (_beautifyFeature == 0) {
        NSUserDefaults *ud = [self myUserDefaults];
        if ([ud objectForKey:kZeogDemoBeautifyFeatureKey]) {
            _beautifyFeature = (int)[ud integerForKey:kZeogDemoBeautifyFeatureKey];
        } else {
            _beautifyFeature = ZEGO_BEAUTIFY_POLISH | ZEGO_BEAUTIFY_WHITEN;
        }
    }
    
    return _beautifyFeature;
}

- (void)setBeautifyFeature:(int)beautifyFeature {
    if (_beautifyFeature != beautifyFeature) {
        _beautifyFeature = beautifyFeature;
        [[self myUserDefaults] setInteger:_beautifyFeature forKey:kZeogDemoBeautifyFeatureKey];
    }
}

#pragma mark - Background image

- (UIImage *)getBackgroundImage:(CGSize)viewSize withText:(NSString *)text
{
    NSTimeInterval beginTime = [[NSDate date] timeIntervalSince1970];
    
    UIImage *backgroundImage = [UIImage imageNamed:@"ZegoBK"];
    UIGraphicsBeginImageContextWithOptions(viewSize, NO, [UIScreen mainScreen].scale);
    
    CGFloat height = viewSize.height;
    if (viewSize.height < viewSize.width)
        height = viewSize.width;

    [backgroundImage drawInRect:CGRectMake((viewSize.width - height)/2, (viewSize.height - height)/2, height, height)];
    
    if (text.length != 0)
    {
        UIColor *textColor = [UIColor whiteColor];
        UIFont *textFont = [UIFont systemFontOfSize:30];
        NSDictionary *attributes = @{NSFontAttributeName: textFont, NSForegroundColorAttributeName: textColor};
        CGRect textRect = [text boundingRectWithSize:CGSizeZero options:NSStringDrawingUsesLineFragmentOrigin attributes:attributes context:nil];
        [text drawAtPoint:CGPointMake((viewSize.width - textRect.size.width)/2, (viewSize.height - textRect.size.height)/2) withAttributes:attributes];
    }
    
    UIImage *finalImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    NSLog(@"cost time is %f", [[NSDate date] timeIntervalSince1970] - beginTime);
    
    return finalImage;
}

#pragma mark - Room type

- (UIViewController *)getViewControllerFromRoomInfo:(ZegoRoomInfo *)roomInfo
{
    NSString *roomID = roomInfo.roomID;
    NSUInteger liveType = 2; // * 默认play 连麦模式
    if ([roomID hasPrefix:@"#d-"])
    {
        liveType = 1;
    }
    else if ([roomID hasPrefix:@"#m-"])
    {
        liveType = 2;
    }
    else if ([roomID hasPrefix:@"#s-"])
    {
        liveType = 3;
    }
    else if ([roomID hasPrefix:@"#w-"])
    {
        liveType = 4;
    }
    else if ([roomID hasPrefix:@"#i-"])
    {
        liveType = 5;
    }
    
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    if (liveType == 1)
    {
        if ([ZegoDemoHelper usingExternalRender])
        {
            ZegoRenderAudienceViewController *audienceViewController = (ZegoRenderAudienceViewController *)[storyboard instantiateViewControllerWithIdentifier:@"glAudienceID"];
            audienceViewController.roomID = roomID;
            return audienceViewController;
        }
        else
        {
            ZegoAudienceViewController *audienceViewController = (ZegoAudienceViewController *)[storyboard instantiateViewControllerWithIdentifier:@"audienceID"];
            audienceViewController.roomID = roomID;
            audienceViewController.streamIdList = [roomInfo.streamInfo copy];
            return audienceViewController;
        }
    }
    else if (liveType == 2)
    {
        ZegoMoreAudienceViewController *audienceViewController = (ZegoMoreAudienceViewController *)[storyboard instantiateViewControllerWithIdentifier:@"moreAudienceID"];
        audienceViewController.roomID = roomID;
        audienceViewController.streamIdList = [roomInfo.streamInfo copy];
        return audienceViewController;
    }
    else if (liveType == 3)
    {
        ZegoMixStreamAudienceViewController *audienceViewController = (ZegoMixStreamAudienceViewController *)[storyboard instantiateViewControllerWithIdentifier:@"mixStreamAudienceID"];
        audienceViewController.roomID = roomID;
        audienceViewController.streamIdList = [roomInfo.streamInfo copy];
        return audienceViewController;
    }
    else if (liveType == 5)
    {
        ZegoWerewolfInTurnViewController *wolfViewController = (ZegoWerewolfInTurnViewController *)[storyboard instantiateViewControllerWithIdentifier:@"werewolfInTurnID"];
        
        wolfViewController.roomID = roomID;
        wolfViewController.anchorID = roomInfo.anchorID;
        wolfViewController.anchorName = roomInfo.anchorName;
    
        return wolfViewController;
    }
    else
    {
        return nil;
    }
}

@end
