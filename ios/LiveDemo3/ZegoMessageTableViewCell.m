//
//  ZegoMessageTableViewCell.m
//  LiveDemo3
//
//  Created by Strong on 2017/1/4.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoMessageTableViewCell.h"

@implementation ZegoMessageTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self)
    {
        self.translatesAutoresizingMaskIntoConstraints = YES;
        
        _contentLabel = [[YYLabel alloc] init];
        self.contentLabel.numberOfLines = 0;
        self.contentLabel.displaysAsynchronously = YES;
        self.contentLabel.textVerticalAlignment = YYTextVerticalAlignmentCenter;
        self.contentLabel.textAlignment = NSTextAlignmentLeft;
        self.contentLabel.fadeOnAsynchronouslyDisplay = NO;
        
        [self.contentView addSubview:self.contentLabel];
        self.contentView.backgroundColor = [UIColor clearColor];
        self.backgroundColor = [UIColor clearColor];
    }
    
    return self;
}

- (void)setLayout:(YYTextLayout *)layout
{
    CGFloat height = layout.textBoundingSize.height;
    self.contentView.frame = CGRectMake(0, 0, self.frame.size.width, height);
    self.contentLabel.frame = CGRectMake(0, 0, self.frame.size.width, height);
    self.contentLabel.textLayout = layout;
}

@end
