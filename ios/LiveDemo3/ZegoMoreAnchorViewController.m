//
//  ZegoMoreAnchorViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/9/9.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoMoreAnchorViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoAnchorOptionViewController.h"
#import "ZegoLiveToolViewController.h"

@interface ZegoMoreAnchorViewController () <ZegoRoomDelegate, ZegoLivePublisherDelegate, ZegoLivePlayerDelegate, ZegoIMDelegate, ZegoLiveToolViewControllerDelegate>

//IBOutlet
@property (weak, nonatomic) IBOutlet UIView *playViewContainer;

@property (weak, nonatomic) ZegoLiveToolViewController *toolViewController;

@property (weak, nonatomic) UIButton *stopPublishButton;
@property (weak, nonatomic) UIButton *mutedButton;
@property (nonatomic, weak) UIButton *sharedButton;

//创建stream后，server返回的streamID(当前直播的streamID)
@property (nonatomic, copy) NSString *streamID;

//正在观看房间里的其他直播
@property (nonatomic, assign) BOOL isPlaying;

//正在播放的streamList
@property (nonatomic, strong) NSMutableArray *playStreamList;

@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;

@property (nonatomic, assign) BOOL isPublishing;

@property (nonatomic, strong) UIColor *defaultButtonColor;
@property (nonatomic, strong) UIColor *disableButtonColor;

@property (nonatomic, copy) NSString *sharedHls;
@property (nonatomic, copy) NSString *sharedRtmp;
@property (nonatomic, copy) NSString *roomID;

@property (nonatomic, assign) UIInterfaceOrientation orientation;

@end

@implementation ZegoMoreAnchorViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
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
    self.mutedButton = self.toolViewController.mutedButton;
    self.sharedButton = self.toolViewController.shareButton;
    
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

#pragma mark - ZegoLiveRoom

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
    
    //开启双声道直播
    [[ZegoDemoHelper api] setAudioChannelCount:2];
    
    bool b = [[ZegoDemoHelper api] startPublishing:self.streamID title:self.liveTitle flag:ZEGO_JOIN_PUBLISH];
    if (b)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始直播，流ID:%@", nil), self.streamID]];
    }
    return b;
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

- (void)loginChatRoom
{
    self.roomID = [ZegoDemoHelper getMyRoomID:MultiPublisherRoom];
    self.streamID = [ZegoDemoHelper getPublishStreamID];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID roomName:self.liveTitle role:ZEGO_ANCHOR withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
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
    
    [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)]];
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
    NSLog(@"%s, stream: %@, err: %d", __func__, streamID, stateCode);

    if (stateCode == 0)
    {
        self.isPublishing = YES;
        self.stopPublishButton.enabled = YES;
        
        [self.stopPublishButton setTitle:NSLocalizedString(@"停止直播", nil) forState:UIControlStateNormal];

        self.sharedHls = [info[kZegoHlsUrlListKey] firstObject];
        self.sharedRtmp = [info[kZegoRtmpUrlListKey] firstObject];

        [self addLogString:[NSString stringWithFormat:@"Hls %@", self.sharedHls]];
        [self addLogString:[NSString stringWithFormat:@"Rtmp %@", self.sharedRtmp]];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播成功,流ID:%@", nil), streamID];
        [self addLogString:logString];
        
        if (self.sharedHls.length > 0 && self.sharedRtmp.length > 0)
        {
            self.sharedButton.enabled = YES;
            
            NSDictionary *dict = @{kFirstAnchor: @(YES), kHlsKey: self.sharedHls, kRtmpKey: self.sharedRtmp};
            NSString *jsonString = [self encodeDictionaryToJSON:dict];
            if (jsonString)
                [[ZegoDemoHelper api] updateStreamExtraInfo:jsonString];
        }
        else
        {
            self.sharedButton.enabled = NO;
        }
    }
    else
    {
        self.isPublishing = NO;
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        self.stopPublishButton.enabled = YES;
        self.sharedButton.enabled = NO;
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"直播结束,流ID：%@, error:%d", nil), streamID, stateCode];
        [self addLogString:logString];
        
        [self removeStreamViewContainer:streamID];
        self.publishView = nil;
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

- (void)onJoinLiveRequest:(int)seq fromUserID:(NSString *)userId fromUserName:(NSString *)userName roomID:(NSString *)roomID
{
    if (seq == 0 || userId.length == 0)
        return;

    [self onReceiveJoinLive:userId userName:userName seq:seq];
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
        NSLog(@"%s, streamID:%@", __func__, streamID);
        
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


- (BOOL)shouldShowPublishAlert
{
    if (self.viewContainersDict.count < self.maxStreamCount)
        return YES;
    
    return NO;
}

#pragma mark - stream Add & Delete
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
    }
    
    self.mutedButton.enabled = YES;
}

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

#pragma mark playStream
- (void)createPlayStream:(NSString *)streamID
{
    if (self.viewContainersDict[streamID] != nil)
        return;
    
    UIView *playView = [self createPlayView:streamID];
    
    [[ZegoDemoHelper api] startPlayingStream:streamID inView:playView];
    [[ZegoDemoHelper api] setViewMode:ZegoVideoViewModeScaleAspectFill ofStream:streamID];
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

#pragma mark close publish

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

#pragma mark - ZegoAnchorToolViewControllerDelegate
- (void)onCloseButton:(id)sender
{
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

- (void)onStopPublishButton:(id)sender
{
    if (self.isPublishing)
    {
        //停止直播
        [self stopPublishing];
        
//        for (ZegoStream *stream in self.playStreamList)
//        {
//            [[ZegoDemoHelper api] endJoinLive:stream.userID completionBlock:nil];
//        }
        
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        self.stopPublishButton.enabled = YES;
    }
    else if ([[self.stopPublishButton currentTitle] isEqualToString:NSLocalizedString(@"开始直播", nil)])
    {
        self.streamID = [ZegoDemoHelper getPublishStreamID];
        self.stopPublishButton.enabled = NO;
        [self doPublish];
    }
}

- (void)onLogButton:(id)sender
{
    [self showLogViewController];
}

- (void)onShareButton:(id)sender
{
    if (self.sharedHls.length == 0)
        return;
    
    [self shareToQQ:self.sharedHls rtmp:self.sharedRtmp bizToken:nil bizID:self.roomID streamID:self.streamID];
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
            [self updateContainerConstraintsForTap:view containerView:self.playViewContainer];
            break;
        }
    }
}

#pragma mark PublishView create
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

- (UIView *)createPublishView
{
    UIView *publishView = [[UIView alloc] init];
    publishView.translatesAutoresizingMaskIntoConstraints = NO;
    
    BOOL result = [self updatePublishView:publishView];
    if (result == NO)
        return nil;
    
    return publishView;
}


@end
