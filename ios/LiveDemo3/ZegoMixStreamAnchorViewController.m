//
//  ZegoMixStreamAnchorViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/9/9.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoMixStreamAnchorViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoAnchorOptionViewController.h"
#import "ZegoLiveToolViewController.h"

@interface ZegoMixStreamAnchorViewController () <ZegoRoomDelegate, ZegoLivePublisherDelegate, ZegoLivePlayerDelegate, ZegoIMDelegate, ZegoLiveToolViewControllerDelegate>

@property (nonatomic, weak) IBOutlet UIView *playViewContainer; // 播放 View Container
@property (nonatomic, weak) UIButton *stopPublishButton;        // 停止直播 button
@property (nonatomic, weak) UIButton *mutedButton;              // 静音 button
@property (nonatomic, weak) UIButton *sharedButton;             // 分享 button
@property (nonatomic, strong) UIColor *defaultButtonColor;      // 默认 button 颜色
@property (nonatomic, strong) UIColor *disableButtonColor;      // 禁用 button 颜色

@property (nonatomic, weak) ZegoLiveToolViewController *toolViewController;
@property (nonatomic, strong) ZegoUser *mixRequestUser;

@property (nonatomic, copy) NSString *streamID;                 // 流 ID
@property (nonatomic, copy) NSString *mixStreamID;              // 混流 ID
@property (nonatomic, copy) NSString *roomID;                   // 房间 ID
@property (nonatomic, copy) NSString *sharedHls;
@property (nonatomic, copy) NSString *sharedRtmp;
@property (nonatomic, assign) int mixRequestSeq;

@property (nonatomic, assign) BOOL isPlaying;                   // 是否正在拉流
@property (nonatomic, assign) BOOL isPublishing;                // 是否正在推流

@property (nonatomic, strong) NSMutableArray<ZegoStream*> *playStreamList;   // 正在播放的 streamList
@property (nonatomic, strong) NSArray *mixPlayStreamList;
@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;  // 房间内的视图，key 为流 ID

@property (nonatomic, assign) UIInterfaceOrientation orientation;


- (void)updateMixStream;

@end

@implementation ZegoMixStreamAnchorViewController

#pragma mark - Life cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupLiveKit];
    [self loginChatRoom];
    
    _viewContainersDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _playStreamList = [[NSMutableArray alloc] init];
    
    for (UIViewController *viewController in self.childViewControllers)
    {
        if ([viewController isKindOfClass:[ZegoLiveToolViewController class]])
        {
            self.toolViewController = (ZegoLiveToolViewController *)viewController;
            self.toolViewController.delegate = self;
            break;
        }
    }
    
    self.stopPublishButton = self.toolViewController.stopPublishButton;
    self.sharedButton = self.toolViewController.shareButton;
    self.mutedButton = self.toolViewController.mutedButton;
    
    self.stopPublishButton.enabled = NO;
    self.sharedButton.enabled = NO;
    self.mutedButton.enabled = NO;
    
    self.defaultButtonColor = [self.mutedButton titleColorForState:UIControlStateNormal];
    self.disableButtonColor = [self.mutedButton titleColorForState:UIControlStateDisabled];
    
    self.orientation = [UIApplication sharedApplication].statusBarOrientation;
    
    if (self.publishView)
    {
        [self updatePublishView:self.publishView];
    }
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Private methods

- (void)loginChatRoom
{
    self.roomID = [ZegoDemoHelper getMyRoomID:MixStreamRoom];
    self.streamID = [ZegoDemoHelper getPublishStreamID];
    self.mixStreamID = [NSString stringWithFormat:@"%@-mix", self.streamID];
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)]];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID
                           roomName:self.liveTitle
                               role:ZEGO_ANCHOR
                withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
                    NSLog(@"%s, error: %d", __func__, errorCode);
                    if (errorCode == 0)
                    {
                        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
                        [self addLogString:logString];
                        
                        [self doPublish];
                    }
                    else
                    {
                        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间失败. error: %d", nil), errorCode];
                        [self addLogString:logString];
                    }
                }];
}

#pragma mark -- ZegoLiveRoom

- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
    [[ZegoDemoHelper api] setPlayerDelegate:self];
    [[ZegoDemoHelper api] setPublisherDelegate:self];
    [[ZegoDemoHelper api] setIMDelegate:self];
}

- (bool)doPublish
{
    //登录成功后配置直播参数，开始直播 创建publishView
    if (self.publishView.superview == nil)
        self.publishView = nil;
    
    if (self.publishView == nil)
    {
        self.publishView = [self createPublishView];
        if (self.publishView)
        {
            [self setAnchorConfig:self.publishView];
            [[ZegoDemoHelper api] startPreview];
        }
    }
    
    self.viewContainersDict[self.streamID] = self.publishView;
    
//    弱网优化
//    [[ZegoDemoHelper api] setLatencyMode:ZEGOAPI_LATENCY_MODE_LOW3];
//    [[ZegoDemoHelper api] setVideoCodecId:VIDEO_CODEC_MULTILAYER ofChannel:ZEGOAPI_CHN_MAIN];
//    [[ZegoDemoHelper api] enableTrafficControl:true properties: (ZEGOAPI_TRAFFIC_CONTROL_BASIC | ZEGOAPI_TRAFFIC_CONTROL_ADAPTIVE_FPS | ZEGOAPI_TRAFFIC_CONTROL_ADAPTIVE_RESOLUTION)];
    // 发起推流
    bool b = [[ZegoDemoHelper api] startPublishing:self.streamID
                                             title:self.liveTitle
                                              flag:ZEGO_MIX_STREAM];
    
    if (b)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始直播，流ID:%@", nil), self.streamID]];
    }
    return b;
}

#pragma mark -- Publish view

// 创建publishView
- (UIView *)createPublishView
{
    UIView *publishView = [[UIView alloc] init];
    publishView.translatesAutoresizingMaskIntoConstraints = NO;
    
    BOOL result = [self updatePublishView:publishView];
    if (result == NO)
        return nil;
    
    return publishView;
}

- (BOOL)updatePublishView:(UIView *)publishView
{
    publishView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:publishView];
    
    BOOL bResult = [self setContainerConstraints:publishView containerView:self.playViewContainer viewCount:self.playViewContainer.subviews.count - 1];
    if (bResult == NO)
    {
        [publishView removeFromSuperview];
        return NO;
    }
    
    [self.playViewContainer bringSubviewToFront:publishView];
    return YES;
}

- (void)stopPublishing
{
    [[ZegoDemoHelper api] stopPreview];
    [[ZegoDemoHelper api] setPreviewView:nil];
    [[ZegoDemoHelper api] stopPublishing];
    
    [self removeStreamViewContainer:self.streamID];
    self.publishView = nil;
    
    self.isPublishing = NO;
}

- (BOOL)shouldShowPublishAlert
{
    if (self.viewContainersDict.count < self.maxStreamCount)
        return YES;
    
    return NO;
}

#pragma mark -- Add and delete stream

// 新增流处理，streamList中是新增的流
- (void)onStreamUpdateForAdd:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        NSString *streamID = stream.streamID;
        if (streamID.length == 0)
            continue;
        
        if ([self isStreamIDExist:streamID])
        {
            continue;
        }
        
        [self.playStreamList addObject:stream];
        [self createPlayStream:streamID];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"新增一条流, 流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        // 更新流布局配置
        [self updateMixStream];
    }
    
    self.mutedButton.enabled = YES;
}

// 删除流处理
- (void)onStreamUpdateForDelete:(NSArray<ZegoStream *> *)streamList
{
    for (ZegoStream *stream in streamList)
    {
        NSString *streamID = stream.streamID;
        if (![self isStreamIDExist:streamID])
            continue;
        
        [[ZegoDemoHelper api] stopPlayingStream:streamID];
        [self removeStreamViewContainer:streamID];
        [self removeStreamInfo:streamID];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"删除一条流, 流ID:%@", nil), streamID];
        [self addLogString:logString];
    }
    
    // 更新混流配置
    [self updateMixStream];
    
    if (self.playStreamList.count == 0)
    {
        self.mutedButton.enabled = NO;
        [self.mutedButton setTitleColor:self.disableButtonColor forState:UIControlStateDisabled];
    }
}

- (BOOL)isStreamIDExist:(NSString *)streamID
{
    if ([self.streamID isEqualToString:streamID])
        return YES;
    
    for (ZegoStream *info in self.playStreamList)
    {
        if ([info.streamID isEqualToString:streamID])
            return YES;
    }
    
    return NO;
}

- (void)removeStreamInfo:(NSString *)streamID
{
    NSInteger index = NSNotFound;
    for (ZegoStream *info in self.playStreamList)
    {
        if ([info.streamID isEqualToString:streamID])
        {
            index = [self.playStreamList indexOfObject:info];
            break;
        }
    }
    
    if (index != NSNotFound)
        [self.playStreamList removeObjectAtIndex:index];
}

- (void)createPlayStream:(NSString *)streamID
{
    if (self.viewContainersDict[streamID] != nil)
        return;
    
    UIView *playView = [self createPlayView:streamID];
    
    [[ZegoDemoHelper api] startPlayingStream:streamID inView:playView];
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
}

- (UIView *)createPlayView:(NSString *)streamID
{
    UIView *playView = [[UIView alloc] init];
    playView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.playViewContainer addSubview:playView];
    
    BOOL bResult = [self setContainerConstraints:playView containerView:self.playViewContainer viewCount:self.viewContainersDict.count];
    if (bResult == NO)
    {
        [playView removeFromSuperview];
        return nil;
    }
    
    self.viewContainersDict[streamID] = playView;
    [self.playViewContainer bringSubviewToFront:playView];
    
    return playView;
}

- (void)removeStreamViewContainer:(NSString *)streamID
{
    UIView *view = self.viewContainersDict[streamID];
    if (view == nil)
        return;
    
    [self updateContainerConstraintsForRemove:view containerView:self.playViewContainer];
    
    [self.viewContainersDict removeObjectForKey:streamID];
}

- (void)closeAllStream
{
    [[ZegoDemoHelper api] stopPreview];
    [[ZegoDemoHelper api] setPreviewView:nil];
    [[ZegoDemoHelper api] stopPublishing];
    [self removeStreamViewContainer:self.streamID];
    
    self.publishView = nil;
    
    if (self.isPlaying)
    {
        for (ZegoStream *info in self.playStreamList)
        {
            [[ZegoDemoHelper api] stopPlayingStream:info.streamID];
            [self removeStreamViewContainer:info.streamID];
        }
    }
    
    [self.viewContainersDict removeAllObjects];
    
    self.isPublishing = NO;
    self.isPlaying = NO;
}

- (void)updateMixStream
{
    ZegoCompleteMixStreamConfig *completeMixConfig = [ZegoCompleteMixStreamConfig new];
    
    completeMixConfig.outputStream = self.mixStreamID;
    completeMixConfig.outputIsUrl = NO;
    completeMixConfig.outputFps = [ZegoSettings sharedInstance].currentConfig.fps;
    completeMixConfig.outputBitrate = [ZegoSettings sharedInstance].currentConfig.bitrate;
    completeMixConfig.outputResolution = [ZegoSettings sharedInstance].currentConfig.videoEncodeResolution;
    completeMixConfig.outputAudioConfig = 0;   // * default config
    completeMixConfig.outputBackgroundColor = 0xc8c8c800;
    
    int height = [ZegoSettings sharedInstance].currentConfig.videoEncodeResolution.height;
    int width = [ZegoSettings sharedInstance].currentConfig.videoEncodeResolution.width;
    int margin = 0; // 用于展示 outputBackgroundColor，默认不展示背景颜色
    
    if (self.isPublishing)
    {
        ZegoMixStreamInfo *info = [[ZegoMixStreamInfo alloc] init];
        info.streamID = self.streamID;
        info.top = 0 + margin;
        info.left = 0 + margin;
        info.bottom = height - margin;
        info.right = width - margin;
        
        [completeMixConfig.inputStreamList addObject:info];
    }
    
    for (NSInteger idx = 0; idx < self.playStreamList.count; ++idx)
    {
        ZegoMixStreamInfo *info = [[ZegoMixStreamInfo alloc] init];
        info.streamID = self.playStreamList[idx].streamID;
        
        if (completeMixConfig.inputStreamList.count == 0)
        {
            info.top = 0;
            info.left = 0;
            info.bottom = height;
            info.right = width;
        }
        else if (completeMixConfig.inputStreamList.count == 1)
        {
            // 新增第1条流布局
            info.top = ceilf(height * 2 / 3);
            info.left = ceilf(width * 2 / 3);   // 画面左上角坐标为（ceilf(width * 2 / 3), ceilf(height * 2 / 3))
            info.bottom = height;
            info.right = width; // 画面右下角坐标为（width, height)
        }
        else if (completeMixConfig.inputStreamList.count == 2)
        {
            // 新增第2条流布局
            info.top = ceilf(height * 2 / 3);
            info.left = 0;
            info.bottom = height;
            info.right = ceilf(width / 3);
        }
        
        [completeMixConfig.inputStreamList addObject:info];
    }
    
    static int seq = 0;
    
    [[ZegoDemoHelper api] mixStream:completeMixConfig seq:++seq];
}

#pragma mark -- Autorate

- (BOOL)shouldAutorotate
{
    return NO;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    if (self.orientation == UIInterfaceOrientationPortrait)
        return UIInterfaceOrientationMaskPortrait;
    else if (self.orientation == UIInterfaceOrientationLandscapeLeft)
        return UIInterfaceOrientationMaskLandscapeLeft;
    else if (self.orientation == UIInterfaceOrientationLandscapeRight)
        return UIInterfaceOrientationMaskLandscapeRight;
    
    return UIInterfaceOrientationMaskPortrait;
}

#pragma mark - ZegoRoomDelegate

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

// 流信息更新回调
- (void)onStreamUpdated:(int)type streams:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    if (type == ZEGO_STREAM_ADD)    // 新增流
        [self onStreamUpdateForAdd:streamList];
    else if (type == ZEGO_STREAM_DELETE)    // 删除流
        [self onStreamUpdateForDelete:streamList];
}

// 流附加信息更新回调
- (void)onStreamExtraInfoUpdated:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    for (ZegoStream *stream in streamList)
    {
        for (ZegoStream *stream1 in self.playStreamList)
        {
            if (stream.streamID == stream1.streamID)
            {
                stream1.extraInfo = stream.extraInfo;
                break;
            }
        }
    }
}

#pragma mark - ZegoLivePublisherDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%s, stream: %@", __func__, streamID);
    
    if (stateCode == 0)
    {
        self.isPublishing = YES;
        self.stopPublishButton.enabled = YES;
        [self.stopPublishButton setTitle:NSLocalizedString(@"停止直播", nil) forState:UIControlStateNormal];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播成功,流ID:%@", nil), streamID];
        [self addLogString:logString];
    }
    else
    {
        NSLog(@"%s, stream: %@, err: %u", __func__, streamID, stateCode);
        self.isPublishing = NO;
        
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        self.stopPublishButton.enabled = YES;
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"直播结束,流ID：%@, error:%d", nil), streamID, stateCode];
        [self addLogString:logString];
        
        [self removeStreamViewContainer:streamID];
        self.publishView = nil;
    }
    
    [self updateMixStream];
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

- (void)onJoinLiveRequest:(int)seq fromUserID:(NSString *)userId fromUserName:(NSString *)userName roomID:(NSString *)roomID
{
    if (seq == 0 || userId.length == 0)
        return;
    
    [self onReceiveJoinLive:userId userName:userName seq:seq];
}


- (void)onMixStreamConfigUpdate:(int)errorCode mixStream:(NSString *)mixStreamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%s, %@, errorCode %d, info: %@", __func__, mixStreamID, errorCode, info);
    
    if (errorCode != 0)
    {
        self.sharedButton.enabled = NO;
        return;
    }
    
    NSString *rtmpUrl = [info[kZegoRtmpUrlListKey] firstObject];
    NSString *hlsUrl = [info[kZegoHlsUrlListKey] firstObject];
    
    self.sharedHls = hlsUrl;
    self.sharedRtmp = rtmpUrl;
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"混流结果: %d", nil), errorCode]];
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"混流rtmp: %@", nil), rtmpUrl]];
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"混流hls: %@", nil), hlsUrl]];
    
    // 无论 hlsUrl 或 rtmpUrl 是否为空，都去更新混流信息
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    if (self.sharedHls.length > 0) {
        [dict setObject:self.sharedHls forKey:kHlsKey];
    }
    
    if (self.sharedRtmp.length > 0) {
        [dict setObject:self.sharedRtmp forKey:kRtmpKey];
    }
    
    [dict setObject:@(YES) forKey:kFirstAnchor];
    [dict setObject:mixStreamID forKey:kMixStreamID];
    NSString *jsonString = [self encodeDictionaryToJSON:dict];
    if (jsonString)
        [[ZegoDemoHelper api] updateStreamExtraInfo:jsonString];
    
    if (self.sharedHls.length > 0 && self.sharedRtmp.length > 0)
    {
        self.sharedButton.enabled = YES;
    }
    else
    {
        self.sharedButton.enabled = NO;
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
    NSString *detail = [self addStaticsInfo:NO stream:streamID fps:quality.fps kbs:quality.kbps akbs:quality.akbps rtt:quality.rtt pktLostRate:quality.pktLostRate];
    
    UIView *view = self.viewContainersDict[streamID];
    if (view)
        [self updateQuality:quality.quality detail:detail onView:view];
}

- (void)onVideoSizeChangedTo:(CGSize)size ofStream:(NSString *)streamID
{
    if (![self isStreamIDExist:streamID])
        return;
    
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"第一帧画面, 流ID:%@", nil), streamID];
    [self addLogString:logString];
    
    UIView *view = self.viewContainersDict[streamID];
    if (view == nil)
        return;
    
    if (size.width > size.height && view.frame.size.width < view.frame.size.height)
    {
        [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFit ofStream:streamID];
    }
}

#pragma mark - ZegoIMDelegate

- (void)onRecvRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoRoomMessage *> *)messageList
{
    [self.toolViewController updateLayout:messageList];
}


#pragma mark - ZegoLiveToolViewControllerDelegate

- (void)onCloseButton:(id)sender
{
    // 退出时关闭混流
    [[ZegoDemoHelper api] updateMixInputStreams:nil];
    
    [self closeAllStream];
    [[ZegoDemoHelper api] logoutRoom];
    
    [self dismissViewControllerAnimated:YES completion:nil];
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

- (void)onOptionButton:(id)sender
{
    [self showPublishOption];
}

- (void)onLogButton:(id)sender
{
    [self showLogViewController];
}

- (void)onStopPublishButton:(id)sender
{
    if (self.isPublishing)
    {
        [self stopPublishing];
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        self.stopPublishButton.enabled = YES;
    }
    else if ([[self.stopPublishButton currentTitle] isEqualToString:NSLocalizedString(@"开始直播", nil)])
    {
        [self doPublish];
        self.stopPublishButton.enabled = NO;
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
    
    // 横屏时切换坐标，区分方向
    if (self.orientation == UIInterfaceOrientationLandscapeLeft) {
        containerPoint = CGPointMake(self.playViewContainer.frame.size.width - containerPoint.y, containerPoint.x);
    }
    
    if (self.orientation == UIInterfaceOrientationLandscapeRight) {
        containerPoint = CGPointMake(containerPoint.y, self.playViewContainer.frame.size.height - containerPoint.x);
    }
    
    for (UIView *view in self.playViewContainer.subviews)
    {
        if (CGRectContainsPoint(view.frame, containerPoint) &&
            !CGSizeEqualToSize(self.playViewContainer.bounds.size, view.frame.size))
        {
            [self updateContainerConstraintsForTap:view containerView:self.playViewContainer];
            break;
        }
    }
}

@end
