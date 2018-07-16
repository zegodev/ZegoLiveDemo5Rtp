//
//  ZegoTestPushViewController.h
//  LiveDemo3
//
//  Created by summery on 02/05/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoLiveViewController.h"

@interface ZegoTestPushViewController : ZegoLiveViewController

//直播标题
@property (nonatomic, copy) NSString *liveTitle;
//预览的界面view
@property (nonatomic, strong) UIView *publishView;

//直播流房间ID
@property (nonatomic, copy) NSString *roomID;
//直播流ID
@property (nonatomic, copy) NSString *streamID;
//直播混流ID
@property (nonatomic, copy) NSString *mixStreamID;
//直播flag
@property (nonatomic, assign) enum ZegoAPIPublishFlag flag;

@end
