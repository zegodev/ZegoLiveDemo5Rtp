//
//  ZegoAnchorToolViewController.h
//  LiveDemo3
//
//  Created by Strong on 2017/1/4.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YYText/YYText.h"
#import "ZegoAVKitManager.h"

@protocol ZegoLiveToolViewControllerDelegate <NSObject>

@optional

- (void)onSendComment:(NSString *)comment;
- (void)onSendLike;

- (void)onOptionButton:(id)sender;
- (void)onMutedButton:(id)sender;
- (void)onLogButton:(id)sender;
- (void)onCloseButton:(id)sender;

- (void)onShareButton:(id)sender;
- (void)onStopPublishButton:(id)sender;

- (void)onJoinLiveButton:(id)sender;
- (void)onEnterFullScreenButton:(id)sender;

- (void)onTapViewPoint:(CGPoint)point;

@end

@interface ZegoLiveToolViewController : UIViewController

@property (nonatomic, weak) id<ZegoLiveToolViewControllerDelegate> delegate;

@property (nonatomic, assign) BOOL isAudience;

@property (nonatomic, weak) IBOutlet UIButton *optionButton;
@property (nonatomic, weak) IBOutlet UIButton *stopPublishButton;
@property (nonatomic, weak) IBOutlet UIButton *mutedButton;
@property (nonatomic, weak) IBOutlet UIButton *shareButton;

@property (nonatomic, weak) IBOutlet UIButton *joinLiveButton;
@property (nonatomic, weak) IBOutlet UIButton *fullScreenButton;
@property (nonatomic, weak) IBOutlet UIButton *joinLiveOptionButton;
@property (nonatomic, weak) IBOutlet UIButton *playMutedButton;

@property (nonatomic, weak) IBOutlet UILabel *renderLabel;

@property (nonatomic, weak) IBOutlet UILabel *timeLabel;

//- (void)updateLayout:(NSArray<ZegoComment *> *)commentList;
- (void)updateLayout:(NSArray<ZegoRoomMessage *> *)messageList;

- (void)updateLikeAnimation:(NSUInteger)count;

- (void)startTimeRecord;
- (void)stopTimeRecord;

@end
