//
//  ZegoWerewolfBaseViewController.m
//  LiveDemo3
//
//  Created by Strong on 2017/3/29.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoWerewolfBaseViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoLogTableViewController.h"

@interface ZegoWerewolfBaseViewController ()

@property (nonatomic, assign) NSUInteger subViewSpace;
@property (nonatomic, assign) NSUInteger subViewWidth;
@property (nonatomic, assign) NSUInteger subViewHeight;
@property (nonatomic, assign) NSUInteger subViewPerRow;

//日志记录
@property (nonatomic, strong) NSMutableArray *logArray;
//帧率，码率信息
@property (nonatomic, strong) NSMutableArray *staticsArray;

@property (nonatomic, strong) dispatch_source_t countTimer;

@end

@implementation ZegoWerewolfBaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _maxStreamCount = [ZegoLiveRoomApi getMaxPlayChannelCount];
    
    CGFloat width = CGRectGetWidth(self.view.frame);
    
    self.subViewSpace = 10;
    if (self.maxStreamCount <= 3)
    {
        self.subViewPerRow = 4;
    }
    else
    {
        self.subViewPerRow = 4;
    }
    
    self.subViewWidth = (width - (self.subViewPerRow + 1) * self.subViewSpace) / self.subViewPerRow;
    self.subViewWidth = ceil(self.subViewWidth);
    self.subViewHeight = 3 * self.subViewWidth / 2;
    
    self.logArray = [NSMutableArray array];
    self.staticsArray = [NSMutableArray array];
    
    self.flag = ZEGO_SINGLE_ANCHOR;
    self.videoSize = CGSizeMake(240, 320);
    self.bitrate = 200000;
    
    //彩蛋
    UILongPressGestureRecognizer *longPressGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(onShowStaticsViewController:)];
    [self.playViewContainer addGestureRecognizer:longPressGesture];
}

- (void)setIdelTimerDisable:(BOOL)disable
{
    [[UIApplication sharedApplication] setIdleTimerDisabled:disable];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self setIdelTimerDisable:YES];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self setIdelTimerDisable:NO];
    [super viewWillDisappear:animated];
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
    return UIInterfaceOrientationMaskPortrait;
}

#pragma mark Action
- (IBAction)onLog:(id)sender
{
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UINavigationController *navigationController = (UINavigationController *)[storyboard instantiateViewControllerWithIdentifier:@"logNavigationID"];
    
    ZegoLogTableViewController *logViewController = (ZegoLogTableViewController *)[navigationController.viewControllers firstObject];
    logViewController.logArray = self.logArray;
    
    [self presentViewController:navigationController animated:YES completion:nil];
}

- (void)onShowStaticsViewController:(UIGestureRecognizer *)gesture
{
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    UINavigationController *navigationController = (UINavigationController *)[storyboard instantiateViewControllerWithIdentifier:@"logNavigationID"];
    
    ZegoLogTableViewController *logViewController = (ZegoLogTableViewController *)[navigationController.viewControllers firstObject];
    logViewController.logArray = self.staticsArray;
    
    [self presentViewController:navigationController animated:YES completion:nil];
}


#pragma mark JSON
- (NSString *)encodeDictionaryToJSON:(NSDictionary *)data
{
    if (data == nil)
        return nil;
    
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:data options:0 error:nil];
    if (jsonData)
    {
        NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        return jsonString;
    }
    
    return nil;
}

- (NSDictionary *)decodeJSONToDictionary:(NSString *)json
{
    if (json == nil)
        return nil;
    
    NSData *jsonData = [json dataUsingEncoding:NSUTF8StringEncoding];
    if (jsonData)
    {
        NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];
        return dictionary;
    }
    
    return nil;
}

- (NSDictionary *)serializeWolfUserInfo:(ZegoWerewolUserInfo *)info
{
    return @{kUserIdKey: info.userId, kUserNameKey: info.userName, kUserIndexKey: @(info.index)};
}

- (ZegoWerewolUserInfo *)deserializeWolfUserInfo:(NSDictionary *)dict
{
    if (!dict[kUserIdKey])
        return nil;
    
    ZegoWerewolUserInfo *info = [ZegoWerewolUserInfo new];
    info.userId = dict[kUserIdKey];
    info.userName = dict[kUserNameKey];
    info.index = [dict[kUserIndexKey] unsignedIntegerValue];
    
    return info;
}

#pragma mark AutoLayout
- (void)updateViewConstraints:(UIView *)view viewIndex:(NSUInteger)viewIndex
{
    UIView *containerView = self.playViewContainer;
    
    NSUInteger xIndex = (viewIndex - 1) % self.subViewPerRow;
    NSUInteger yIndex = (viewIndex - 1) / self.subViewPerRow;
    
    CGFloat xToLeftConstraints = xIndex * (self.subViewSpace + self.subViewWidth) + self.subViewSpace;
    CGFloat yToTopConstraints = yIndex * (self.subViewSpace + self.subViewHeight) + self.subViewSpace;
    
    NSLayoutConstraint *widthConstraints = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeWidth multiplier:1.0 constant:self.subViewWidth];
    NSLayoutConstraint *heightConstraints = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeHeight multiplier:1.0 constant:self.subViewHeight];
    
    NSLayoutConstraint *leftConstraints = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:containerView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:xToLeftConstraints];
    NSLayoutConstraint *topConstraints = [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:containerView attribute:NSLayoutAttributeTop multiplier:1.0 constant:yToTopConstraints];
    
    [containerView addConstraints:@[widthConstraints, heightConstraints, leftConstraints, topConstraints]];
}

- (void)setContainerConstraints:(UIView *)view viewIndex:(NSUInteger)viewIndex
{
    if (view == nil)
        return;
    
    [self updateViewConstraints:view viewIndex:viewIndex];
    
    [UIView animateWithDuration:0.1 animations:^{
        [self.view layoutIfNeeded];
    }];
}

- (NSUInteger)getViewIndex:(UIView *)view containerView:(UIView *)containerView
{
    if (CGRectGetWidth(view.frame) == CGRectGetWidth(containerView.frame) &&
        CGRectGetHeight(view.frame) == CGRectGetHeight(containerView.frame))
        return 0;
    else
    {
        CGFloat deltaHeight = CGRectGetMinY(view.frame) - self.subViewSpace;
        CGFloat deltaWidth = CGRectGetMinX(view.frame) - self.subViewSpace;
        
        NSUInteger xIndex = deltaWidth / (self.subViewSpace + self.subViewWidth);
        NSUInteger yIndex = deltaHeight / (self.subViewSpace + self.subViewHeight);
        
        return yIndex * self.subViewPerRow + xIndex + 1;
    }
}

- (void)updateContainerConstraintsForRemove:(UIView *)removeView
{
    if (removeView == nil)
        return;
    
    NSUInteger removeIndex = [self getViewIndex:removeView containerView:self.playViewContainer];
    [self.playViewContainer removeConstraints:self.playViewContainer.constraints];
    
    for (UIView *view in self.playViewContainer.subviews)
    {
        NSUInteger viewIndex = [self getViewIndex:view containerView:self.playViewContainer];
        if (viewIndex > removeIndex)
            [self updateViewConstraints:view viewIndex:viewIndex - 1];
        else if (viewIndex < removeIndex)
            [self updateViewConstraints:view viewIndex:viewIndex];
    }
    
    [removeView removeFromSuperview];
    [UIView animateWithDuration:0.1 animations:^{
        [self.view layoutIfNeeded];
    }];
}

#pragma help function

- (NSString *)getCurrentTime
{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"[HH-mm-ss:SSS]";
    return [formatter stringFromDate:[NSDate date]];
}


- (void)addLogString:(NSString *)logString
{
    if (logString.length != 0)
    {
        NSString *totalString = [NSString stringWithFormat:@"%@: %@", [self getCurrentTime], logString];
        [self.logArray insertObject:totalString atIndex:0];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:@"logUpdateNotification" object:self userInfo:nil];
    }
}

- (NSString *)addStaticsInfo:(BOOL)publish stream:(NSString *)streamID fps:(double)fps kbs:(double)kbs rtt:(int)rtt pktLostRate:(int)pktLostRate
{
    if (streamID.length == 0)
        return nil;
    
    NSString *qualityString = [NSString stringWithFormat:@"[%@] 帧率: %.3f, 视频码率: %.3f kb/s, 延时: %d ms, 丢包率: %.3f%%", publish ? @"推流": @"拉流", fps, kbs, rtt, pktLostRate/256.0 * 100];
    NSString *totalString =[NSString stringWithFormat:@"[%@] 流ID: %@, 帧率: %.3f, 视频码率: %.3f kb/s, 延时: %d ms, 丢包率: %.3f%%", publish ? @"推流": @"拉流", streamID, fps, kbs, rtt, pktLostRate/256.0 * 100];
    [self.staticsArray insertObject:totalString atIndex:0];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"logUpdateNotification" object:self userInfo:nil];
    return qualityString;
}

#pragma UIView
- (void)addNumber:(NSUInteger)number toView:(UIView *)view
{
    CATextLayer *layer = [CATextLayer layer];
    layer.frame = CGRectMake(10, 10, 20, 20);
    
    layer.string = [NSString stringWithFormat:@"%lu", (unsigned long)number];
    layer.fontSize = 12;
    layer.backgroundColor = [UIColor clearColor].CGColor;
    layer.foregroundColor = [UIColor redColor].CGColor;
    layer.alignmentMode = kCAAlignmentCenter;
    layer.contentsScale = [UIScreen mainScreen].scale;
    [view.layer addSublayer:layer];
}

- (void)addText:(NSString *)text toView:(UIView *)view
{
    UILabel *label = [[UILabel alloc] init];
    label.translatesAutoresizingMaskIntoConstraints = NO;
    [view addSubview:label];
    
    label.text = text;
    label.font = [UIFont systemFontOfSize:12];
    label.textColor = [UIColor blackColor];
    label.textAlignment = NSTextAlignmentCenter;
    label.numberOfLines = 0;
    
    NSArray *hConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[label]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(label)];
    NSArray *vConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:[label]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(label)];
    NSLayoutConstraint *heightConstraints = [NSLayoutConstraint constraintWithItem:label attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeHeight multiplier:0.25 constant:0];
    
    [view addConstraints:hConstraints];
    [view addConstraints:vConstraints];
    [view addConstraint:heightConstraints];
}

#pragma mark Authorization check
//检查相机权限
- (BOOL)checkVideoAuthorizationWithResult:(void (^)(BOOL granted))resultBlock
{
    AVAuthorizationStatus videoAuthStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if (videoAuthStatus == AVAuthorizationStatusDenied || videoAuthStatus == AVAuthorizationStatusRestricted)
        return NO;
    if (videoAuthStatus == AVAuthorizationStatusNotDetermined)
    {
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            if (resultBlock)
                resultBlock(granted);
        }];
    }
    return YES;
}

- (BOOL)checkAudioAuthorizationWithResult:(void (^)(BOOL granted))resultBlock
{
    AVAuthorizationStatus audioAuthStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    if (audioAuthStatus == AVAuthorizationStatusDenied || audioAuthStatus == AVAuthorizationStatusRestricted)
        return NO;
    if (audioAuthStatus == AVAuthorizationStatusNotDetermined)
    {
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
            if (resultBlock)
                resultBlock(granted);
        }];
    }
    
    return YES;
}

- (void)startCountDownWithTime:(NSInteger)time fireBlock:(void (^)(int))block
{
    __block NSInteger timeOut = time;
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    self.countTimer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    dispatch_source_set_timer(self.countTimer, dispatch_walltime(NULL, 0), 1.0 * NSEC_PER_SEC, 0);
    dispatch_source_set_event_handler(self.countTimer, ^{
        if (timeOut <= 0)
        {
            [self stopCountDownTimer];
            if (block)
                block(0);
        }
        else
        {
            int allTime = (int)time + 1;
            int seconds = timeOut % allTime;
            if (block)
                block(seconds);
            
            timeOut -= 1;
        }
    });
    
    dispatch_resume(self.countTimer);
}

- (void)stopCountDownTimer
{
    if (self.countTimer)
    {
        dispatch_source_cancel(self.countTimer);
        self.countTimer = nil;
    }
}

@end

@implementation ZegoWerewolUserInfo

@end
