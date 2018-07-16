//
//  ZegoWerewolfBaseViewController.h
//  LiveDemo3
//
//  Created by Strong on 2017/3/29.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoAVKitManager.h"

#define kSpeakingCommandKey    @"command"

#define kSpeakingUserIdKey     @"userId"

#define kCurrentUserListKey    @"currentUserList"
#define kNewUserKey            @"newUser"

#define kUserIdKey             @"userId"
#define kUserNameKey           @"userName"

#define kSpeakingModeKey       @"roomMode"
#define kUserIndexKey          @"userIndex"
#define kServerModeIndexKey    @"urtralServer"
#define kDontStopPublishKey    @"dontStopPublish"

#define kUserCharacterKey      @"character"

#define kPostSpeakingInterval       2
#define kSpeakingTimerInterval      (60 + kPostSpeakingInterval)
#define kAnchorTimerInterval        (5 + (kSpeakingTimerInterval))

#define kStartSpeakingTitle NSLocalizedString(@"开始说话", nil)
#define kStopSpeakingTitle  NSLocalizedString(@"说话结束", nil)

typedef NS_ENUM (NSUInteger, ZegoSpeakingCmd) {
    kAllowSpeaking = 1,
    kStartSpeaking = 2,
    kStopSpeaking = 3,
    
    kFreeSpeaking = 4,
    kInTurnSpeaking = 5,
    
    kAskRoomInfo = 11,
    kAnswerRoomInfo = 12,
    kNewUserInRoom  = 13,
    kUserLeaveRoom  = 14,
};

typedef NS_ENUM(NSUInteger, ZegoSpeakingMode) {
    kFreeSpeakingMode = 1,
    kInTurnSpeakingMode = 2,
};

@interface ZegoWerewolUserInfo : NSObject

@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *userName;
@property (nonatomic, copy) NSString *streamId;
@property (nonatomic, strong) UIView *videoView;
@property (nonatomic, assign) NSUInteger index;

@end

@interface ZegoWerewolfBaseViewController : UIViewController

@property (nonatomic, weak) IBOutlet UIView *playViewContainer;
@property (nonatomic, weak) IBOutlet UIView *bigPlayView;
@property (nonatomic, weak) IBOutlet UIButton *speakButton;
@property (nonatomic, weak) IBOutlet UILabel *characterLabel;

@property (nonatomic, assign) double bitrate;
@property (nonatomic, assign) CGSize videoSize;
@property (nonatomic, assign) ZegoApiPublishFlag flag;

@property (nonatomic, assign, readonly) NSUInteger maxStreamCount;

//json
- (NSString *)encodeDictionaryToJSON:(NSDictionary *)data;
- (NSDictionary *)decodeJSONToDictionary:(NSString *)json;
- (NSDictionary *)serializeWolfUserInfo:(ZegoWerewolUserInfo *)info;
- (ZegoWerewolUserInfo *)deserializeWolfUserInfo:(NSDictionary *)dict;

//Auoto layout
- (void)updateViewConstraints:(UIView *)view viewIndex:(NSUInteger)viewIndex;
- (void)setContainerConstraints:(UIView *)view viewIndex:(NSUInteger)viewIndex;
- (NSUInteger)getViewIndex:(UIView *)view containerView:(UIView *)containerView;
- (void)updateContainerConstraintsForRemove:(UIView *)removeView;

//Log
- (void)addLogString:(NSString *)logString;
- (NSString *)addStaticsInfo:(BOOL)publish stream:(NSString *)streamID fps:(double)fps kbs:(double)kbs rtt:(int)rtt pktLostRate:(int)pktLostRate;

//view
- (void)addNumber:(NSUInteger)number toView:(UIView *)view;
- (void)addText:(NSString *)text toView:(UIView *)view;

//authority
- (BOOL)checkVideoAuthorizationWithResult:(void (^)(BOOL granted))resultBlock;
- (BOOL)checkAudioAuthorizationWithResult:(void (^)(BOOL granted))resultBlock;

//count down timer
- (void)startCountDownWithTime:(NSInteger)time fireBlock:(void (^)(int seconds))block;
- (void)stopCountDownTimer;

@end
