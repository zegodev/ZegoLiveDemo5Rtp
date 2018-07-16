//
//  ZegoWerewolfInTurnViewController.h
//  LiveDemo3
//
//  Created by Strong on 2017/3/27.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoSettings.h"
#import "ZegoWerewolfBaseViewController.h"

@interface ZegoWerewolfInTurnViewController : ZegoWerewolfBaseViewController

@property (nonatomic, copy) NSString *roomID;

@property (nonatomic, copy) NSString *anchorID;
@property (nonatomic, copy) NSString *anchorName;

@end
