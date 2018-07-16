//
//  ZegoAudienceViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/27.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoMoreAudienceViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoLiveToolViewController.h"

static id selfObject;

@interface ZegoMoreAudienceViewController () <ZegoRoomDelegate, ZegoLivePlayerDelegate, ZegoLivePublisherDelegate, ZegoIMDelegate, UIAlertViewDelegate, ZegoLiveToolViewControllerDelegate>

@property (weak, nonatomic) IBOutlet UIView *playViewContainer;

@property (nonatomic, weak) ZegoLiveToolViewController *toolViewController;

@property (weak, nonatomic) UIButton *publishButton;
@property (weak, nonatomic) UIButton *optionButton;
@property (weak, nonatomic) UIButton *mutedButton;
@property (weak, nonatomic) UIButton *fullscreenButton;
@property (nonatomic, weak) UIButton *sharedButton;

@property (nonatomic, strong) NSMutableArray<ZegoStream *> *streamList;
@property (nonatomic, strong) NSMutableArray<ZegoStream *> *originStreamList;   // 直播秒开流列表

@property (nonatomic, assign) BOOL loginRoomSuccess;

@property (nonatomic, assign) BOOL isPublishing;
@property (nonatomic, copy) NSString *publishTitle;
@property (nonatomic, copy) NSString *publishStreamID;

@property (nonatomic, strong) UIColor *defaultButtonColor;

@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;
@property (nonatomic, strong) NSMutableDictionary *streamID2SizeDict;
@property (nonatomic, strong) NSMutableDictionary *videoSizeDict;

@property (nonatomic, copy) NSString *sharedHls;
@property (nonatomic, copy) NSString *sharedRtmp;

@end

@implementation ZegoMoreAudienceViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    selfObject = self;
    
    for (UIViewController *viewController in self.childViewControllers)
    {
        if ([viewController isKindOfClass:[ZegoLiveToolViewController class]])
        {
            self.toolViewController = (ZegoLiveToolViewController *)viewController;
            self.toolViewController.delegate = self;
            self.toolViewController.isAudience = YES;
            break;
        }
    }
    
    self.optionButton = self.toolViewController.joinLiveOptionButton;
    self.publishButton = self.toolViewController.joinLiveButton;
    self.mutedButton = self.toolViewController.playMutedButton;
    self.fullscreenButton = self.toolViewController.fullScreenButton;
    self.sharedButton = self.toolViewController.shareButton;
    
    _streamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    _viewContainersDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _videoSizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _streamID2SizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _originStreamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    
    [self setupLiveKit];
    
    [self loginRoom];
    
    UIImage *backgroundImage = [[ZegoSettings sharedInstance] getBackgroundImage:self.view.bounds.size withText:NSLocalizedString(@"加载中", nil)];
    [self setBackgroundImage:backgroundImage playerView:self.playViewContainer];
    
    [self setButtonHidden:YES];
    
    self.publishButton.enabled = NO;
    self.optionButton.enabled = NO;
    self.sharedButton.enabled = NO;
    
    self.fullscreenButton.hidden = YES;
    
    [self playStreamEnteringRoom];
    
    if ([ZegoDemoHelper recordTime])
    {
        [self.toolViewController startTimeRecord];
    }

}

- (void)setButtonHidden:(BOOL)hidden
{
    if (hidden)
    {
        self.publishButton.alpha = 0;
        self.optionButton.alpha = 0;
        self.mutedButton.alpha = 0;
    }
    else
    {
        self.publishButton.alpha = 1;
        self.optionButton.alpha = 1;
        self.mutedButton.alpha = 1;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setBackgroundImage:(UIImage *)image playerView:(UIView *)playerView
{
    playerView.backgroundColor = [UIColor colorWithPatternImage:image];
}

#pragma mark fullscreen action

- (NSString *)getStreamIDFromView:(UIView *)view
{
    for (NSString *streamID in self.viewContainersDict)
    {
        if (self.viewContainersDict[streamID] == view)
            return streamID;
    }
    
    return nil;
}

- (void)exitFullScreen:(NSString *)streamID
{
    BOOL isLandscape = UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation]);
    
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
    if (isLandscape)
    {
        [[ZegoDemoHelper api] setViewRotation:90 ofStream:streamID];
    }
    else
    {
        [[ZegoDemoHelper api] setViewRotation:0 ofStream:streamID];
    }
    self.videoSizeDict[streamID] = @(NO);
}

- (void)enterFullScreen:(NSString *)streamID
{
    BOOL isLandscape = UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation]);
    
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
    if (isLandscape)
    {
        [[ZegoDemoHelper api] setViewRotation:0 ofStream:streamID];
    }
    else
    {
        [[ZegoDemoHelper api] setViewRotation:90 ofStream:streamID];
    }
    self.videoSizeDict[streamID] = @(YES);
}

#pragma mark transition view
- (void)setRotateFromInterfaceOrientation:(UIInterfaceOrientation)orientation
{
    for (NSString *streamID in self.viewContainersDict.allKeys)
    {
        int rotate = 0;
        switch (orientation)
        {
            case UIInterfaceOrientationPortrait:
                rotate = 0;
                break;
                
            case UIInterfaceOrientationPortraitUpsideDown:
                rotate = 180;
                break;
                
            case UIInterfaceOrientationLandscapeLeft:
                rotate = 270;
                break;
                
            case UIInterfaceOrientationLandscapeRight:
                rotate = 90;
                break;
                
            default:
                return;
        }
        
//        [[ZegoDemoHelper api] setViewRotation:rotate ofStream:streamID];
//        [[ZegoDemoHelper api] setViewRotation:0 ofStream:streamID];
//        [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
    }
}

- (void)changeFirstViewContent
{
    UIView *view = [self getFirstViewInContainer:self.playViewContainer];
    NSString *streamID = [self getStreamIDFromView:view];
    if (streamID == nil)
        return;
    
    id info = self.videoSizeDict[streamID];
    if (info == nil)
        return;
    
    BOOL isfull = [info boolValue];
    if (isfull)
    {
        [self exitFullScreen:streamID];
        [self onEnterFullScreenButton:nil];
    }
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
    
    [coordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
        UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
        [self setRotateFromInterfaceOrientation:orientation];
        [self changeFirstViewContent];
        
    } completion:nil];
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [super willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
    
    [self setRotateFromInterfaceOrientation:toInterfaceOrientation];
    [self changeFirstViewContent];
}

#pragma mark -- Media side info

static int mediaSeq = 0;
void onReceivedMediaSideInfo(const char *pszStreamID, const unsigned char* buf, int dataLen) {
    if (dataLen == 0) {
        NSLog(@"onReceivedMediaSideInfo data is empty");
        return;
    }
    
    NSString *streamID = [NSString stringWithCString:pszStreamID encoding:NSUTF8StringEncoding];
    NSData *mediaInfo = [NSData dataWithBytes:buf + 4 length:dataLen - 4];
    NSError *error = nil;
    NSDictionary *info = [NSJSONSerialization JSONObjectWithData:mediaInfo options:0 error:&error];
    
    if (error == nil) {
        int seq = [info[@"seq"] intValue];
        if (seq <= mediaSeq) {
            NSLog(@"onReceivedMediaSideInfo repeat seq %d, discard", seq);
            return;
        }

        mediaSeq = seq;
        NSLog(@"onReceivedMediaSideInfo type %@, id %@, title %@, options: %@", info[@"type"], info[@"id"], info[@"title"], info[@"options"]);
        
        NSString *options = info[@"options"];
        NSArray *optionArray = [options componentsSeparatedByString:@"|"];
        NSMutableArray *optionSorted = [[NSMutableArray alloc] initWithCapacity:[optionArray count]];
        
        // FIXME: 这里要改，赶时间临时这么写
        for (NSString *item in optionArray) {
            if ([item hasPrefix:@"A"]) {
                optionSorted[0] = item;
            } else if ([item hasPrefix:@"B"]) {
                optionSorted[1] = item;
            } else if ([item hasPrefix:@"C"]){
                optionSorted[2] = item;
            } else if ([item hasPrefix:@"D"]){
                optionSorted[3] = item;
            }
        }
        
        if ([info[@"type"] isEqualToString:@"question"]) {
            [selfObject showAlert:info[@"title"] title:info[@"type"] options:optionSorted];
        } else if ([info[@"type"] isEqualToString:@"answer"]) {
            NSLog(@"onReceivedMediaSideInfo type answer, don't handle");
            // id, type
        } else if ([info[@"type"] isEqualToString:@"sum"]) {
            NSLog(@"onReceivedMediaSideInfo type sum, don't handle");
            // type
        } else {
            NSLog(@"onReceivedMediaSideInfo unknown type, don't handle");
        }
        
    }
}


#pragma mark - ZegoLiveRoom
- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
    [[ZegoDemoHelper api] setPlayerDelegate:self];
    [[ZegoDemoHelper api] setPublisherDelegate:self];
    [[ZegoDemoHelper api] setIMDelegate:self];
    [[ZegoDemoHelper api] setMediaSideCallback:onReceivedMediaSideInfo];

}

- (void)loginRoom
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)];
    [self addLogString:logString];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID role:ZEGO_AUDIENCE withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        NSLog(@"%s, error: %d", __func__, errorCode);
        if (errorCode == 0)
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
            [self addLogString:logString];
            
            self.loginRoomSuccess = YES;
            
            if (streamList.count == 0)
                return;
            
            for (ZegoStream *stream in streamList)
            {
                NSDictionary *dict = [self decodeJSONToDictionary:stream.extraInfo];
                if (dict == nil)
                    continue;
                
                if ([dict[@"first"] boolValue] == YES)
                {
                    self.sharedHls = dict[kHlsKey];
                    self.sharedRtmp = dict[kRtmpKey];
                    
                    self.sharedButton.enabled = YES;
                    break;
                }
            }
            
            // 更新流播放列表，包括新增流、删除流
            NSMutableArray *newStreamList = [streamList mutableCopy];
            for (int i = (int)newStreamList.count - 1; i >= 0; i--) {
                for (int j = (int)self.originStreamList.count - 1; j >= 0; j--) {
                    ZegoStream *newStream = newStreamList[i];
                    ZegoStream *old = self.originStreamList[j];
                    if ([newStream.streamID isEqualToString:old.streamID]) {
                        
                        [self.streamList removeObject:old];
                        [self.streamList addObject:newStream];
                        
                        [newStreamList removeObject:newStream];
                        break;
                    }
                }
            }
            if (newStreamList.count) {
                for (ZegoStream *stream in newStreamList) {
                    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录成功后新增流. 流ID: %@", nil), stream.streamID];
                    [self addLogString:logString];
                }
                [self onStreamUpdateForAdd:newStreamList];
            } else {
                NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录成功后没有新增的流", nil)];
                [self addLogString:logString];
            }
            
            for (int i = (int)self.originStreamList.count - 1; i >= 0; i--) {
                for (int j = (int)streamList.count - 1; j >= 0; j--) {
                    ZegoStream *newStream = streamList[j];
                    ZegoStream *old = self.originStreamList[i];
                    if ([newStream.streamID isEqualToString:old.streamID]) {
                        [self.originStreamList removeObject:old];
                        break;
                    }
                }
            }
            if (self.originStreamList.count) {
                for (ZegoStream *stream in self.originStreamList) {
                    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录成功后删除流. 流ID: %@", nil), stream.streamID];
                    [self addLogString:logString];
                }
                [self onStreamUpdateForDelete:self.originStreamList];
            } else {
                NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录成功后没有删除的流", nil)];
                [self addLogString:logString];
            }
        }
        else
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间失败. error: %d", nil), errorCode];
            [self addLogString:logString];
            
            self.loginRoomSuccess = NO;
            
            [self onStreamUpdateForDelete:self.originStreamList];
            [self showNoLivesAlert];
        }
    }];
}

// 秒开播
- (void)playStreamEnteringRoom {
    for (NSString *streamId in self.streamIdList) {
        ZegoStream *stream = [[ZegoStream alloc] init];
        stream.streamID = streamId;
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"直播观看秒开. 流ID: %@", nil), stream.streamID];
        [self addLogString:logString];
        [self.originStreamList addObject:stream];
    }
    [self onStreamUpdateForAdd:self.originStreamList];
}

- (void)createPublishStream
{
    self.publishTitle = [NSString stringWithFormat:@"Hello-%@", [ZegoSettings sharedInstance].userName];
    NSString *streamID = [ZegoDemoHelper getPublishStreamID];
    
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"创建流成功, streamID:%@", nil), streamID];
    [self addLogString:logString];
    
    //创建发布view
    UIView *publishView = [self createPublishView:streamID];
    if (publishView)
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始发布直播", nil)];
        [self addLogString:logString];
        
        [self setAnchorConfig:publishView];
        
        //开启双声道直播
        [[ZegoDemoHelper api] setAudioChannelCount:2];
        
        [[ZegoDemoHelper api] startPublishing:streamID title:self.publishTitle flag:ZEGO_JOIN_PUBLISH];
    }
    else
    {
        self.publishButton.enabled = YES;
    }
}

#pragma mark - ZegoRoomDelegate

- (void)onTempBroken:(int)errorCode roomID:(NSString *)roomID {
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"与服务器连接临时断开, error: %d", nil), errorCode];
    [self addLogString:logString];
    
    self.toolViewController.joinLiveButton.enabled = NO;
}

- (void)onReconnect:(int)errorCode roomID:(NSString *)roomID {
    self.toolViewController.joinLiveButton.enabled = YES;
}

- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"连接失败, error: %d", nil), errorCode];
    [self addLogString:logString];
}

- (void)onKickOut:(int)reason roomID:(NSString *)roomID
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:NSLocalizedString(@"被踢出房间", nil) delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alertView show];
    
    [self onCloseButton:nil];
}

- (void)onStreamUpdated:(int)type streams:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    if (type == ZEGO_STREAM_ADD)
        [self onStreamUpdateForAdd:streamList];
    else if (type == ZEGO_STREAM_DELETE)
        [self onStreamUpdateForDelete:streamList];
}

- (void)onStreamExtraInfoUpdated:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    for (ZegoStream *stream in streamList)
    {
        for (ZegoStream *stream1 in self.streamList)
        {
            if (stream.streamID == stream1.streamID)
            {
                stream1.extraInfo = stream.extraInfo;
                break;
            }
        }
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

- (void)onVideoSizeChangedTo:(CGSize)size ofStream:(NSString *)streamID
{
    NSLog(@"%s, streamID %@", __func__, streamID);
    
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"第一帧画面, 流ID:%@", nil), streamID];
    [self addLogString:logString];
    
    if (self.optionButton.alpha == 0)
    {
        [self setButtonHidden:NO];
        [self setBackgroundImage:nil playerView:self.playViewContainer];
    }
    
    UIView *view = self.viewContainersDict[streamID];
    if (view)
        [self setBackgroundImage:nil playerView:view];
    
    if ([self.publishStreamID isEqualToString:streamID])
        return;
    
    if ([self isStreamIDExist:streamID] && view)
    {
        if (size.width > size.height && view.frame.size.width < view.frame.size.height)
        {
            [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
            
            self.videoSizeDict[streamID] = @(NO);
            
            if (CGRectEqualToRect(view.frame, self.playViewContainer.bounds))
                self.fullscreenButton.hidden = NO;
        }
        
        self.streamID2SizeDict[streamID] = [NSValue valueWithCGSize:size];
    }
}

- (void)onPlayQualityUpate:(NSString *)streamID quality:(ZegoApiPlayQuality)quality
{
    NSString *detail = [self addStaticsInfo:NO stream:streamID fps:quality.fps kbs:quality.kbps akbs:quality.akbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
    
    UIView *view = self.viewContainersDict[streamID];
    if (view)
        [self updateQuality:quality.quality detail:detail onView:view];
}

- (void)onEndJoinLiveCommad:(NSString *)fromUserId userName:(NSString *)fromUserName roomID:(NSString *)roomID
{
    if (self.isPublishing)
    {
        [self stopPublishing];
        
        self.isPublishing = NO;
        self.publishButton.enabled = YES;
        [self.publishButton setTitle:NSLocalizedString(@"请求连麦", nil) forState:UIControlStateNormal];
        self.optionButton.enabled = NO;
    }
}

// 观众端收到主播端的邀请连麦请求
- (void)onInviteJoinLiveRequest:(int)seq fromUserID:(NSString *)userId fromUserName:(NSString *)userName roomID:(NSString *)roomID {
    if (seq == 0 || userId.length == 0)
        return;
    
    [self onReceiveRequestJoinLive:userId userName:userName seq:seq];
}

// 观众端响应邀请连麦请求
- (void)sendInviteRequestRespond:(BOOL)agreed seq:(int)seq requestPublisher:(ZegoUser *)requestUser {
    BOOL success = [[ZegoDemoHelper api] respondInviteJoinLiveReq:seq result:(agreed == false)];
    if (success && agreed) {
        [self createPublishStream];
    }
}

#pragma mark - ZegoLivePublisherDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%s, stream: %@", __func__, streamID);

    if (stateCode == 0)
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播成功,流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        //记录当前的发布信息
        self.isPublishing = YES;
        self.publishButton.enabled = YES;
        [self.publishButton setTitle:NSLocalizedString(@"停止直播", nil) forState:UIControlStateNormal];
        self.publishStreamID = streamID;
        self.optionButton.enabled = YES;
        
        NSString *sharedHls = [info[kZegoHlsUrlListKey] firstObject];
        NSString *sharedRtmp = [info[kZegoRtmpUrlListKey] firstObject];
        
        if (sharedHls.length > 0 && sharedRtmp.length > 0)
        {
            NSDictionary *dict = @{kFirstAnchor: @(NO), kHlsKey: sharedHls, kRtmpKey: sharedRtmp};
            NSString *jsonString = [self encodeDictionaryToJSON:dict];
            if (jsonString)
                [[ZegoDemoHelper api] updateStreamExtraInfo:jsonString];
        }
    }
    else
    {
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
        self.isPublishing = NO;
        self.publishButton.enabled = YES;
        [self.publishButton setTitle:NSLocalizedString(@"请求连麦", nil) forState:UIControlStateNormal];
        //    self.publishStreamID = nil;
        self.optionButton.enabled = NO;
        //删除publish的view
        [self removeStreamViewContainer:streamID];
    }
}

- (void)onAuxCallback:(void *)pData dataLen:(int *)pDataLen sampleRate:(int *)pSampleRate channelCount:(int *)pChannelCount
{
    [self auxCallback:pData dataLen:pDataLen sampleRate:pSampleRate channelCount:pChannelCount];
}

- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality
{
    NSString *detail = [self addStaticsInfo:YES stream:streamID fps:quality.fps kbs:quality.kbps akbs:quality.akbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
    
    UIView *view = self.viewContainersDict[streamID];
    if (view) {
        [self updateQuality:quality.quality detail:detail onView:view];
    }
}

#pragma mark - ZegoIMDelegate

- (void)onUserUpdate:(NSArray<ZegoUserState *> *)userList updateType:(ZegoUserUpdateType)type
{
    for (ZegoUserState *state in userList)
    {
        if (state.role == ZEGO_ANCHOR && state.updateFlag == ZEGO_USER_DELETE)
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"主播已退出：%@", nil), state.userName];
            [self addLogString:logString];
            
            [self showNoAnchorAlert];
            break;
        }
    }
}

- (void)onRecvRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoRoomMessage *> *)messageList
{
    [self.toolViewController updateLayout:messageList];
}

- (BOOL)shouldShowPublishAlert
{
    if (self.viewContainersDict.count < self.maxStreamCount)
        return YES;
    
    return NO;
}

#pragma mark - alert
- (void)showNoLivesAlert
{
    if ([self isDeviceiOS7])
    {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:NSLocalizedString(@"主播已退出", nil) delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alertView show];
    }
    else
    {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"" message:NSLocalizedString(@"主播已退出", nil) preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            [self onCloseButton:nil];
        }];
        
        [alertController addAction:okAction];
        
        [self presentViewController:alertController animated:YES completion:nil];
    }
}

- (void)showNoAnchorAlert
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"提示"
                                                                             message:@"主播已退出，请前往其他房间观看直播"
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定"
                                                     style:UIAlertActionStyleDefault
                                                   handler:^(UIAlertAction * _Nonnull action) {
                                                       [self onCloseButton:nil];
    }];
    
    [alertController addAction:confirm];
    [self presentViewController:alertController animated:YES completion:nil];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [self onCloseButton:nil];
}

- (void)showAlert:(NSString *)message title:(NSString *)title options:(NSArray *)options {
    if (!options.count) {
        NSLog(@"options count is 0");
        return;
    }
    
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                             message:message
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    for (int i = 0; i < options.count; i++) {
        UIAlertAction *action = [UIAlertAction actionWithTitle:NSLocalizedString(options[i], nil)
                                                         style:UIAlertActionStyleDefault
                                                       handler:^(UIAlertAction * _Nonnull action) {
                                                           
                                                       }];
        [alertController addAction:action];
    }
    [self presentViewController:alertController animated:YES completion:nil];
}

#pragma mark stream add & delete
- (BOOL)isStreamIDExist:(NSString *)streamID
{
    if ([self.publishStreamID isEqualToString:streamID])
        return YES;
    
    for (ZegoStream *info in self.streamList)
    {
        if ([info.streamID isEqualToString:streamID])
            return YES;
    }
    
    return NO;
}

- (void)onTapView:(UIView *)view
{
    if (view == nil)
        return;
    
    [self updateContainerConstraintsForTap:view containerView:self.playViewContainer];
    
    UIView *firstView = [self getFirstViewInContainer:self.playViewContainer];
    NSString *streamID = [self getStreamIDFromView:firstView];
    if (streamID == nil)
        return;
    
    id info = self.videoSizeDict[streamID];
    if (info == nil)
    {
        self.fullscreenButton.hidden = YES;
    }
    else
    {
        self.fullscreenButton.hidden = NO;
    }
}

- (void)addStreamViewContainer:(NSString *)streamID
{
    if (streamID.length == 0)
        return;
    
    if (self.viewContainersDict[streamID] != nil)
        return;
    
    UIView *bigView = [[UIView alloc] init];
    bigView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:bigView];
    
    BOOL bResult = [self setContainerConstraints:bigView containerView:self.playViewContainer viewCount:self.viewContainersDict.count];
    if (bResult == NO)
    {
        [bigView removeFromSuperview];
        return;
    }
    
    UIImage *backgroundImage = [[ZegoSettings sharedInstance] getBackgroundImage:self.view.bounds.size withText:NSLocalizedString(@"加载中", nil)];
    [self setBackgroundImage:backgroundImage playerView:bigView];
    
    self.viewContainersDict[streamID] = bigView;
    bool ret = [[ZegoDemoHelper api] startPlayingStream:streamID inView:bigView];
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
    assert(ret);
}

- (void)removeStreamViewContainer:(NSString *)streamID
{
    if (streamID.length == 0)
        return;
    
    UIView *view = self.viewContainersDict[streamID];
    if (view == nil)
        return;
    
    [self updateContainerConstraintsForRemove:view containerView:self.playViewContainer];
    
    [self.viewContainersDict removeObjectForKey:streamID];
}

- (void)removeStreamInfo:(NSString *)streamID
{
    NSInteger index = NSNotFound;
    for (ZegoStream *info in self.streamList)
    {
        if ([info.streamID isEqualToString:streamID])
        {
            index = [self.streamList indexOfObject:info];
            break;
        }
    }
    
    if (index != NSNotFound)
        [self.streamList removeObjectAtIndex:index];
}

- (void)onStreamUpdateForAdd:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        NSString *streamID = stream.streamID;
        if (streamID.length == 0)
            continue;
        
        if ([self isStreamIDExist:streamID])
            continue;
        
        if (self.viewContainersDict.count >= self.maxStreamCount)
            return;
        
        [self.streamList addObject:stream];
        [self addStreamViewContainer:streamID];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"新增一条流, 流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        if (self.viewContainersDict.count >= self.maxStreamCount)
        {
            if (!self.isPublishing)
                self.publishButton.enabled = NO;
        }
        else
            self.publishButton.enabled = YES;
    }
}

- (void)onStreamUpdateForDelete:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        NSString *streamID = stream.streamID;
        if (streamID.length == 0)
            continue;
        
        if (![self isStreamIDExist:streamID])
            continue;
        
        [[ZegoDemoHelper api] stopPlayingStream:streamID];
        
        [self removeStreamViewContainer:streamID];
        [self removeStreamInfo:streamID];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"删除一条流, 流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        if (self.viewContainersDict.count < self.maxStreamCount)
            self.publishButton.enabled = YES;
        else
        {
            if (!self.isPublishing)
                self.publishButton.enabled = NO;
        }
        
        if (self.viewContainersDict.count == 0)
            self.publishButton.enabled = NO;
    }
}

- (UIView *)createPublishView:(NSString *)streamID
{
    if (streamID.length == 0)
        return nil;
    
    UIView *publishView = [[UIView alloc] init];
    publishView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:publishView];
    
    BOOL bResult = [self setContainerConstraints:publishView containerView:self.playViewContainer viewCount:self.viewContainersDict.count];
    if (bResult == NO)
    {
        [publishView removeFromSuperview];
        return nil;
    }
    
    self.viewContainersDict[streamID] = publishView;
    [self.playViewContainer bringSubviewToFront:publishView];
    
    return publishView;
}

#pragma mark onClose action

- (void)stopPublishing
{
    if (self.isPublishing)
    {
        [[ZegoDemoHelper api] stopPreview];
        [[ZegoDemoHelper api] setPreviewView:nil];
        [[ZegoDemoHelper api] stopPublishing];
        [self removeStreamViewContainer:self.publishStreamID];
    }
}

- (void)clearAllStream
{
    for (ZegoStream *info in self.streamList)
    {
        [[ZegoDemoHelper api] stopPlayingStream:info.streamID];
        UIView *playView = self.viewContainersDict[info.streamID];
        if (playView)
        {
            [self updateContainerConstraintsForRemove:playView containerView:self.playViewContainer];
            [self.viewContainersDict removeObjectForKey:info.streamID];
        }
    }
    
    [self stopPublishing];
    
    [self.viewContainersDict removeAllObjects];
}

#pragma mark - ZegoLiveToolViewControllerDelegate
- (void)onCloseButton:(id)sender
{
    [self setBackgroundImage:nil playerView:self.playViewContainer];
    
    [self clearAllStream];
    
    if (self.loginRoomSuccess)
        [[ZegoDemoHelper api] logoutRoom];
    
    if ([ZegoDemoHelper recordTime])
    {
        [self.toolViewController stopTimeRecord];
    }
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)onOptionButton:(id)sender
{
    [self showPublishOption];
}

- (void)onJoinLiveButton:(id)sender
{
    if (self.isPublishing)
    {
        [self stopPublishing];
        
        self.isPublishing = NO;
        self.publishButton.enabled = YES;
        [self.publishButton setTitle:NSLocalizedString(@"请求连麦", nil) forState:UIControlStateNormal];
        self.optionButton.enabled = NO;
    }
    else if ([[self.publishButton currentTitle] isEqualToString:NSLocalizedString(@"请求连麦", nil)])
    {
        bool success = [[ZegoDemoHelper api] requestJoinLive:^(int result, NSString *fromUserID, NSString *fromUserName) {
            NSString *logString = nil;
            if (result != 0)
            {
                [self requestPublishResultAlert:fromUserName];
                self.publishButton.enabled = YES;
                logString = [NSString stringWithFormat:NSLocalizedString(@"有主播拒绝请求连麦", nil)];
            }
            else
            {
                logString = [NSString stringWithFormat:NSLocalizedString(@"有主播同意了你的请求", nil)];
                [self createPublishStream];
            }
            [self addLogString:logString];
        }];
        
        assert(success);

        self.publishButton.enabled = NO;
    }
}

- (void)onMutedButton:(id)sender
{
    if (self.enableSpeaker)
    {
        self.enableSpeaker = NO;
        [self.mutedButton setTitleColor:[UIColor redColor] forState:UIControlStateNormal];
    }
    else
    {
        self.enableSpeaker = YES;
        [self.mutedButton setTitleColor:self.defaultButtonColor forState:UIControlStateNormal];
    }
}

- (void)onLogButton:(id)sender
{
    [self showLogViewController];
}

- (void)onShareButton:(id)sender
{
    if (self.streamList.count == 0)
        return;
    
    BOOL found = NO;
    for (ZegoStream *stream in self.streamList)
    {
        NSDictionary *dict = [self decodeJSONToDictionary:stream.extraInfo];
        if (dict == nil)
            continue;
        
        if ([dict[@"first"] boolValue] == YES)
        {
            [self shareToQQ:dict[kHlsKey] rtmp:dict[kRtmpKey] bizToken:nil bizID:self.roomID streamID:stream.streamID];
            break;
        }
    }
    
    if (found == NO)
    {
        ZegoStream *stream = [self.streamList firstObject];
        NSDictionary *dict = [self decodeJSONToDictionary:stream.extraInfo];
        if (dict)
            [self shareToQQ:dict[kHlsKey] rtmp:dict[kRtmpKey] bizToken:nil bizID:self.roomID streamID:stream.streamID];
    }
}

- (void)onEnterFullScreenButton:(id)sender
{
    UIView *view = [self getFirstViewInContainer:self.playViewContainer];
    NSString *streamID = [self getStreamIDFromView:view];
    if (streamID == nil)
        return;
    
    id info = self.videoSizeDict[streamID];
    if (info == nil)
        return;
    
    BOOL isfull = [info boolValue];
    if (isfull)
    {
        //退出全屏
        [self exitFullScreen:streamID];
        [self.fullscreenButton setTitle:NSLocalizedString(@"进入全屏", nil) forState:UIControlStateNormal];
    }
    else
    {
        //进入全屏
        [self enterFullScreen:streamID];
        [self.fullscreenButton setTitle:NSLocalizedString(@"退出全屏", nil) forState:UIControlStateNormal];
    }
}

- (void)onSendComment:(NSString *)comment
{
    bool ret = [[ZegoDemoHelper api] sendRoomMessage:comment type:ZEGO_TEXT category:ZEGO_CHAT priority:ZEGO_DEFAULT completion:nil];
    if (ret)
    {
        ZegoRoomMessage *roomMessage = [ZegoRoomMessage new];
        roomMessage.fromUserId = [ZegoSettings sharedInstance].userID;
        roomMessage.fromUserName = [ZegoSettings sharedInstance].userName;
        roomMessage.content = comment;
        roomMessage.type = ZEGO_TEXT;
        roomMessage.category = ZEGO_CHAT;
        roomMessage.priority = ZEGO_DEFAULT;
        
        [self.toolViewController updateLayout:@[roomMessage]];
    }
}

- (void)onSendLike
{
    //    [[ZegoDemoHelper api] likeAnchor:1 count:10];
    NSDictionary *likeDict = @{@"likeType": @(1), @"likeCount": @(10)};
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:likeDict options:0 error:nil];
    NSString *content = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    
    bool ret = [[ZegoDemoHelper api] sendRoomMessage:content type:ZEGO_TEXT category:ZEGO_LIKE priority:ZEGO_DEFAULT completion:nil];
    if (ret)
    {
        ZegoRoomMessage *roomMessage = [ZegoRoomMessage new];
        roomMessage.fromUserId = [ZegoSettings sharedInstance].userID;
        roomMessage.fromUserName = [ZegoSettings sharedInstance].userName;
        roomMessage.content = @"点赞了主播";
        roomMessage.type = ZEGO_TEXT;
        roomMessage.category = ZEGO_CHAT;
        roomMessage.priority = ZEGO_DEFAULT;
        
        [self.toolViewController updateLayout:@[roomMessage]];
    }
}

- (void)onTapViewPoint:(CGPoint)point
{
    CGPoint containerPoint = [self.view.window convertPoint:point toView:self.playViewContainer];
    
    for (UIView *view in self.playViewContainer.subviews)
    {
        if (CGRectContainsPoint(view.frame, containerPoint) &&
            !CGSizeEqualToSize(self.playViewContainer.bounds.size, view.frame.size))
        {
            [self onTapView:view];
            break;
        }
    }
}


@end
