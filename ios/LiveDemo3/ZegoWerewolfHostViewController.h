//
//  ZegoWerewolfHostViewController.h
//  LiveDemo3
//
//  Created by Strong on 2017/3/29.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoWerewolfBaseViewController.h"

@interface ZegoWerewolfHostViewController : ZegoWerewolfBaseViewController

@property (nonatomic, copy) NSString* liveTitle;

@property (nonatomic, assign) BOOL isUtralServer;

@property (nonatomic, assign) BOOL dontStopPublishMode;

@end
