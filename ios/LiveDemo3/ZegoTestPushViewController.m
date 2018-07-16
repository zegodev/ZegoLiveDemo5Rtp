//
//  ZegoTestPushViewController.m
//  LiveDemo3
//
//  Created by summery on 02/05/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

#import "ZegoTestPushViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoAnchorOptionViewController.h"
#import "ZegoLiveToolViewController.h"

@interface ZegoTestPushViewController ()<ZegoRoomDelegate, ZegoLivePublisherDelegate, ZegoIMDelegate, ZegoLiveToolViewControllerDelegate>

@property (weak, nonatomic) IBOutlet UIView *playViewContainer;
@property (weak, nonatomic) IBOutlet UIView *toolView;

@property (nonatomic, weak) ZegoLiveToolViewController *toolViewController;

@property (nonatomic, weak) UIButton *stopPublishButton;
@property (nonatomic, weak) UIButton *mutedButton;
@property (nonatomic, weak) UIButton *sharedButton;

//@property (nonatomic, copy) NSString *streamID; // 推流ID

@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;

@property (nonatomic, assign) BOOL isPublishing;

@property (nonatomic, strong) UIColor *defaultButtonColor;
@property (nonatomic, strong) UIColor *disableButtonColor;

@property (nonatomic, copy) NSString *sharedHls;
@property (nonatomic, copy) NSString *sharedRtmp;
//@property (nonatomic, copy) NSString *roomID; // 房间ID

@property (nonatomic, assign) UIInterfaceOrientation orientation;

@end

@implementation ZegoTestPushViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self setupLiveKit];
    [self loginChatRoom];
    
    _viewContainersDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    
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

#pragma mark - Private method

#pragma mark -- Handle rotation

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

#pragma mark -- Config ZegoLiveRoom

- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
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
    
    // 如果没有setMixStreamConfig，则不能正常播放
    if (self.flag == ZEGOAPI_MIX_STREAM) {
        CGSize videoSize = [ZegoSettings sharedInstance].currentConfig.videoEncodeResolution;
        [[ZegoDemoHelper api] setMixStreamConfig:@{kZegoMixStreamIDKey: self.mixStreamID,
                                                   kZegoMixStreamResolution: [NSValue valueWithCGSize:CGSizeMake(2*videoSize.width, 2*videoSize.height)]}];
    }

    
    bool b = [[ZegoDemoHelper api] startPublishing:self.streamID title:self.liveTitle flag:self.flag];
    if (b)
    {
        [self addLogString:[NSString stringWithFormat:NSLocalizedString(@"开始直播，流ID:%@", nil), self.streamID]];
    }
    return b;
}

- (void)loginChatRoom
{
//    self.roomID = [ZegoDemoHelper getMyRoomID:SinglpoePublisherRoom];
//    self.streamID = [ZegoDemoHelper getPublishStreamID];
    self.mixStreamID = [NSString stringWithFormat:@"%@-mix", self.streamID];
    
    [[ZegoDemoHelper api] loginRoom:self.roomID roomName:self.liveTitle role:ZEGO_ANCHOR  withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
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

#pragma mark -- Create publishView

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

- (void)removeStreamViewContainer:(NSString *)streamID
{
    UIView *view = self.viewContainersDict[streamID];
    if (view == nil)
        return;
    
    [self updateContainerConstraintsForRemove:view containerView:self.playViewContainer];
    
    [self.viewContainersDict removeObjectForKey:streamID];
}

#pragma mark -- Close publish

- (void)closeAllStream
{
    [self stopPublishing];
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

#pragma mark - ZegoRoomDelegate

- (void)onDisconnect:(int)errorCode roomID:(NSString *)roomID
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"连接失败, error: %d", nil), errorCode];
    [self addLogString:logString];
}

#pragma mark - ZegoLivePublisherDelegate

- (void)onPublishStateUpdate:(int)stateCode streamID:(NSString *)streamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%s, stream: %@, state: %d", __func__, streamID, stateCode);
    
    NSString *logString = nil;
    
    if (stateCode == 0)
    {
        self.isPublishing = YES;
        
        [self.stopPublishButton setTitle:NSLocalizedString(@"停止直播", nil) forState:UIControlStateNormal];
        
        self.sharedHls = [info[kZegoHlsUrlListKey] firstObject];
        self.sharedRtmp = [info[kZegoRtmpUrlListKey] firstObject];
        
        [self addLogString:[NSString stringWithFormat:@"Hls %@", self.sharedHls]];
        [self addLogString:[NSString stringWithFormat:@"Rtmp %@", self.sharedRtmp]];
        
        logString = [NSString stringWithFormat:NSLocalizedString(@"发布直播成功,流ID:%@", nil), streamID];
        
        if (self.sharedHls.length > 0 && self.sharedRtmp.length > 0)
        {
            self.sharedButton.enabled = YES;
            
            NSDictionary *dict = @{kHlsKey: self.sharedHls, kRtmpKey: self.sharedRtmp};
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
        [self removeStreamViewContainer:streamID];
        self.publishView = nil;
        self.sharedButton.enabled = NO;
        
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        
        logString = [NSString stringWithFormat:NSLocalizedString(@"直播结束,流ID：%@, error:%d", nil), streamID, stateCode];
    }
    
    [self addLogString:logString];
    
    self.stopPublishButton.enabled = YES;
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

// 使混流模式下播放成功
- (void)onMixStreamConfigUpdate:(int)errorCode mixStream:(NSString *)mixStreamID streamInfo:(NSDictionary *)info
{
    NSLog(@"%@, errorCode %d", mixStreamID, errorCode);
    
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
    
    if (self.sharedHls.length > 0 && self.sharedRtmp.length > 0)
    {
        self.sharedButton.enabled = YES;
        
        NSDictionary *dict = @{kFirstAnchor: @(YES), kMixStreamID: mixStreamID, kHlsKey: self.sharedHls, kRtmpKey: self.sharedRtmp};
        NSString *jsonString = [self encodeDictionaryToJSON:dict];
        if (jsonString)
            [[ZegoDemoHelper api] updateStreamExtraInfo:jsonString];
    }
    else
    {
        self.sharedButton.enabled = NO;
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
        [self stopPublishing];
        
        // * update button
        [self.stopPublishButton setTitle:NSLocalizedString(@"开始直播", nil) forState:UIControlStateNormal];
        self.stopPublishButton.enabled = YES;
    }
    else if ([[self.stopPublishButton currentTitle] isEqualToString:NSLocalizedString(@"开始直播", nil)])
    {
        [self doPublish];
        self.stopPublishButton.enabled = NO;
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


@end
