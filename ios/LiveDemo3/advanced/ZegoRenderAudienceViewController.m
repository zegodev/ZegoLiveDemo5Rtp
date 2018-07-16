//
//  ZegoRenderViewController.m
//  LiveDemo3
//
//  Created by Strong on 2016/10/18.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoRenderAudienceViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoLiveToolViewController.h"
#import "ZegoRenderViewController.h"
#import <GLKit/GLKit.h>

@interface ZegoRenderAudienceViewController () <ZegoRoomDelegate, ZegoLivePlayerDelegate, ZegoIMDelegate, ZegoLiveToolViewControllerDelegate>

@property (weak, nonatomic) IBOutlet UIView *playViewContainer;

@property (nonatomic, weak) ZegoLiveToolViewController *toolViewController;

@property (weak, nonatomic) UIButton *publishButton;
@property (weak, nonatomic) UIButton *optionButton;
@property (weak, nonatomic) UIButton *mutedButton;
@property (weak, nonatomic) UIButton *fullscreenButton;

@property (nonatomic, strong) NSMutableArray<ZegoStream *> *streamList;

@property (nonatomic, assign) BOOL loginRoomSuccess;

@property (nonatomic, copy) NSString *liveChannel;

@property (nonatomic, strong) UIColor *defaultButtonColor;

@property (nonatomic, strong) NSMutableDictionary *subViewControllers;
@property (nonatomic, strong) NSMutableDictionary *viewContainersDict;
@property (nonatomic, strong) NSMutableDictionary *streamID2SizeDict;
@property (nonatomic, strong) NSMutableDictionary *videoSizeDict;

@end

@implementation ZegoRenderAudienceViewController

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
    
    self.optionButton = self.toolViewController.joinLiveOptionButton;
    self.publishButton = self.toolViewController.joinLiveButton;
    self.mutedButton = self.toolViewController.playMutedButton;
    self.fullscreenButton = self.toolViewController.fullScreenButton;
    
    self.toolViewController.renderLabel.hidden = NO;
    
    _streamList = [[NSMutableArray alloc] initWithCapacity:self.maxStreamCount];
    _viewContainersDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _videoSizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];
    _streamID2SizeDict = [[NSMutableDictionary alloc] initWithCapacity:self.maxStreamCount];

    
    self.subViewControllers = [NSMutableDictionary dictionary];
    
    self.liveChannel = self.roomID;
    
    [self setupLiveKit];
    
    //room信令与channel信令并行处理
    [self loginRoom];
    
    [self setButtonHidden:YES];
    
    self.fullscreenButton.hidden = YES;
    self.publishButton.enabled = NO;
    self.optionButton.enabled = NO;
}

- (void)setButtonHidden:(BOOL)hidden
{
    if (hidden)
    {
        self.mutedButton.enabled = NO;
    }
    else
    {
        self.mutedButton.enabled = YES;
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


#pragma mark ZegoAVKit
- (void)setupLiveKit
{
    [[ZegoDemoHelper api] setRoomDelegate:self];
    [[ZegoDemoHelper api] setPlayerDelegate:self];
    [[ZegoDemoHelper api] setIMDelegate:self];
}

#pragma mark ZegoLiveRoom
- (void)loginRoom
{
    [[ZegoDemoHelper api] loginRoom:self.roomID role:ZEGO_AUDIENCE withCompletionBlock:^(int errorCode, NSArray<ZegoStream *> *streamList) {
        NSLog(@"%s, error: %d", __func__, errorCode);
        if (errorCode == 0)
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间成功. roomID: %@", nil), self.roomID];
            [self addLogString:logString];
            
            self.loginRoomSuccess = YES;
            if (streamList.count != 0)
                [self onStreamUpdateForAdd:streamList];
            
            [self onLoginChannel:self.roomID error:0];
        }
        else
        {
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"登录房间失败. error: %d", nil), errorCode];
            [self addLogString:logString];
            
            self.loginRoomSuccess = NO;
            [self showNoLivesAlert];
        }
    }];
    
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"开始登录房间", nil)];
    [self addLogString:logString];
}

#pragma mark close
- (void)clearAllStream
{
    for (ZegoStream *info in self.streamList)
    {
        [[ZegoDemoHelper api] stopPlayingStream:info.streamID];
        
        UIViewController *subViewController = self.subViewControllers[info.streamID];
        if (subViewController)
            [subViewController removeFromParentViewController];
        
        UIView *playView = self.viewContainersDict[info.streamID];
        if (playView)
        {
            [self updateContainerConstraintsForRemove:playView containerView:self.playViewContainer];
            [self.viewContainersDict removeObjectForKey:info.streamID];
        }
    }
    
    [self.viewContainersDict removeAllObjects];
}

#pragma mark ZegoLiveToolViewControllerDelegate
- (void)onCloseButton:(id)sender
{
    [self setBackgroundImage:nil playerView:self.playViewContainer];
    
    [self clearAllStream];
    
    if (self.loginRoomSuccess)
    {
        [[ZegoDemoHelper api] logoutRoom];
    }
    
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

- (void)onLogButton:(id)sender
{
    [self showLogViewController];
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

- (NSString *)getStreamIDFromView:(UIView *)view
{
    for (NSString *streamID in self.viewContainersDict)
    {
        if (self.viewContainersDict[streamID] == view)
            return streamID;
    }
    
    return nil;
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
    
    [coordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
    } completion:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
    }];
}

#pragma mark ZegoLiveApiDelegate
- (void)onLoginChannel:(NSString *)channel error:(int)err
{
    if (self.streamList.count == 0 && self.loginRoomSuccess)
    {
        
    }
    else
    {
        for (ZegoStream *info in self.streamList)
        {
            if (self.viewContainersDict[info.streamID] != nil)
                continue;
            
            [self addStreamViewContainer:info.streamID];
            
            NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"继续播放之前的流, 流ID:%@", nil), info.streamID];
            [self addLogString:logString];
        }
    }
}

- (void)onPlayStateUpdate:(int)stateCode streamID:(NSString *)streamID
{
    NSLog(@"%s, streamID:%@", __func__, streamID);

    if (stateCode == 0)
    {
        [self setButtonHidden:NO];
        
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

#pragma mark ZegoRoomApiDelegate

- (void)onDisconnect:(NSString *)roomID errorCode:(unsigned int)errorCode
{
    NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"连接失败, error: %d", nil), errorCode];
    [self addLogString:logString];
}

- (void)onLogoutRoom:(NSString *)roomID
{
    NSLog(@"%s", __func__);
}

- (void)onStreamUpdated:(int)type streams:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID
{
    if (type == ZEGO_STREAM_ADD)
        [self onStreamUpdateForAdd:streamList];
    else if (type == ZEGO_STREAM_DELETE)
        [self onStreamUpdateForDelete:streamList];
}

- (void)onRecvRoomMessage:(NSString *)roomId messageList:(NSArray<ZegoRoomMessage *> *)messageList
{
    [self.toolViewController updateLayout:messageList];
}

#pragma mark Stream add & delete function
- (BOOL)isStreamIDExist:(NSString *)streamID
{
    for (ZegoStream *info in self.streamList)
    {
        if ([info.streamID isEqualToString:streamID])
            return YES;
    }
    
    return NO;
}

- (void)addStreamViewContainer:(NSString *)streamID
{
    if (streamID.length == 0)
        return;
    
    if (self.viewContainersDict[streamID] != nil)
        return;
    
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    ZegoRenderViewController *renderViewController = (ZegoRenderViewController *)[storyboard instantiateViewControllerWithIdentifier:@"renderStoryboardID"];
    
    renderViewController.view.translatesAutoresizingMaskIntoConstraints = NO;
    GLKView *bigView = (GLKView *)renderViewController.view;
    [self.playViewContainer addSubview:bigView];
    [self.playViewContainer sendSubviewToBack:bigView];
    
    [self addChildViewController:renderViewController];
    self.subViewControllers[streamID] = renderViewController;
     
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
    assert(ret);
}

- (void)removeStreamViewContainer:(NSString *)streamID
{
    if (streamID.length == 0)
        return;
    
    UIViewController *viewController = self.subViewControllers[streamID];
    if (viewController)
        [viewController removeFromParentViewController];
    
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
        
        [self.streamList addObject:stream];
        [self addStreamViewContainer:streamID];
        
        NSString *logString = [NSString stringWithFormat:NSLocalizedString(@"新增一条流, 流ID:%@", nil), streamID];
        [self addLogString:logString];
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
    }
}

#pragma mark Alert
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

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [self onCloseButton:nil];
}

@end
