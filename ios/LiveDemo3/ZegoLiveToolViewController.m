//
//  ZegoAnchorToolViewController.m
//  LiveDemo3
//
//  Created by Strong on 2017/1/4.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoLiveToolViewController.h"
#import "ZegoMessageTableViewCell.h"
#import "ZegoLikeView.h"

@interface ZegoLiveToolViewController ()

@property (nonatomic, weak) IBOutlet UIView *editingView;
@property (nonatomic, weak) IBOutlet UITextField *textField;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint *commentViewConstraint;
@property (nonatomic, weak) IBOutlet UIButton *sendButton;
@property (nonatomic, weak) IBOutlet UIView *likeTapView;

@property (nonatomic, weak) IBOutlet UITableView *messageView;

@property (nonatomic, weak) IBOutlet NSLayoutConstraint *topViewHeightConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint *topViewBottomConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint *commentViewHeightConstraint;

@property (nonatomic, weak) IBOutlet UIView *anchorView;
@property (nonatomic, weak) IBOutlet UIView *audienceView;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint *audienceViewTopConstraint;

@property (nonatomic, weak) IBOutlet ZegoLikeView *likeView;

@property (nonatomic, strong) NSMutableArray<YYTextLayout*> *liveMessageList;

@property (nonatomic, assign) NSTimeInterval currentTime;

@property (nonatomic, strong) NSTimer *timer;
@property (nonatomic, assign) NSUInteger likeCount;

@property (nonatomic, strong) NSTimer *recordTimer;
@property (nonatomic, strong) NSDateFormatter *timeFormatter;

@end

@implementation ZegoLiveToolViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor clearColor];
    
    self.topViewHeightConstraint.constant = CGRectGetHeight(self.view.frame) - self.topViewBottomConstraint.constant - self.commentViewHeightConstraint.constant;
    
    self.liveMessageList = [NSMutableArray array];
    self.isAudience = NO;
    self.renderLabel.hidden = YES;
    
    self.messageView.allowsSelection = NO;
    self.messageView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.messageView.backgroundColor = [UIColor clearColor];
    self.messageView.tableFooterView = [[UIView alloc] init];
    [self.messageView registerClass:[ZegoMessageTableViewCell class] forCellReuseIdentifier:@"liveMessageIdentifier"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillChangeFrame:) name:UIKeyboardWillChangeFrameNotification object:nil];
    
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapView:)];
    [self.view addGestureRecognizer:tapGestureRecognizer];
    
    UITapGestureRecognizer *likeTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapLikeView:)];
    [self.likeTapView addGestureRecognizer:likeTapGestureRecognizer];
    
    self.timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(updateTimeLabel) userInfo:nil repeats:YES];
    [[NSRunLoop mainRunLoop] addTimer:self.timer forMode:NSRunLoopCommonModes];
}

- (void)startTimeRecord
{
    if (!self.timeFormatter)
    {
        self.timeFormatter = [[NSDateFormatter alloc] init];
        self.timeFormatter.dateFormat = @"HH:mm:ss:SSS";
        self.timeFormatter.timeZone = [NSTimeZone timeZoneWithAbbreviation:@"GMT+0800"];
    }
    
    self.timeLabel.hidden = NO;
    
    if (!self.recordTimer)
    {
        self.recordTimer = [NSTimer scheduledTimerWithTimeInterval:1.0/60 target:self selector:@selector(updateTimeLabel) userInfo:nil repeats:YES];
        [[NSRunLoop mainRunLoop] addTimer:self.recordTimer forMode:NSRunLoopCommonModes];
        
        [self.recordTimer fire];
    }
}

- (void)stopTimeRecord
{
    if (self.recordTimer != nil)
    {
        [self.recordTimer invalidate];
        self.recordTimer = nil;
    }
}

- (void)updateTimeLabel
{
    [self.timeLabel setText:[self.timeFormatter stringFromDate:[NSDate date]]];
}

#pragma mark rotate
- (void)updateTopViewConstraints
{
    self.topViewHeightConstraint.constant = CGRectGetHeight(self.view.frame) - self.topViewBottomConstraint.constant - self.commentViewHeightConstraint.constant;
    
    [UIView animateWithDuration:0.1 animations:^{
        [self.view layoutIfNeeded];
    }];
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [coordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
        [self updateTopViewConstraints];
    } completion:^(id<UIViewControllerTransitionCoordinatorContext>  _Nonnull context) {
        
    }];
    
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [self updateTopViewConstraints];
    
    [super willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self.textField resignFirstResponder];
    
    [self.timer invalidate];
    self.timer = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setIsAudience:(BOOL)isAudience
{
    _isAudience = isAudience;
    
    if (self.isAudience)
    {
        self.anchorView.hidden = YES;
        self.audienceView.hidden = NO;
        self.audienceViewTopConstraint.constant = 44;
        self.shareButton.hidden = NO;
    }
    else
    {
        self.anchorView.hidden = NO;
        self.audienceView.hidden = YES;
        self.shareButton.hidden = NO;
    }
}

- (void)keyboardWillChangeFrame:(NSNotification *)notification
{
    if (!self.textField.isEditing)
        return;
    
    NSDictionary *keyboardAnimationDetail = notification.userInfo;
    NSTimeInterval duration = [keyboardAnimationDetail[UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    CGRect beginFrame = [keyboardAnimationDetail[UIKeyboardFrameBeginUserInfoKey] CGRectValue];
    CGRect keyboardFrame = [keyboardAnimationDetail[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    keyboardFrame = [self.view.window convertRect:keyboardFrame toView:self.view];
    if (CGRectEqualToRect(keyboardFrame, CGRectZero))
        return;
    
    NSUInteger animationCurve = [keyboardAnimationDetail[UIKeyboardAnimationCurveUserInfoKey] unsignedIntegerValue];
    
    CGFloat chatInputOffset = CGRectGetMinY(keyboardFrame) + self.bottomLayoutGuide.length - CGRectGetHeight(self.view.bounds);
    if (chatInputOffset > 0)
        chatInputOffset = 0;
    
    self.commentViewConstraint.constant = chatInputOffset;
    [UIView animateWithDuration:duration delay:0.0 options:animationCurve animations:^{
        [self.view layoutIfNeeded];
        self.editingView.alpha = !(beginFrame.origin.y < keyboardFrame.origin.y);
    } completion:^(BOOL finished) {
    }];
}

- (void)onTapView:(UIGestureRecognizer *)gesture
{
    if (self.textField.isEditing)
    {
        [self.textField resignFirstResponder];
    }
    else
    {
        if ([self.delegate respondsToSelector:@selector(onTapViewPoint:)])
            [self.delegate onTapViewPoint:[gesture locationInView:nil]];
    }
}

- (void)onTapLikeView:(UITapGestureRecognizer *)gesture
{
    //点赞
    [self.likeView doLikeAnimation];
    [self onLike];
}

- (void)onLike
{
    NSTimeInterval currentTime = [[NSDate date] timeIntervalSince1970];
    if (self.currentTime == 0 || currentTime - self.currentTime < 60)
    {
        self.currentTime = [[NSDate date] timeIntervalSince1970];
        if ([self.delegate respondsToSelector:@selector(onSendLike)])
            [self.delegate onSendLike];
    }
}

#pragma mark UITextFieldDelegate
- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [self onSendMessage:nil];
    
    return YES;
}

- (IBAction)onComment:(id)sender
{
    [self.textField becomeFirstResponder];
}

- (IBAction)onSendMessage:(id)sender
{
    if (self.textField.text.length != 0)
    {
        if ([self.delegate respondsToSelector:@selector(onSendComment:)])
            [self.delegate onSendComment:self.textField.text];
                
        self.textField.text = @"";
    }
}

- (IBAction)onClose:(id)sender
{
    
    if ([self.delegate respondsToSelector:@selector(onCloseButton:)])
        [self.delegate onCloseButton:sender];
}

- (IBAction)onShare:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onShareButton:)])
        [self.delegate onShareButton:sender];
}

#pragma mark Anchor action
- (IBAction)onOption:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onOptionButton:)])
        [self.delegate onOptionButton:sender];
}

- (IBAction)onStopPublish:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onStopPublishButton:)])
        [self.delegate onStopPublishButton:sender];
}

- (IBAction)onMute:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onMutedButton:)])
        [self.delegate onMutedButton:sender];
}

- (IBAction)onLog:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onLogButton:)])
        [self.delegate onLogButton:sender];
}

#pragma mark Audience action
- (IBAction)onJoinLive:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onJoinLiveButton:)])
        [self.delegate onJoinLiveButton:sender];
}

- (IBAction)onFullScreen:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(onEnterFullScreenButton:)])
        [self.delegate onEnterFullScreenButton:sender];
}

#pragma mark comment
- (void)updateLayout:(NSArray<ZegoRoomMessage *> *)messageList
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        for (ZegoRoomMessage *message in messageList)
        {
            if (message.category == ZEGO_CHAT)
                [self caculateLayout:@"" userName:message.fromUserName content:message.content];
            else if (message.category == ZEGO_LIKE)
            {
                //解析Content 内容
                NSData *contentData = [message.content dataUsingEncoding:NSUTF8StringEncoding];
                NSDictionary *contentDict = [NSJSONSerialization JSONObjectWithData:contentData options:0 error:nil];
                
                NSUInteger count = [contentDict[@"likeCount"] unsignedIntegerValue];
                if (count != 0)
                {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [self updateLikeAnimation:count];
                    });
                }
                [self caculateLayout:@"" userName:message.fromUserName content:@"点赞了主播"];
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                [self.messageView reloadData];
                [self scrollTableViewToBottom];
            });
        }
    });
}

- (void)caculateLayout:(NSString *)userInfo userName:(NSString *)userName content:(NSString *)content
{
    if (userName.length == 0 || content.length == 0)
        return;
    
    CGFloat totalWidth = CGRectGetWidth(self.messageView.frame) - 20;
    
    NSMutableAttributedString *totalText = [[NSMutableAttributedString alloc] init];
    if (userInfo)
    {
        NSMutableAttributedString *userInfoString = [[NSMutableAttributedString alloc] initWithString:userInfo];
        userInfoString.yy_font = [UIFont systemFontOfSize:12.0];
        userInfoString.yy_color = [UIColor whiteColor];
        
        YYTextBorder *border = [YYTextBorder new];
        border.strokeColor = [UIColor redColor];
        border.fillColor = [UIColor redColor];
        border.cornerRadius = 1;
        border.lineJoin = kCGLineJoinBevel;
        border.insets = UIEdgeInsetsMake(0, 0, 2.5, 0);
        
        userInfoString.yy_textBackgroundBorder = border;
        [userInfoString addAttribute:NSBaselineOffsetAttributeName value:@(2) range:NSMakeRange(0, userInfo.length)];
        
        [totalText appendAttributedString:userInfoString];
    }
    
    NSMutableAttributedString *userNameString = [[NSMutableAttributedString alloc] initWithString:[NSString stringWithFormat:@" %@: ", userName]];
    
    userNameString.yy_font = [UIFont systemFontOfSize:16.0];
    userNameString.yy_color = [UIColor colorWithRed:253/255.0 green:181/255.0 blue:84/255.0 alpha:1.0];
    
    [totalText appendAttributedString:userNameString];
    
    NSMutableAttributedString *contentString = [[NSMutableAttributedString alloc] initWithString:content];
    contentString.yy_font = [UIFont systemFontOfSize:16.0];
    contentString.yy_color = [UIColor whiteColor];
    
    [totalText appendAttributedString:contentString];
    
    YYTextContainer *container = [YYTextContainer containerWithSize:CGSizeMake(totalWidth, CGFLOAT_MAX)];
    container.insets = UIEdgeInsetsMake(2, 10, 2, 10);
    
    YYTextLayout *textLayout = [YYTextLayout layoutWithContainer:container text:totalText];
    
    [self.liveMessageList addObject:textLayout];
    
}

- (void)scrollTableViewToBottom
{
    NSInteger lastItemIndex = [self.messageView numberOfRowsInSection:0] - 1;
    if (lastItemIndex < 0)
    {
        return;
    }
    
    NSIndexPath *lastIndexPath = [NSIndexPath indexPathForRow:lastItemIndex inSection:0];
    [self.messageView scrollToRowAtIndexPath:lastIndexPath atScrollPosition:UITableViewScrollPositionBottom animated:NO];
}

#pragma mark like
- (void)updateLikeAnimation:(NSUInteger)count
{
    if (count == 0)
        return;
    
    self.likeCount += count;
    if (self.timer == nil)
    {
        self.timer = [NSTimer scheduledTimerWithTimeInterval:0.3 target:self selector:@selector(onLikeAnimation) userInfo:nil repeats:YES];
    }
}

- (void)onLikeAnimation
{
    [self.likeView doLikeAnimation];
    self.likeCount -= 1;
    if (self.likeCount == 0)
    {
        [self.timer invalidate];
        self.timer = nil;
    }
}

#pragma mark UITableView DataSource & delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.liveMessageList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    NSString *cellID = @"liveMessageIdentifier";
    ZegoMessageTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    if (!cell)
    {
        cell = [[ZegoMessageTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellID];
    }
    
    if (indexPath.row >= self.liveMessageList.count)
        return cell;
    
    cell.layout = self.liveMessageList[indexPath.row];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if (indexPath.row >= self.liveMessageList.count)
        return 0.0;
    
    YYTextLayout *layout = self.liveMessageList[indexPath.row];
    
    return layout.textBoundingSize.height;
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    return NO;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
