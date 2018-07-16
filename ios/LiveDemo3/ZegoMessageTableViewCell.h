//
//  ZegoMessageTableViewCell.h
//  LiveDemo3
//
//  Created by Strong on 2017/1/4.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YYText/YYText.h"

@interface ZegoMessageTableViewCell : UITableViewCell

@property (nonatomic, strong) YYLabel *contentLabel;
@property (nonatomic, strong) YYTextLayout *layout;

@end
