//
//  ZegoWerewolfHostViewController.m
//  LiveDemo3
//
//  Created by Strong on 2017/3/29.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoWerewolfHostViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"


@interface ZegoWerewolfHostViewController () <ZegoRoomDelegate, ZegoLivePublisherDelegate, ZegoLivePlayerDelegate, ZegoIMDelegate>

@property (nonatomic, weak) IBOutlet UIButton *inTurnSpeakButton;       // 轮流说话 button
@property (nonatomic, weak) IBOutlet UIButton *endInTurnSpeakButton;    // 结束轮流说话 button
@property (nonatomic, weak) IBOutlet UILabel *tipsLabel;                // 当前模式 label
@property (nonatomic, weak) IBOutlet UILabel *countDownLable;           //倒计时

@property (nonatomic, copy) NSString *roomID;                   // 房间 ID
@property (nonatomic, strong) NSMutableArray<ZegoWerewolUserInfo *> *userList;           // 用户列表

@property (nonatomic, assign) NSUInteger currentIndex;          // 主播控制座位号
@property (nonatomic, strong) NSMutableArray<ZegoWerewolUserInfo *> *inturnSpeakingList; // 轮流讲话用户列表

@property (nonatomic, assign) NSUInteger selfCharacter;

@property (nonatomic, strong) NSTimer *speakingTimer;           // 说话时间计时
@property (nonatomic, strong) NSTimer *anchorTimer;             // 主播时间计时
@property (nonatomic, assign) ZegoSpeakingMode speakingMode;    // 当前说话模式

@property (nonatomic, assign) NSUInteger currentSpeakingIndex;  // 当前说话座位号
@property (nonatomic, copy) NSString *currentSpeakingUserId;    // 当前说话用户 Id

@property (nonatomic, strong) NSTimer *sendStopSpeakingTimer;
@property (nonatomic, assign) BOOL isPublishing;                // 正在发布状态
@property (nonatomic, assign) BOOL isSpeaking;                  // 正在讲话状态

@property (nonatomic, assign) BOOL everPublishSuccess;            //不停止推流的情况下，只用发布一次

@end

@implementation ZegoWerewolfHostViewController

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _userList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    
    // 设置当前模式为自由讲话模式
    self.speakingMode = kFreeSpeakingMode;
    self.roomID = [ZegoDemoHelper getMyRoomID:WerewolfInTurnRoom];
    
    self.speakButton.enabled = NO;
    [self.speakButton setTitle:kStartSpeakingTitle forState:UIControlStateNormal];
    [self.speakButton setExclusiveTouch:YES];
    
    // 无音视频权限不允许讲话
    [self checkAudioAuthorizationWithResult:^(BOOL granted) {
        if (granted == NO)
            self.speakButton.enabled = NO;
    }];
    
    [self checkVideoAuthorizationWithResult:^(BOOL granted) {
        if (granted == NO)
            self.speakButton.enabled = NO;
    }];
    
    self.characterLabel.hidden = YES;
    
    self.endInTurnSpeakButton.enabled = NO;
    self.inTurnSpeakButton.enabled = NO;
    
    [self.speakButton addObserver:self forKeyPath:@"enabled" options:NSKeyValueObservingOptionNew context:nil];
    
    [self setupLiveKit];
    [self loginChatRoom];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Event response

// 关闭页面
- (IBAction)onCloseView:(id)sender
{
    if (self.speakingTimer)
    {
        [self onSpeakingTimer];
        [self reportStopSpeaking];
    }
    
    if (self.sendStopSpeakingTimer)
    {
        [self stopTimer:self.sendStopSpeakingTimer];
        [self onStopSpeakingTimer];
    }
    
    [self stopCurrentMode];
    [self.userList removeAllObjects];
    
    [[ZegoDemoHelper api] logoutRoom];
    
    [self.speakButton removeObserver:self forKeyPath:@"enabled"];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

// 开始说话
- (IBAction)onStartTalking:(id)sender
{
    if (self.speakButton.enabled == NO)
        return;
    
    if (!self.isSpeaking)
    {
        // 开始说活
        [self.speakButton setTitle:NSLocalizedString(@"结束说话", nil) forState:UIControlStateNormal];
        [self startTalking];
    }
    else
    {
        // 停止说话
        [self stopTalking];
    }
}

#pragma mark --  Touch InTurnButton

- (IBAction)onInturnButton:(id)sender
{
    self.inturnSpeakingList = [NSMutableArray arrayWithArray:self.userList];
    
    self.speakButton.enabled = NO;
    
    NSDictionary *characters = [self randomCharacter];
    [self broadInTurnSpeaking:characters];
}

- (NSDictionary *)randomCharacter
{
    NSUInteger count = self.inturnSpeakingList.count;
    NSMutableDictionary *characters = [NSMutableDictionary dictionary];
    NSMutableArray *countArray = [NSMutableArray array];
    
    for (ZegoWerewolUserInfo *userInfo in self.inturnSpeakingList)
    {
        int x = arc4random() % count + 1;
        while ([self isRandomNumberExist:countArray number:x])
        {
            x = arc4random() % count + 1;
        }
        
        [countArray addObject:@(x)];
        [characters setObject:@(x) forKey:userInfo.userId];
    }
    
    return characters;
}

- (BOOL)isRandomNumberExist:(NSArray *)countArray number:(int)number
{
    for (NSNumber *character in countArray)
    {
        if ([character intValue] == number)
            return YES;
    }
    
    return NO;
}

#pragma mark --  Touch EndInTurnButton

- (IBAction)onEndInturnButton:(id)sender
{
    //每个人都可以推流
    [self.inturnSpeakingList removeAllObjects];
    self.inturnSpeakingList = nil;
    self.characterLabel.hidden = YES;
    self.countDownLable.hidden = YES;
    
    self.speakingMode = kFreeSpeakingMode;
    self.speakButton.enabled = NO;
    
    if (self.dontStopPublishMode)
        [self stopCurrentDontStopPublishMode];
    else
        [self stopCurrentMode];
    
    [self stopTimer:self.sendStopSpeakingTimer];
    
    if (self.speakingTimer)
    {
        [self.speakingTimer invalidate];
        self.speakingTimer = nil;
    }
    
    if (self.anchorTimer)
    {
        [self.anchorTimer invalidate];
        self.anchorTimer = nil;
    }
    
    self.currentSpeakingIndex = 0;
    self.currentSpeakingUserId = nil;
    [self broadFreeSpeaking];
}

#pragma mark -- Talking

- (void)startTalkingWithStopMode
{
    self.tipsLabel.text = NSLocalizedString(@"正在系统同步...", nil);
    
    [self stopTimer:self.sendStopSpeakingTimer];
    
    // 关闭麦克风和摄像头
    [[ZegoDemoHelper api] enableMic:NO];
    [[ZegoDemoHelper api] enableCamera:NO];
    
    // 发布
    [self doPublish];
}

- (void)startTalkingWithDontStopMode
{
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    //此信令主用用来更新界面
    [self reportStartSpeaking];
    
    //出预览画面
    [[ZegoDemoHelper api] enableMic:YES];
    [[ZegoDemoHelper api] enableCamera:YES];
    
    if (self.speakingMode == kFreeSpeakingMode)
        [[ZegoDemoHelper api] setPreviewView:userInfo.videoView];
    else if (self.speakingMode == kInTurnSpeakingMode)
        [[ZegoDemoHelper api] setPreviewView:self.bigPlayView];
    
    self.tipsLabel.text = NSLocalizedString(@"正在说话", nil);
    
    self.isSpeaking = YES;
}

- (void)stopTalkingWithStopMode
{
    [[ZegoDemoHelper api] enableMic:NO];
    [[ZegoDemoHelper api] enableCamera:NO];
    [[ZegoDemoHelper api] setPreviewView:nil];
    
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    if (userInfo.streamId == nil)
    {
        //推流失败
    }
    else if (self.isPublishing)
    {
        //正在推流
        [self stopPublish];
        if (self.speakingMode == kInTurnSpeakingMode)
        {
            [self stopTimer:self.speakingTimer];
            [self reportStopSpeaking];
            
            [self updateSpeakingButton:NO];
        }
        else if (self.speakingMode == kFreeSpeakingMode)
        {
            [self updateSpeakingButton:YES];
        }
        self.tipsLabel.text = NSLocalizedString(@"推流中止", nil);
    }
    else
    {
        //推流成功，停止推流
        self.tipsLabel.text = NSLocalizedString(@"推流中止", nil);
        
        self.speakButton.enabled = NO;
        self.sendStopSpeakingTimer = [NSTimer scheduledTimerWithTimeInterval:kPostSpeakingInterval target:self selector:@selector(onStopSpeakingTimer) userInfo:nil repeats:NO];
        [self reportStopSpeaking];
    }
}

- (void)stopTalkingWithDontStopMode
{
    [[ZegoDemoHelper api] enableMic:NO];
    [[ZegoDemoHelper api] enableCamera:NO];
    [[ZegoDemoHelper api] setPreviewView:nil];
    
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    if (userInfo.streamId == nil)
    {
        //推流失败
    }
    else
    {
        if (self.speakingMode == kFreeSpeakingMode)
            self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
        else if (self.speakingMode == kInTurnSpeakingMode)
            self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
        
        if (self.speakingMode == kInTurnSpeakingMode)
        {
            [self stopTimer:self.speakingTimer];
            [self updateSpeakingButton:NO];
        }
        else if (self.speakingMode == kFreeSpeakingMode)
        {
            [self updateSpeakingButton:YES];
        }
        
        [self reportStopSpeaking];
    }
    
    self.isSpeaking = NO;
}

// 开始说话
- (void)startTalking
{
    if (self.dontStopPublishMode)
        [self startTalkingWithDontStopMode];
    else
        [self startTalkingWithStopMode];
}

- (void)stopTalking
{
    if (self.dontStopPublishMode)
        [self stopTalkingWithDontStopMode];
    else
        [self stopTalkingWithStopMode];
}

- (void)updateSpeakingButton:(BOOL)enable
{
    self.speakButton.enabled = enable;
    [self.speakButton setTitle:kStartSpeakingTitle forState:UIControlStateNormal];
}

- (void)onStopSpeakingTimer
{
    if (self.speakingMode == kInTurnSpeakingMode)
    {
        [self stopSpeakingTimer];
    }
    else if (self.speakingMode == kFreeSpeakingMode)
    {
        [self stopPublish];
        [self updateSpeakingButton:YES];
        
        ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
        userInfo.streamId = nil;
    }
    
    [self stopTimer:self.sendStopSpeakingTimer];
    
    if (self.speakingMode == kFreeSpeakingMode)
        self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
    else if (self.speakingMode == kInTurnSpeakingMode)
        self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
}

- (void)stopTimer:(NSTimer *)timer
{
    if (timer)
    {
        [timer invalidate];
        timer = nil;
    }
}

#pragma mark - Private methods

#pragma mark -- Live room

- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
    [[ZegoDemoHelper api] setPlayerDelegate:self];
    [[ZegoDemoHelper api] setPublisherDelegate:self];
    [[ZegoDemoHelper api] setIMDelegate:self];
}

- (void)loginChatRoom
{
    self.tipsLabel.text = NSLocalizedString(@"开始登录房间", nil);
    
    [[ZegoDemoHelper api] setRoomConfig:NO userStateUpdate:YES];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID
                           roomName:self.liveTitle
                               role:ZEGO_ANCHOR
                withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
                    if (errorCode == 0)
                    {
                        self.tipsLabel.text = NSLocalizedString(@"登录房间成功", nil);
                        
                        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
                        [self addLogString:logString];
                        
                        ZegoWerewolUserInfo *userInfo = [ZegoWerewolUserInfo new];
                        userInfo.userId = [ZegoSettings sharedInstance].userID;
                        userInfo.userName = [ZegoSettings sharedInstance].userName;
                        userInfo.index = 1;
                        
                        self.currentIndex = 1;
                        
                        [self createPublishView:userInfo];
                        [self.userList addObject:userInfo];
                        
                        if (self.dontStopPublishMode)
                        {
                            [self doPublishNoStopPublishMode];
                            self.isSpeaking = NO;
                        }
                        self.speakButton.enabled = YES;     // 登录成功以后，才讲开始说话button enable
                        self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
                    }
                    else
                    {
                        self.tipsLabel.text = NSLocalizedString(@"登录房间失败", nil);
                        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间失败. error: %d", nil), errorCode];
                        [self addLogString:logString];
                    }
                }];
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)]];
}

// 创建新发布view
- (void)createPublishView:(ZegoWerewolUserInfo *)userInfo
{
    [self createPlayView:userInfo];
    
    [self setAnchorConfig];
}

// 创建新播放view
- (void)createPlayView:(ZegoWerewolUserInfo *)userInfo
{
    userInfo.videoView = [[UIView alloc] init];
    userInfo.videoView.translatesAutoresizingMaskIntoConstraints = NO;
    userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
    [self.playViewContainer addSubview:userInfo.videoView];
    
    [self addNumber:userInfo.index toView:userInfo.videoView];
    [self addText:userInfo.userName toView:userInfo.videoView];
    
    [self.playViewContainer sendSubviewToBack:userInfo.videoView];
    
    [self setContainerConstraints:userInfo.videoView viewIndex:self.playViewContainer.subviews.count];
}

// 推流设置
- (void)setAnchorConfig
{
    ZegoAVConfig *config = [[ZegoAVConfig alloc] init];
    config.videoEncodeResolution = self.videoSize;
    config.videoCaptureResolution = config.videoEncodeResolution;
    config.fps= 15;
    config.bitrate = self.bitrate;
    
    [[ZegoDemoHelper api] setAVConfig:config];
    [[ZegoDemoHelper api] enableBeautifying:ZEGO_BEAUTIFY_POLISH | ZEGO_BEAUTIFY_WHITEN];
    [[ZegoDemoHelper api] setPreviewViewMode:ZegoVideoViewModeScaleAspectFill];
    
    if ([ZegoDemoHelper recordTime])
    {
        [[ZegoDemoHelper api] enablePreviewMirror:false];
    }
}

#pragma mark -- User

// 获取当前用户列表
- (NSArray<ZegoUser *> *)getCurrentMemberList
{
    NSMutableArray *memberList = [NSMutableArray arrayWithCapacity:self.userList.count];
    for (ZegoWerewolUserInfo *info in self.userList)
    {
        if ([info.userId isEqualToString:[ZegoSettings sharedInstance].userID])
            continue;
        
        ZegoUser *user = [ZegoUser new];
        user.userId = info.userId;
        user.userName = info.userName;
        
        [memberList addObject:user];
    }
    
    return memberList;
}

// 移除用户
- (void)removeOldUser:(NSString *)userId broadcast:(BOOL)broadcast
{
    ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:userId];
    BOOL userExist = NO;
    
    if (userInfo != nil)
    {
        [self stopPlay:userInfo];
        
        [self removeInTurnSpeakingUser:userId];
        if (broadcast)
            [self broadUserLeave:userId];
        
        [self updateContainerConstraintsForRemove:userInfo.videoView];
        
        [self.userList removeObject:userInfo];
        
        userExist = YES;
    }
    
    if (self.userList.count < 2 && userExist)
    {
        if (self.inTurnSpeakButton.enabled)
        {
            [self onEndInturnButton:nil];
        }
        
        self.inTurnSpeakButton.enabled = NO;
        self.endInTurnSpeakButton.enabled = NO;
        
        //只有一个人时，切换为自由模式
        [self stopCurrentMode];
        self.speakingMode = kFreeSpeakingMode;
        [self updateSpeakingButton:YES];
        
        self.tipsLabel.text = NSLocalizedString(@"所有玩家都退出了", nil);
    }
}

- (void)removeInTurnSpeakingUser:(NSString *)userId
{
    if (self.speakingMode == kFreeSpeakingMode)
        return;
    
    ZegoWerewolUserInfo *userInfo = nil;
    for (ZegoWerewolUserInfo *info in self.inturnSpeakingList)
    {
        if ([userId isEqualToString:info.userId])
        {
            userInfo = info;
            break;
        }
    }
    
    if (userInfo != nil)
    {
        if (userInfo.index == self.currentSpeakingIndex && self.currentSpeakingIndex != 0)
        {
            [self resetPlayViewAndStop:userId];
            [self arrangeNextSpeaker];
        }
        
        [self.inturnSpeakingList removeObject:userInfo];
    }
}

// 获取当前用户信息
- (ZegoWerewolUserInfo *)getSelfUserInfo
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
        {
            return userInfo;
        }
    }
    return nil;
}

// 获取指定userId用户信息
- (ZegoWerewolUserInfo *)getUserInfoByUserId:(NSString *)userId
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:userId])
            return userInfo;
    }
    return nil;
}

#pragma mark -- Publish

- (void)doPublish
{
    // 获取当前用户的 userId
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    userInfo.streamId = [ZegoDemoHelper getPublishStreamID];
    
    [[ZegoDemoHelper api] setWaterMarkImagePath:nil];
    [[ZegoDemoHelper api] setPreviewWaterMarkRect:CGRectMake(-1, -1, -1, -1)];
    [[ZegoDemoHelper api] setPublishWaterMarkRect:CGRectMake(-1, -1, -1, -1)];
    
    [[ZegoDemoHelper api] startPreview];
    [[ZegoDemoHelper api] setPreviewView:nil];
    
    bool b = [[ZegoDemoHelper api] startPublishing:userInfo.streamId title:self.liveTitle flag:self.isUtralServer ? ZEGO_JOIN_PUBLISH : ZEGO_SINGLE_ANCHOR];
    if (b)
    {
        self.isPublishing = YES;
        self.isSpeaking = YES;
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始直播，流ID:%@", nil), userInfo.streamId]];
    }
}

- (void)doPublishNoStopPublishMode
{
    //do publish
    [[ZegoDemoHelper api] enableCamera:NO];
    [[ZegoDemoHelper api] enableMic:NO];
    
    [self doPublish];
}

- (void)stopPublish
{
    [[ZegoDemoHelper api] setPreviewView:nil];
    [[ZegoDemoHelper api] stopPreview];
    [[ZegoDemoHelper api] stopPublishing];
    
    self.isSpeaking = NO;
}

#pragma mark -- InTurnSpeaking

- (void)updatePlayView:(NSString *)userId
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:userId])
            userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.33 alpha:0.5];
        else
            userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
    }
}

- (void)resetPlayViewAndStop:(NSString *)userId
{
    ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:userId];
    if (userInfo == nil)
        return;
    
    if ([userId isEqualToString:[ZegoSettings sharedInstance].userID])
    {
        [self stopPublish];
        userInfo.streamId = nil;
    }
    else
    {
        [self stopPlay:userInfo];
        userInfo.streamId = nil;
    }
    
    userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
}

- (void)resetPlayView:(NSString *)userId
{
    ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:userId];
    if (userInfo == nil)
        return;
    
    if ([userId isEqualToString:[ZegoSettings sharedInstance].userID])
    {
        [[ZegoDemoHelper api] setPreviewView:nil];
        if (!self.dontStopPublishMode)
            userInfo.streamId = nil;
    }
    else
    {
        [[ZegoDemoHelper api] updatePlayView:nil ofStream:userInfo.streamId];
        if (!self.dontStopPublishMode)
            userInfo.streamId = nil;
    }
    
    userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
}

- (void)onAnchorSpeaking
{
    [self updateSpeakingButton:YES];
    
    self.speakingTimer = [NSTimer scheduledTimerWithTimeInterval:kSpeakingTimerInterval target:self selector:@selector(onSpeakingTimer) userInfo:nil repeats:NO];
    
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    [self updatePlayView:userInfo.userId];
    [self broadAllowSpeaking:userInfo.userId];
}

- (void)stopSpeakingTimer
{
    [self stopTimer:self.speakingTimer];
    [self stopTimer:self.sendStopSpeakingTimer];
    
    if (self.dontStopPublishMode)
        [self resetPlayView:[ZegoSettings sharedInstance].userID];
    else
        [self resetPlayViewAndStop:[ZegoSettings sharedInstance].userID];
    
    [self updateSpeakingButton:NO];
}

- (void)onSpeakingTimer
{
    [self stopSpeakingTimer];
    [self reportStopSpeaking];
}

- (void)onAnchorTimer
{
    if (self.anchorTimer)
    {
        [self.anchorTimer invalidate];
        self.anchorTimer = nil;
    }
    
    [self reportNoRespondStopSpeaking:self.currentSpeakingUserId];
    self.currentSpeakingUserId = nil;
    
    [self arrangeNextSpeaker];
}

#pragma mark -- Broadcast message

- (void)broadAllowSpeaking:(NSString *)userId
{
    if (userId.length == 0)
        return;
    
    NSDictionary *infoDict = @{kSpeakingCommandKey: @(kAllowSpeaking), kSpeakingUserIdKey: userId};
    
    NSString *content = [self encodeDictionaryToJSON:infoDict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"下一个说话: %@", nil), userId]];
        
        if (self.anchorTimer)
        {
            [self.anchorTimer invalidate];
            self.anchorTimer = nil;
        }
        
        self.anchorTimer = [NSTimer scheduledTimerWithTimeInterval:kAnchorTimerInterval target:self selector:@selector(onAnchorTimer) userInfo:nil repeats:NO];
    }];
}

- (void)reportStopSpeaking
{
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey : @(kStopSpeaking), kSpeakingUserIdKey: [ZegoSettings sharedInstance].userID};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"结束说话", nil)]];
        
        if (self.speakingMode == kInTurnSpeakingMode) {
            //主播说完了，下一个人
            [self arrangeNextSpeaker];
        }
        
    }];
}

- (void)reportStartSpeaking
{
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey: @(kStartSpeaking), kSpeakingUserIdKey: [ZegoSettings sharedInstance].userID};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始说话", nil)]];
    }];
}

- (void)reportNoRespondStopSpeaking:(NSString *)userId
{
    if (userId.length == 0)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey : @(kStopSpeaking), kSpeakingUserIdKey: userId};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"结束%@说话", nil), userId]];
    }];
}

- (void)broadFreeSpeaking
{
    NSDictionary *dict = @{kSpeakingCommandKey : @(kFreeSpeaking)};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:@"Free Speaking"]];
        
        [self updateSpeakingButton:YES];
        self.inTurnSpeakButton.enabled = YES;
        self.endInTurnSpeakButton.enabled = NO;
        
        self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
    }];
}

- (void)broadInTurnSpeaking:(NSDictionary<NSString *, NSNumber*>*)characters
{
    if (characters == nil)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey : @(kInTurnSpeaking), kUserCharacterKey: characters};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:@"InTurn Speaking"]];
        
        self.characterLabel.hidden = NO;
        NSUInteger selfCharacter = [[characters objectForKey:[ZegoSettings sharedInstance].userID] unsignedIntegerValue];
        self.characterLabel.text = [NSString stringWithFormat:NSLocalizedString(@"角色:%lu", nil), selfCharacter];
        
        self.currentSpeakingIndex = 0;
        self.inTurnSpeakButton.enabled = NO;
        self.endInTurnSpeakButton.enabled = YES;
        
        self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
        self.speakingMode = kInTurnSpeakingMode;
        
        [self stopTimer:self.sendStopSpeakingTimer];
        if (self.dontStopPublishMode)
            [self stopCurrentDontStopPublishMode];
        else
            [self stopCurrentMode];
        
        [self arrangeNextSpeaker];
    }];
}

- (void)broadUserLeave:(NSString *)userId
{
    if (userId.length == 0)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey : @(kUserLeaveRoom), kUserIdKey: userId};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:@"user Leave Room"]];
    }];
}

- (void)answerRoomInfoAggreed:(NSString *)userId userName:(NSString *)userName
{
    self.currentIndex += 1;
    
    NSMutableArray *userContent = [NSMutableArray arrayWithCapacity:self.userList.count];
    for (ZegoWerewolUserInfo *info in self.userList)
    {
        [userContent addObject:[self serializeWolfUserInfo:info]];
    }
    
    if (userContent.count == 0)
        return;
    
    NSDictionary *dict = @{kSpeakingCommandKey: @(kAnswerRoomInfo), kUserIndexKey: @(self.currentIndex), kSpeakingModeKey: @(self.speakingMode), kCurrentUserListKey: userContent, kServerModeIndexKey : @(self.isUtralServer), kDontStopPublishKey: @(self.dontStopPublishMode)};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    ZegoUser *user = [ZegoUser new];
    user.userId = userId;
    user.userName = userName;
    
    [[ZegoDemoHelper api] sendCustomCommand:@[user] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:@"Answer %@ about Room Info", userName]];
        
        ZegoWerewolUserInfo *userInfo = [ZegoWerewolUserInfo new];
        userInfo.userId = userId;
        userInfo.userName = userName;
        userInfo.index = self.currentIndex;
        
        [self createPlayView:userInfo];
        
        //通知其他人新用户加入
        NSDictionary *notifyDict = @{kSpeakingCommandKey: @(kNewUserInRoom), kNewUserKey: [self serializeWolfUserInfo:userInfo]};
        NSString *notifyContent = [self encodeDictionaryToJSON:notifyDict];
        if (notifyContent == nil)
            return;
        
        [[ZegoDemoHelper api] sendCustomCommand:[self getCurrentMemberList] content:notifyContent completion:^(int errorCode, NSString *roomID) {
            [self addLogString:[NSString stringWithFormat:@"notify others about %@", userName]];
        }];
        
        [self.userList addObject:userInfo];
        
        if (self.speakingMode == kFreeSpeakingMode)
        {
            if (self.userList.count >= 2 && self.inTurnSpeakButton.enabled == NO)
                self.inTurnSpeakButton.enabled = YES;
            
            self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
        }
    }];
}

- (void)answerRoomInfo:(NSString *)userId userName:(NSString *)userName
{
    [self removeOldUser:userId broadcast:YES];
    
    return [self answerRoomInfoAggreed:userId userName:userName];
}

#pragma mark -- Stream

- (void)playInSmallView:(ZegoWerewolUserInfo *)userInfo
{
    if (userInfo.streamId.length != 0)
    {
        [[ZegoDemoHelper api] startPlayingStream:userInfo.streamId inView:userInfo.videoView];
        [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFill ofStream:userInfo.streamId];
    }
}

- (void)playInBigView:(ZegoWerewolUserInfo *)userInfo
{
    if (userInfo.streamId.length != 0)
    {
        [[ZegoDemoHelper api] startPlayingStream:userInfo.streamId inView:self.bigPlayView];
        [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFill ofStream:userInfo.streamId];
    }
}

- (void)stopPlayInSmallView:(ZegoWerewolUserInfo *)userInfo
{
    [self stopPlay:userInfo];
}

- (void)stopPlayInBigView:(ZegoWerewolUserInfo *)userInfo
{
    [self stopPlay:userInfo];
}

- (void)stopPlay:(ZegoWerewolUserInfo *)userInfo
{
    if (userInfo.streamId.length != 0)
    {
        [[ZegoDemoHelper api] updatePlayView:nil ofStream:userInfo.streamId];
        [[ZegoDemoHelper api] stopPlayingStream:userInfo.streamId];
    }
}

- (void)stopCurrentMode
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
            [self stopPublish];
        else
            [self stopPlay:userInfo];
        
        userInfo.streamId = nil;
        userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
    }
    
    self.currentSpeakingIndex = 0;
}

- (void)stopCurrentDontStopPublishMode
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
        {
            [[ZegoDemoHelper api] enableCamera:NO];
            [[ZegoDemoHelper api] enableMic:NO];
            
            [[ZegoDemoHelper api] setPreviewView:nil];
            
            self.isSpeaking = NO;
        }
        else
        {
            [[ZegoDemoHelper api] updatePlayView:nil ofStream:userInfo.streamId];
        }
        
        userInfo.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
    }
    
    self.currentSpeakingIndex = 0;
}

#pragma mark -- Dispatch

- (void)arrangeNextSpeaker
{
    if (self.anchorTimer)
    {
        [self.anchorTimer invalidate];
        self.anchorTimer = nil;
    }
    
    [self addLogString:[NSString stringWithFormat:@"current speaking Index: %lu", self.currentSpeakingIndex]];
    
    NSInteger minDelta = INT_MAX;
    NSUInteger index = 0;
    for (ZegoWerewolUserInfo *userInfo in self.inturnSpeakingList)
    {
        if (userInfo.index > self.currentSpeakingIndex && userInfo.index - self.currentSpeakingIndex < minDelta)
        {
            minDelta = userInfo.index - self.currentSpeakingIndex;
            index = [self.inturnSpeakingList indexOfObject:userInfo];
        }
    }
    
    ZegoWerewolUserInfo *userInfo = [self.inturnSpeakingList objectAtIndex:index];
    self.currentSpeakingIndex = userInfo.index;
    self.currentSpeakingUserId = userInfo.userId;
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"下一个说话: %@", nil), userInfo.userName]];
    
    if ([userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
    {
        [self onAnchorSpeaking];
    }
    else
    {
        [self updatePlayView:userInfo.userId];
        if (self.dontStopPublishMode)
        {
            for (ZegoWerewolUserInfo *info in self.userList)
            {
                if (![userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
                    [[ZegoDemoHelper api] updatePlayView:nil ofStream:info.streamId];
                
                if ([info.userId isEqualToString:userInfo.userId])
                {
                    [[ZegoDemoHelper api] updatePlayView:self.bigPlayView ofStream:info.streamId];
                }
            }
        }
        
        [self broadAllowSpeaking:userInfo.userId];
    }
}

#pragma mark - ZegoRoomDelegate

- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"连接失败, error: %d", nil), errorCode];
    [self addLogString:logString];
}

- (void)onStreamUpdated:(int)type streams:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    if (type == ZEGO_STREAM_ADD)
        [self onStreamUpdateAdded:streamList];
    else if (type == ZEGO_STREAM_DELETE)
        [self onStreamUpdateDeleted:streamList];
}

- (void)onStreamUpdateAdded:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:stream.userID];
        if (userInfo == nil)
        {
            [[ZegoDemoHelper api] updatePlayView:nil ofStream:stream.streamID];
            [[ZegoDemoHelper api] stopPlayingStream:stream.streamID];
            continue;
        }
        
        if (userInfo.streamId.length != 0)
        {
            [[ZegoDemoHelper api] updatePlayView:nil ofStream:userInfo.streamId];
            [[ZegoDemoHelper api] stopPlayingStream:userInfo.streamId];
        }
        
        userInfo.streamId = stream.streamID;
        if (self.speakingMode == kFreeSpeakingMode)
        {
            [self playInSmallView:userInfo];
        }
        else
        {
            if ([userInfo.userId isEqualToString:self.currentSpeakingUserId])
                [self playInBigView:userInfo];
        }
    }
}

- (void)onStreamUpdateDeleted:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:stream.userID];
        if (userInfo == nil)
            continue;
        
        if (![userInfo.streamId isEqualToString:stream.streamID])
        {
            [[ZegoDemoHelper api] updatePlayView:nil ofStream:stream.streamID];
            [[ZegoDemoHelper api] stopPlayingStream:stream.streamID];
        }
        
        if (self.speakingMode == kFreeSpeakingMode)
        {
            [self stopPlayInSmallView:userInfo];
        }
        else
        {
            [self stopPlayInBigView:userInfo];
        }
        
        userInfo.streamId = nil;
    }
}

- (void)onReceiveCustomCommand:(NSString *)fromUserID userName:(NSString *)fromUserName content:(NSString *)content roomID:(NSString *)roomID
{
    NSDictionary *dict = [self decodeJSONToDictionary:content];
    if (dict == nil)
        return;
    
    NSUInteger command = [dict[kSpeakingCommandKey] integerValue];
    
    if (command == kStopSpeaking)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        
        if (userId.length == 0 || [[ZegoSettings sharedInstance].userID isEqualToString:userId])
            return;
        
        
        if (![userId isEqualToString:self.currentSpeakingUserId] && self.speakingMode == kInTurnSpeakingMode)
            return;
        
        [self resetPlayView:userId];
        
        if (self.speakingMode == kInTurnSpeakingMode) {
            //安排下一个人说话
            [self arrangeNextSpeaker];
        }

    }
    else if (command == kStartSpeaking)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        
        if (userId.length == 0 || [[ZegoSettings sharedInstance].userID isEqualToString:userId])
            return;
        
        ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:userId];
        if (userInfo == nil)
            return;
        
        if (self.speakingMode == kInTurnSpeakingMode)
        {
            if ([userId isEqualToString:self.currentSpeakingUserId])
                [[ZegoDemoHelper api] updatePlayView:self.bigPlayView ofStream:userInfo.streamId];
        }
        else if (self.speakingMode == kFreeSpeakingMode)
            [[ZegoDemoHelper api] updatePlayView:userInfo.videoView ofStream:userInfo.streamId];
    }
    else if (command == kAskRoomInfo)
    {
        //收到请求房间信息
        [self answerRoomInfo:fromUserID userName:fromUserName];
    }
    else if (command == kUserLeaveRoom)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        
        if (userId.length == 0 || [[ZegoSettings sharedInstance].userID isEqualToString:userId])
            return;
        
        [self removeOldUser:userId broadcast:NO];
    }
    else
    {
        //主播不可能给自己发此消息
        [self addLogString:[NSString stringWithFormat:@"receive %@ info message %lu", fromUserName, (unsigned long)command]];
    }
    
}

#pragma mark - ZegoLivePlayerDelegate

- (void)onPlayStateUpdate:(int)stateCode streamID:(NSString *)streamID
{
    NSLog(@"%s, streamID:%@", __func__, streamID);
    
    if (stateCode == 0)
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"播放流成功, 流ID:%@", nil), streamID];
        [self addLogString:logString];
    }
    else
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"播放流失败, 流ID:%@,  error:%d", nil), streamID, stateCode];
        [self addLogString:logString];
    }
}

- (void)onPlayQualityUpate:(NSString *)streamID quality:(ZegoApiPlayQuality)quality
{
    [self addStaticsInfo:YES stream:streamID fps:quality.fps kbs:quality.kbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
}

- (void)onVideoSizeChangedTo:(CGSize)size ofStream:(NSString *)streamID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"第一帧画面, 流ID:%@", nil), streamID];
    [self addLogString:logString];
}

#pragma mark - ZegoLivePublishDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%s, stream: %@", __func__, streamID);
    
    self.isPublishing = NO;
    if (stateCode == 0)
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播成功,流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        self.tipsLabel.text = NSLocalizedString(@"系统同步成功", nil);
        
        ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
        if (userInfo == nil || ![userInfo.streamId isEqualToString:streamID])
            return;
        
        if (self.dontStopPublishMode)
        {
            self.everPublishSuccess = YES;
            return;
        }
        
        //出预览画面
        [[ZegoDemoHelper api] enableMic:YES];
        [[ZegoDemoHelper api] enableCamera:YES];
        
        if (self.speakingMode == kFreeSpeakingMode)
            [[ZegoDemoHelper api] setPreviewView:userInfo.videoView];
        else
            [[ZegoDemoHelper api] setPreviewView:self.bigPlayView];
    }
    else
    {
        ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
        if (userInfo == nil || ![userInfo.streamId isEqualToString:streamID])
            return;
        
        //推流失败，streamId清空
        userInfo.streamId = nil;
        self.tipsLabel.text = NSLocalizedString(@"系统同步失败", nil);
        
        if (stateCode != 1)
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播失败, 流ID:%@, err:%d", nil), streamID, stateCode];
            [self addLogString:logString];
        }
        else
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播结束, 流ID:%@", nil), streamID];
            [self addLogString:logString];
        }
        
        NSLog(@"%s, stream: %@, err: %u", __func__, streamID, stateCode);
    }
}

- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality
{
    [self addStaticsInfo:YES stream:streamID fps:quality.fps kbs:quality.kbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
}

#pragma mark - IM Delegate

- (BOOL)isUserShouldDelete:(NSArray<ZegoUserState *> *)userList userId:(NSString *)userId
{
    BOOL isExist = NO;
    for (ZegoUserState *state in userList)
    {
        if ([userId isEqualToString:state.userID])
        {
            isExist = YES;
            break;
        }
    }
    
    if (isExist)
        return NO;
    return YES;
}

- (void)onUserUpdate:(NSArray<ZegoUserState *> *)userList updateType:(ZegoUserUpdateType)type
{
    if (type == ZEGO_UPDATE_TOTAL)
    {
        NSMutableArray *deletedArray = [NSMutableArray array];
        for (ZegoWerewolUserInfo *userInfo in self.userList)
        {
            if ([userInfo.userId isEqualToString:[ZegoSettings sharedInstance].userID])
                continue;
            
            if ([self isUserShouldDelete:userList userId:userInfo.userId])
                [deletedArray addObject:userInfo];
        }
        
        for (ZegoWerewolUserInfo *userInfo in deletedArray)
        {
            [self removeOldUser:userInfo.userId broadcast:YES];
        }
        return;
    }
    
    for (ZegoUserState *state in userList)
    {
        if (state.role == ZEGO_ANCHOR && state.updateFlag == ZEGO_USER_DELETE)
        {
            //主播退出，关闭房间
            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"anchor is logout" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
            [alertView show];
            
            [self onCloseView:nil];
        }
        else if (state.updateFlag == ZEGO_USER_ADD)
        {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"%@进入房间,等待对方应答", nil),state.userName]];
        }
        else if (state.updateFlag == ZEGO_USER_DELETE)
        {
            [self removeOldUser:state.userID broadcast:YES];
        }
        
    }
}

#pragma mark observer
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"enabled"])
    {
        if (self.speakingMode == kFreeSpeakingMode)
        {
            self.countDownLable.hidden = YES;
            return;
        }
        
        BOOL isEnabled = [[change objectForKey:NSKeyValueChangeNewKey] boolValue];
        if (isEnabled)
        {
            self.countDownLable.hidden = NO;
            [self startCountDownWithTime:60 fireBlock:^(int seconds) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    self.countDownLable.text = [NSString stringWithFormat:@"%0.2d", seconds];
                });
            }];
        }
        else
        {
            if (self.countDownLable.hidden == NO)
            {
                self.countDownLable.hidden = YES;
                [self stopCountDownTimer];
            }
            
        }
    }
}
@end
