//
//  ZegoWerewolfInTurnViewController.m
//  LiveDemo3
//
//  Created by Strong on 2017/3/27.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoWerewolfInTurnViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"

@interface ZegoWerewolfInTurnViewController () <ZegoRoomDelegate, ZegoLivePublisherDelegate, ZegoLivePlayerDelegate, ZegoIMDelegate>

@property (nonatomic, weak) IBOutlet UILabel *tipsLabel;
@property (nonatomic, weak) IBOutlet UILabel *countDownLable;           //倒计时

@property (nonatomic, copy) NSString* liveTitle;

@property (nonatomic, strong) NSMutableArray<ZegoWerewolUserInfo *> *userList;

//说话时间计时
@property (nonatomic, strong) NSTimer *speakingTimer;
//当前说话模式
@property (nonatomic, assign) ZegoSpeakingMode speakingMode;

@property (nonatomic, strong) NSTimer *sendStopSpeakingTimer;

@property (nonatomic, strong) NSMutableArray<ZegoStream *> *beforeLoginStreamList;

@property (nonatomic, assign) BOOL isPublishing;

@property (nonatomic, assign) BOOL isUtralServer;
@property (nonatomic, assign) BOOL isSpeaking;

@property (nonatomic, copy) NSString *currentSpeakingUserId;    // 当前说话用户 Id

@property (nonatomic, assign) BOOL dontStopPublishMode;
@property (nonatomic, assign) BOOL everPublishSuccess;

@end

@implementation ZegoWerewolfInTurnViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.speakingMode = kFreeSpeakingMode;
    self.userList = [NSMutableArray arrayWithCapacity:self.maxStreamCount];
    
    self.liveTitle = [NSString stringWithFormat:@"Hello-%@", [ZegoSettings sharedInstance].userID];
    
    self.characterLabel.hidden = YES;
    self.countDownLable.hidden = YES;
    
    [self.speakButton setTitle:kStartSpeakingTitle forState:UIControlStateNormal];
    [self.speakButton setExclusiveTouch:YES];
    self.speakButton.enabled = NO;
    
    [self checkAudioAuthorizationWithResult:^(BOOL granted) {
        if (granted == NO)
            self.speakButton.enabled = NO;
    }];
    
    [self checkVideoAuthorizationWithResult:^(BOOL granted) {
        if (granted == NO)
            self.speakButton.enabled = NO;
    }];
    
    if (self.anchorID.length == 0)
    {
        [self notifyAnchorLogout];
    }
    
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

#pragma mark Action
- (IBAction)onCloseView:(id)sender
{
    if (self.speakingTimer != nil)
    {
        [self onSpeakingTimer];
        [self reportStopSpeaking];
    }
    
    if (self.sendStopSpeakingTimer != nil)
    {
        [self stopTimer:self.sendStopSpeakingTimer];
        [self onStopSpeakingTimer];
    }
    
    [self stopCurrentMode];
    [self broadUserLeave:[ZegoSettings sharedInstance].userID];
    
    [self.userList removeAllObjects];
    
    [[ZegoDemoHelper api] logoutRoom];
    
    [self.speakButton removeObserver:self forKeyPath:@"enabled"];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)onStartTalking:(id)sender
{
    if (self.speakButton.enabled == NO)
        return;
    
    if (!self.isSpeaking)
    {
        //开始说活
        [self.speakButton setTitle:NSLocalizedString(@"结束说话", nil) forState:UIControlStateNormal];
        [self startTalking];
    }
    else
    {
        [self stopTalking];
    }
}

- (void)stopTimer:(NSTimer *)timer
{
    if (timer)
    {
        [timer invalidate];
        timer = nil;
    }
}

- (void)startTalkingWithStopMode
{
    self.tipsLabel.text = NSLocalizedString(@"正在系统同步...", nil);
    
    [self stopTimer:self.sendStopSpeakingTimer];
    
    [[ZegoDemoHelper api] enableMic:NO];
    [[ZegoDemoHelper api] enableCamera:NO];
    [self doPublish];
}

- (void)startTalkingWithDontStopMode
{
    ZegoWerewolUserInfo *userInfo = [self getSelfUserInfo];
    if (userInfo == nil)
        return;
    
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
        else
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
    }
    
    [self stopTimer:self.sendStopSpeakingTimer];
    
    if (self.speakingMode == kFreeSpeakingMode)
        self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
    else if (self.speakingMode == kInTurnSpeakingMode)
        self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
}

#pragma mark Help function

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

- (void)removeOldUser:(NSString *)userId
{
    ZegoWerewolUserInfo *userInfo = [self getUserInfoByUserId:userId];
    if (userInfo == nil)
        return;
    
    [self updateContainerConstraintsForRemove:userInfo.videoView];
    [self.userList removeObject:userInfo];
}

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
    
    [[ZegoDemoHelper api] loginRoom:self.roomID roomName:self.liveTitle role: ZEGO_AUDIENCE withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        if (errorCode == 0)
        {
            self.tipsLabel.text = NSLocalizedString(@"登录房间成功", nil);
            
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
            [self addLogString:logString];
            
            self.beforeLoginStreamList = [NSMutableArray arrayWithArray:streamList];
            
            if (streamList.count < self.maxStreamCount)
            {
                //请求主播相关信息
                [self askAnchorRoomInfo];
            }
        }
        else
        {
            self.tipsLabel.text = NSLocalizedString(@"登录房间失败", nil);
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间失败. error: %d", nil), errorCode];
            [self addLogString:logString];
            
            if (errorCode == 1048680)
            {
                [self notifyAnchorLogout];
            }
        }
    }];
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)]];
}

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

- (ZegoWerewolUserInfo *)getUserInfoByUserId:(NSString *)userId
{
    for (ZegoWerewolUserInfo *userInfo in self.userList)
    {
        if ([userInfo.userId isEqualToString:userId])
            return userInfo;
    }
    
    return nil;
}

- (void)createPublishView:(ZegoWerewolUserInfo *)userInfo
{
    [self createPlayView:userInfo];
    
    [self setAnchorConfig];
    [[ZegoDemoHelper api] setPreviewView:userInfo.videoView];
}

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

- (void)doPublish
{
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

#pragma mark InTurnSpeaking
- (void)updatePlayView:(NSString *)userId
{
    for (ZegoWerewolUserInfo *info in self.userList)
    {
        if ([userId isEqualToString:info.userId])
            info.videoView.backgroundColor = [UIColor colorWithWhite:0.333 alpha:0.5];
        else
            info.videoView.backgroundColor = [UIColor colorWithWhite:0.667 alpha:0.5];
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

- (ZegoUser *)getAnchorUser
{
    ZegoUser *user = [ZegoUser new];
    user.userId = self.anchorID;
    user.userName = self.anchorName;
    
    return user;
}

- (void)askAnchorRoomInfo
{
    self.tipsLabel.text = NSLocalizedString(@"等待主持人响应", nil);
    
    NSDictionary *dict = @{kSpeakingCommandKey: @(kAskRoomInfo)};
    NSString *content = [self encodeDictionaryToJSON:dict];
    if (content == nil)
        return;
    
    ZegoUser *user = [self getAnchorUser];
    [[ZegoDemoHelper api] sendCustomCommand:@[user] content:content completion:^(int errorCode, NSString *roomID) {
        [self addLogString:[NSString stringWithFormat:@"Ask Anchor about Room Info"]];
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

#pragma mark View
- (void)playInSmallView:(ZegoWerewolUserInfo *)userInfo
{
    if (userInfo.streamId.length != 0)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始播放流%@, 流ID:", nil), userInfo.streamId]];
        
        [[ZegoDemoHelper api] startPlayingStream:userInfo.streamId inView:userInfo.videoView];
        [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFill ofStream:userInfo.streamId];
    }
}

- (void)playInBigView:(ZegoWerewolUserInfo *)userInfo
{
    if (userInfo.streamId.length != 0)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始播放流%@, 流ID:", nil), userInfo.streamId]];
        
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
}

- (void)playPreviousStream:(ZegoWerewolUserInfo *)info
{
    for (ZegoStream *stream in self.beforeLoginStreamList)
    {
        if ([info.userId isEqualToString:stream.userID])
        {
            info.streamId = stream.streamID;
            [self playInSmallView:info];
            break;
        }
    }
}

#pragma mark ZegoRoomDelegate
- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"连接失败, error: %d", nil), errorCode];
    [self addLogString:logString];
}

- (void)onStreamUpdated:(int)type streams:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    if (self.userList.count == 0)
    {
        //在信令到达前的流
        if (type == ZEGO_STREAM_ADD)
        {
            [self onStreamUpdatedBeforeLoginAdded:streamList];
        }
        else if (type == ZEGO_STREAM_DELETE)
        {
            [self onStreamUpdatedBeforeLoginDeleted:streamList];
        }
        
        return;
    }
    
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
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始播放, 流ID:%@", nil), stream.streamID];
        [self addLogString:logString];
        
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
        
        userInfo.streamId = stream.streamID;
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

- (void)removeOldSameUserStream:(ZegoStream *)stream
{
    for (ZegoStream *oldStream in self.beforeLoginStreamList)
    {
        if ([oldStream.userID isEqualToString:stream.userID])
        {
            [self.beforeLoginStreamList removeObject:oldStream];
            break;
        }
    }
}

- (void)removeStream:(ZegoStream *)stream
{
    for (ZegoStream *oldStream in self.beforeLoginStreamList)
    {
        if ([stream.streamID isEqualToString:oldStream.streamID])
        {
            [self.beforeLoginStreamList removeObject:oldStream];
            break;
        }
    }
}

- (void)onStreamUpdatedBeforeLoginAdded:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        [self removeOldSameUserStream:stream];
        
        [self.beforeLoginStreamList addObject:stream];
    }
}

- (void)onStreamUpdatedBeforeLoginDeleted:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        [self removeStream:stream];
    }
}

- (void)onReceiveCustomCommand:(NSString *)fromUserID userName:(NSString *)fromUserName content:(NSString *)content roomID:(NSString *)roomID
{
    NSDictionary *dict = [self decodeJSONToDictionary:content];
    if (dict == nil)
        return;
    
    NSUInteger command = [dict[kSpeakingCommandKey] integerValue];

    if (command == kAllowSpeaking)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        
        if (userId.length == 0)
            return;
        
        if ([userId isEqualToString:[ZegoSettings sharedInstance].userID])
        {
            //轮到自己说话了
            [self updateSpeakingButton:YES];
            self.speakingTimer = [NSTimer scheduledTimerWithTimeInterval:kSpeakingTimerInterval target:self selector:@selector(onSpeakingTimer) userInfo:nil repeats:NO];
        }
        
        self.currentSpeakingUserId = userId;
        [self updatePlayView:userId];
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
    else if (command == kStopSpeaking)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        if (userId.length == 0)
            return;
        
        //停止播放流的view
        self.currentSpeakingUserId = nil;
        [self resetPlayView:userId];
        
        if ([[ZegoSettings sharedInstance].userID isEqualToString:userId] && self.isSpeaking)
        {
            self.isSpeaking = NO;
            [self stopTimer:self.speakingTimer];
            [self stopTimer:self.sendStopSpeakingTimer];
            
            if (self.speakingMode == kFreeSpeakingMode)
            {
                self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
            }
            else if (self.speakingMode == kInTurnSpeakingMode)
            {
                self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
                [self updateSpeakingButton:NO];
            }
        }
    }
    else if (command == kAnswerRoomInfo)
    {
        NSUInteger userIndex = [dict[kUserIndexKey] unsignedIntegerValue];
        self.speakingMode = (ZegoSpeakingMode)[dict[kSpeakingModeKey] unsignedIntegerValue];
        self.isUtralServer = [dict[kServerModeIndexKey] boolValue];
        self.dontStopPublishMode = [dict[kDontStopPublishKey] boolValue];
        
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"主持人同意了你的请求,当前模式: %d", nil), self.dontStopPublishMode]];
        
        NSArray *dictUserList = dict[kCurrentUserListKey];
        NSMutableArray *currentUserList = [NSMutableArray array];
        for (NSDictionary *dict in dictUserList)
        {
            ZegoWerewolUserInfo *info = [self deserializeWolfUserInfo:dict];
            if (info)
                [currentUserList addObject:info];
        }
        
        if (userIndex > 1)
        {
            if (self.speakingMode == kFreeSpeakingMode)
            {
                self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
                [self updateSpeakingButton:YES];
            }
            else
            {
                self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话(正在游戏,等待下一局)", nil);
                [self updateSpeakingButton:NO];
            }
            
            for (ZegoWerewolUserInfo *info in currentUserList)
            {
                [self createPlayView:info];
                
                if (self.dontStopPublishMode)
                {
                    [self playPreviousStream:info];
                }
                else if (self.speakingMode == kFreeSpeakingMode)
                {
                    [self playPreviousStream:info];
                }
            }
            
            //清理之前的流，不用再记录
            [self.beforeLoginStreamList removeAllObjects];
            self.beforeLoginStreamList = nil;
            
            [self.userList addObjectsFromArray:currentUserList];
            ZegoWerewolUserInfo *userInfo = [ZegoWerewolUserInfo new];
            userInfo.userId = [ZegoSettings sharedInstance].userID;
            userInfo.userName = [ZegoSettings sharedInstance].userName;
            userInfo.index = userIndex;
            
            [self createPublishView:userInfo];
            [self.userList addObject:userInfo];
            
            if (self.dontStopPublishMode && self.speakingMode == kFreeSpeakingMode)
            {
                [self doPublishNoStopPublishMode];
                self.isSpeaking = NO;
            }
        }
        else
        {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"主播返回index %d 错误", nil), userIndex]];
        }
    }
    else if (command == kFreeSpeaking)
    {
        self.tipsLabel.text = NSLocalizedString(@"当前模式:自由说话", nil);
        
        if (!self.everPublishSuccess && self.dontStopPublishMode)
        {
            [self doPublishNoStopPublishMode];
            self.isSpeaking = NO;
        }
        
        [self stopTimer:self.sendStopSpeakingTimer];
        self.speakingMode = kFreeSpeakingMode;
        
        if (self.dontStopPublishMode)
            [self stopCurrentDontStopPublishMode];
        else
            [self stopCurrentMode];
        
        self.characterLabel.hidden = YES;
        [self updateSpeakingButton:YES];
        
        self.currentSpeakingUserId = nil;
    }
    else if (command == kInTurnSpeaking)
    {
        NSDictionary *characterDict = dict[kUserCharacterKey];
        if (characterDict)
        {
            NSUInteger selfCharacter = [[characterDict objectForKey:[ZegoSettings sharedInstance].userID] unsignedIntegerValue];
            self.characterLabel.hidden = NO;
            self.characterLabel.text = [NSString stringWithFormat:NSLocalizedString(@"角色:%lu", nil), selfCharacter];
        }
        
        self.tipsLabel.text = NSLocalizedString(@"当前模式:轮流说话", nil);
        [self stopTimer:self.sendStopSpeakingTimer];
        self.speakingMode = kInTurnSpeakingMode;
        
        if (self.dontStopPublishMode)
            [self stopCurrentDontStopPublishMode];
        else
            [self stopCurrentMode];
        
        [self updateSpeakingButton:NO];
    }
    else if (command == kNewUserInRoom)
    {
        NSDictionary *userInfoDict = dict[kNewUserKey];
        
        ZegoWerewolUserInfo *info = [self deserializeWolfUserInfo:userInfoDict];
        if (info)
        {
            [self createPlayView:info];
            [self.userList addObject:info];
        }
    }
    else if (command == kUserLeaveRoom)
    {
        NSString *userId = dict[kSpeakingUserIdKey];
        
        if (userId.length == 0)
            return;
        
        [self removeOldUser:userId];
    }
    else
    {
        [self addLogString:[NSString stringWithFormat:@"receive %@ info message %lu", fromUserName, (unsigned long)command]];
    }
}

#pragma mark ZegoLivePlayerDelegate
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
    [self addStaticsInfo:NO stream:streamID fps:quality.fps kbs:quality.kbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
}

#pragma mark ZegoLivePublishDelegate
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

- (void)onVideoSizeChangedTo:(CGSize)size ofStream:(NSString *)streamID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"第一帧画面, 流ID:%@", nil), streamID];
    [self addLogString:logString];
}

#pragma mark IM Delegate

- (void)notifyAnchorLogout
{
    //主播退出，关闭房间
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"anchor is logout" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alertView show];
    [self onCloseView:nil];
}

- (void)onUserUpdate:(NSArray<ZegoUserState *> *)userList updateType:(ZegoUserUpdateType)type
{
    for (ZegoUserState *state in userList)
    {
        if (state.role == ZEGO_ANCHOR && state.updateFlag == ZEGO_USER_DELETE)
        {
            //主播退出，关闭房间
            [self notifyAnchorLogout];
        }
        else if (state.updateFlag == ZEGO_USER_ADD)
        {
            [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"%@进入房间,等待主持人处理", nil),state.userName]];
        }
        else if (state.updateFlag == ZEGO_USER_DELETE)
        {
            [self removeOldUser:state.userID];
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
            self.countDownLable.hidden = YES;
            [self stopCountDownTimer];
        }
    }
}

@end
