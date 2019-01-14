//
//  ZegoMixStreamAudienceViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/27.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoMixStreamAudienceViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoLiveToolViewController.h"


@interface ZegoMixStreamAudienceViewController () <ZegoRoomDelegate, ZegoLivePlayerDelegate, ZegoLivePublisherDelegate, ZegoIMDelegate, UIAlertViewDelegate, ZegoLiveToolViewControllerDelegate>

@property (weak, nonatomic) IBOutlet UIView *playViewContainer;

@property (nonatomic, weak) ZegoLiveToolViewController *toolViewController;

@property (weak, nonatomic) UIButton *publishButton;
@property (weak, nonatomic) UIButton *optionButton;
@property (weak, nonatomic) UIButton *mutedButton;
@property (weak, nonatomic) UIButton *fullscreenButton;
@property (nonatomic, weak) UIButton *sharedButton;

@property (nonatomic, strong) NSMutableArray<ZegoStream *> *streamList; // 单流信息列表
@property (nonatomic, strong) NSMutableArray<ZegoStream *> *originStreamList;   // 直播秒开流列表

@property (nonatomic, assign) BOOL loginRoomSuccess;

@property (nonatomic, assign) BOOL isPublishing;
@property (nonatomic, copy) NSString *publishTitle;
@property (nonatomic, copy) NSString *publishStreamID;  // 发布流ID

@property (nonatomic, strong) UIColor *defaultButtonColor;

@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;
@property (nonatomic, strong) NSMutableDictionary *streamID2SizeDict;
@property (nonatomic, strong) NSMutableDictionary *videoSizeDict;

@property (nonatomic, copy) NSString *mixStreamID;  // 混流ID
@property (nonatomic, copy) NSString *anchorStreamID;

@property (nonatomic, strong) NSMutableArray<ZegoStream *> *mixStreamList; // 混流信息列表
@property (nonatomic, strong) UIView *mixStreamPlayView;

@property (nonatomic, copy) NSString *sharedHls;
@property (nonatomic, copy) NSString *sharedRtmp;

@end

@implementation ZegoMixStreamAudienceViewController

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
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
    
    self.optionButton = self.toolViewController.joinLiveOptionButton; // 观众直播界面的，直播设置button
    self.publishButton = self.toolViewController.joinLiveButton; // 请求连麦button
    self.mutedButton = self.toolViewController.playMutedButton;
    self.fullscreenButton = self.toolViewController.fullScreenButton;
    self.sharedButton = self.toolViewController.shareButton;
    
    _streamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    _viewContainersDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _videoSizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _streamID2SizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _mixStreamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    _originStreamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    
    [self setupLiveKit];
    [self loginRoom];
    
//    UIImage *backgroundImage = [[ZegoSettings sharedInstance] getBackgroundImage:self.view.bounds.size withText:NSLocalizedString(@"加载中", nil)];
//    [self setBackgroundImage:backgroundImage playerView:self.playViewContainer];
    
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

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Private methods

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

- (void)setBackgroundImage:(UIImage *)image playerView:(UIView *)playerView
{
    playerView.backgroundColor = [UIColor colorWithPatternImage:image];
}

// 流ID是否为当前推流的ID，或是否已存在于单流列表中
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

#pragma mark -- Alert

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

#pragma mark -- Add Stream

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

// 新增流时，创建一个新的view播放
- (void)addStreamViewContainer:(NSString *)streamID
{
    if (streamID.length == 0)
        return;
    
    if (self.viewContainersDict[streamID] != nil)
        return;
    
    UIView *bigView = [[UIView alloc] init];
    bigView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:bigView];
    
    BOOL bResult = [self setContainerConstraints:bigView
                                   containerView:self.playViewContainer
                                       viewCount:self.viewContainersDict.count];
    if (bResult == NO)
    {
        [bigView removeFromSuperview];
        return;
    }
    
    UIImage *backgroundImage = [[ZegoSettings sharedInstance] getBackgroundImage:self.view.bounds.size withText:NSLocalizedString(@"加载中", nil)];
    [self setBackgroundImage:backgroundImage playerView:bigView];
    
    self.viewContainersDict[streamID] = bigView;
    
    bool ret = [[ZegoDemoHelper api] startPlayingStream:streamID inView:bigView];
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFill ofStream:streamID];
    [[ZegoDemoHelper api] setViewRotation:0 ofStream:streamID];
    
    assert(ret);
}

#pragma mark -- Delete stream 

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
    
    [self.viewContainersDict removeAllObjects];
    
    if (self.isPublishing) // 正在连麦中
    {
        [[ZegoDemoHelper api] stopPreview];
        [[ZegoDemoHelper api] setPreviewView:nil];
        [[ZegoDemoHelper api] stopPublishing];
        [self removeStreamViewContainer:self.publishStreamID];
    }
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

#pragma mark -- Play and stop mix stream

- (void)playMixStream:(NSArray *)streamList
{
    NSString *mixStream;
    NSString *anchorStream;
    
    for (ZegoStream *stream in streamList)
    {
        NSDictionary *dict = [self decodeJSONToDictionary:stream.extraInfo];
        if (dict == nil)
            continue;
        
        if (dict[kMixStreamID] != nil)
        {
            mixStream = dict[kMixStreamID];
            anchorStream = stream.streamID;
            
            self.sharedHls = dict[kHlsKey];
            self.sharedRtmp = dict[kRtmpKey];
            if (self.sharedHls && self.sharedRtmp)
                self.sharedButton.enabled = YES;
            
            break;
        }
    }
    
    if (mixStream == nil)
        return;
    
    self.mixStreamID = mixStream;
    self.anchorStreamID = anchorStream;
    
    if (self.streamList.count < self.maxStreamCount)
        self.publishButton.enabled = YES;
    
    //create playView
    self.mixStreamPlayView = [[UIView alloc] init];
    self.mixStreamPlayView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:self.mixStreamPlayView];
    
    BOOL bResult = [self setContainerConstraints:self.mixStreamPlayView containerView:self.playViewContainer viewCount:self.viewContainersDict.count];
    if (bResult == NO)
    {
        [self.mixStreamPlayView removeFromSuperview];
        return;
    }
    
    self.mixStreamPlayView.frame = self.playViewContainer.bounds;
    [self.playViewContainer bringSubviewToFront:self.mixStreamPlayView];
    
//    self.viewContainersDict[self.mixStreamID] = self.mixStreamPlayView;
    
    //play mixStream
    [[ZegoDemoHelper api] startPlayingStream:self.mixStreamID inView:self.mixStreamPlayView];
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:self.mixStreamID];
    
}

- (void)stopPlayMixStream:(NSArray *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        if ([self.anchorStreamID isEqualToString:stream.streamID])
        {
            [[ZegoDemoHelper api] stopPlayingStream:self.mixStreamID];
            [self.mixStreamPlayView removeFromSuperview];
            self.mixStreamPlayView = nil;
            break;
        }
    }
}


#pragma mark -- FullScreen

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

#pragma mark -- Transition

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
        
    } completion:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
    }];
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [super willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
    
    [self setRotateFromInterfaceOrientation:toInterfaceOrientation];
    [self changeFirstViewContent];
}

#pragma mark - ZegoLiveRoom

- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
    [[ZegoDemoHelper api] setPlayerDelegate:self];
    [[ZegoDemoHelper api] setPublisherDelegate:self];
    [[ZegoDemoHelper api] setIMDelegate:self];
}

- (void)loginRoom
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)];
    [self addLogString:logString];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID
                               role:ZEGO_AUDIENCE
                withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        NSLog(@"%s, error: %d", __func__, errorCode);
        if (errorCode == 0)
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
            [self addLogString:logString];
            
            self.loginRoomSuccess = YES;
            
            // 停止播放秒播中的单流，拉混流
            [self onStreamUpdateForDelete:self.originStreamList];

            if (streamList.count != 0)
            {
                [self playMixStream:streamList];
                [self.mixStreamList addObjectsFromArray:streamList];
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
    
    // 播放 StreamID
    [self onStreamUpdateForAdd:self.originStreamList];
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
    if (!self.isPublishing && self.mixStreamList != nil) {
        // 未连麦，当前拉混流（观众围观）
        if (type == ZEGO_STREAM_ADD) {
            for (ZegoStream *stream in streamList) {
                NSString *streamID = stream.streamID;
                if (streamID.length == 0) {
                    continue;
                }
            
                if ([self isStreamIDExist:streamID]) {
                    continue;
                }
                
                [self.mixStreamList addObject:stream];
            }
            
            if (self.viewContainersDict.count >= self.maxStreamCount) {
                if (!self.isPublishing) {
                    self.publishButton.enabled = NO;
                }
            } else {
                self.publishButton.enabled = YES;
            }
        } else if (type == ZEGO_STREAM_DELETE) {
            for (ZegoStream *stream in streamList) {
                NSString *streamID = stream.streamID;
                if (streamID.length == 0) {
                    continue;
                }
                
                if ([self isStreamIDExist:streamID]) {
                    continue;
                }
                
                for (ZegoStream *mixStream in self.mixStreamList) {
                    if(mixStream.extraInfo.length > 0 && [mixStream.streamID isEqualToString:stream.streamID]) {
                        [self.mixStreamList removeObject:stream];
                        break;
                    }
                }
            }
            
            [self stopPlayMixStream:streamList];
            
            if (self.mixStreamList.count < self.maxStreamCount) {
                self.publishButton.enabled = YES;
            } else {
                if (!self.isPublishing) {
                    self.publishButton.enabled = NO;
                }
            }
            
            if (self.viewContainersDict.count == 0) {
                self.publishButton.enabled = NO;
            }
        }
    } else {
        if (type == ZEGO_STREAM_ADD) {
            [self onStreamUpdateForAdd:streamList];
        } else if (type == ZEGO_STREAM_DELETE) {
            [self onStreamUpdateForDelete:streamList];
        }
    }
}

- (void)onStreamExtraInfoUpdated:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    NSArray *oldStreamList = nil;
    
    if (self.isPublishing && self.mixStreamList != nil) {
        oldStreamList = self.streamList;
    } else {
        oldStreamList = self.mixStreamList;
    }
    
    for (ZegoStream *newStream in streamList)
    {
        for (ZegoStream *oldStream in oldStreamList)
        {
            if (newStream.streamID == oldStream.streamID)
            {
                oldStream.extraInfo = newStream.extraInfo;
                break;
            }
        }
    }

    if ([self.mixStreamList count]) {
        ZegoStream *stream = self.mixStreamList[0];
        if ([stream.extraInfo isEqualToString:@""]) {
            // 当 loginRoom 成功后返回的 streamList 的 extraInfo 为空时（后台处理慢时可能导致该问题），需要等待本回调返回的、更新后的 streamList 信息播放
            if (streamList && [streamList count] && [roomID isEqualToString: self.roomID]) {
                [self playMixStream:streamList];
            }
        } else {
            [self playMixStream:streamList];
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
        if (size.width > size.height)
        {
            [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
            
            self.videoSizeDict[streamID] = @(NO);
            
//            if (CGRectEqualToRect(view.frame, self.playViewContainer.bounds))
//                self.fullscreenButton.hidden = NO;
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
        
        if (self.mixStreamPlayView)
        {
            //停止拉混流
            [[ZegoDemoHelper api] stopPlayingStream:self.mixStreamID];
            [self.mixStreamPlayView removeFromSuperview];
            self.mixStreamPlayView = nil;
            
            //开始拉单流
            [self onStreamUpdateForAdd:self.mixStreamList];
            [self.mixStreamList removeAllObjects];
        }
        
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
    }
}

- (void)onPublishQualityUpdate:(NSString *)streamID quality:(ZegoApiPublishQuality)quality
{  
    NSString *detail = [self addStaticsInfo:YES stream:streamID fps:quality.fps kbs:quality.kbps akbs:quality.akbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
    
    UIView *view = self.viewContainersDict[streamID];
    if (view)
        [self updateQuality:quality.quality detail:detail onView:view];
}

- (void)onAuxCallback:(void *)pData dataLen:(int *)pDataLen sampleRate:(int *)pSampleRate channelCount:(int *)pChannelCount
{
    [self auxCallback:pData dataLen:pDataLen sampleRate:pSampleRate channelCount:pChannelCount];
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

#pragma mark - UIAlertView delegate

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

#pragma mark - ZegoLiveToolViewControllerDelegate

- (void)onCloseButton:(id)sender
{
    [self setBackgroundImage:nil playerView:self.playViewContainer];
    
    [self clearAllStream];
    
    if ([ZegoDemoHelper recordTime])
    {
        [self.toolViewController stopTimeRecord];
    }
    
    if (self.loginRoomSuccess)
        [[ZegoDemoHelper api] logoutRoom];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)onOptionButton:(id)sender
{
    [self showPublishOption];
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

- (void)onShareButton:(id)sender
{
    if (self.sharedHls.length == 0)
        return;
    
    [self shareToQQ:self.sharedHls rtmp:self.sharedRtmp bizToken:nil bizID:self.roomID streamID:self.mixStreamID];
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

#pragma mark -- Join live

// 点击申请连麦/结束连麦
- (void)onJoinLiveButton:(id)sender
{
    if (self.isPublishing) // 连麦中，停止直播
    {
        [[ZegoDemoHelper api] stopPreview];
        [[ZegoDemoHelper api] setPreviewView:nil];
        [[ZegoDemoHelper api] stopPublishing];
        self.isPublishing = NO;
        self.publishButton.enabled = YES;
        [self.publishButton setTitle:NSLocalizedString(@"请求连麦", nil) forState:UIControlStateNormal];
        self.optionButton.enabled = NO;
        //删除publish的view
        [self removeStreamViewContainer:self.publishStreamID];
        
        //停止拉单流
        [self.mixStreamList addObjectsFromArray:self.streamList];
        [self onStreamUpdateForDelete:self.streamList.copy];
        [self.streamList removeAllObjects];

        //开始拉混流
        [self playMixStream:self.mixStreamList];
    }
    else if ([[self.publishButton currentTitle] isEqualToString:NSLocalizedString(@"请求连麦", nil)]) // 未连麦，点击请求连麦
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

// 连麦成功后，创建新view，播放新增的流
- (void)createPublishStream
{
    self.publishTitle = [NSString stringWithFormat:@"Hello-%@", [ZegoSettings sharedInstance].userName];
    
    NSUInteger currentTime = (NSUInteger)[[NSDate date] timeIntervalSince1970];
    NSString *streamID = [NSString stringWithFormat:@"s-%@-%lu", [ZegoSettings sharedInstance].userID, (unsigned long)currentTime];
    
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"创建流成功, streamID:%@", nil), streamID];
    [self addLogString:logString];
    
    //创建发布view
    UIView *publishView = [self createPublishView:streamID];
    if (publishView)
    {
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始发布直播", nil)];
        [self addLogString:logString];
        
        [self setAnchorConfig:publishView];
        
        //弱网优化
//        [[ZegoDemoHelper api] setLatencyMode:ZEGOAPI_LATENCY_MODE_LOW3];
//        [[ZegoDemoHelper api] setVideoCodecId:VIDEO_CODEC_MULTILAYER ofChannel:ZEGOAPI_CHN_MAIN];
//        [[ZegoDemoHelper api] enableTrafficControl:true properties: (ZEGOAPI_TRAFFIC_CONTROL_BASIC | ZEGOAPI_TRAFFIC_CONTROL_ADAPTIVE_FPS | ZEGOAPI_TRAFFIC_CONTROL_ADAPTIVE_RESOLUTION)];
        [[ZegoDemoHelper api] startPublishing:streamID title:self.publishTitle flag:ZEGO_JOIN_PUBLISH];
    }
    else
    {
        self.publishButton.enabled = YES;
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

#pragma mark -- Tap view to switch

// 点击切换大小窗口
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

- (void)onTapView:(UIView *)view
{
    if (view == nil)
        return;
    
    [self updateContainerConstraintsForTap:view containerView:self.playViewContainer];
    
    UIView *firstView = [self getFirstViewInContainer:self.playViewContainer];
    NSString *streamID = [self getStreamIDFromView:firstView];
    if (streamID == nil)
        return;
    
//    id info = self.videoSizeDict[streamID];
//    if (info == nil)
//    {
//        self.fullscreenButton.hidden = YES;
//    }
//    else
//    {
//        self.fullscreenButton.hidden = NO;
//    }
}

@end
