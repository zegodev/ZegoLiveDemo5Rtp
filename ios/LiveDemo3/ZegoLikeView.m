//
//  ZegoLikeView.m
//  LiveDemo3
//
//  Created by Strong on 2017/1/5.
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#import "ZegoLikeView.h"

@interface ZegoLikeView () <CAAnimationDelegate>

@property (nonatomic, strong) NSMutableArray *keepArray;
@property (nonatomic, strong) NSMutableArray *deleteArray;
@property (nonatomic, assign) NSInteger likeCount;

@end

@implementation ZegoLikeView

- (NSMutableArray *)keepArray
{
    if (!_keepArray)
        _keepArray = [[NSMutableArray alloc] init];
    
    return _keepArray;
}

- (NSMutableArray *)deleteArray
{
    if (!_deleteArray)
        _deleteArray = [[NSMutableArray alloc] init];
    
    return _deleteArray;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self)
    {
        self.likeCount = 0;
    }
    
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.likeCount = 0;
    }
    
    return self;
}

- (void)doLikeAnimation
{
    self.likeCount += 1;
    if (self.likeCount == INT_MAX)
        self.likeCount = 0;
    
    CALayer *shipLayer = nil;
    if (self.deleteArray.count > 0)
    {
        shipLayer = [self.deleteArray firstObject];
        [self.deleteArray removeObject:shipLayer];
    }
    else
    {
        NSArray *imageList = @[@"live_like_s_blue",@"live_like_s_grn",@"live_like_s_orange",@"live_like_s_violet",@"live_like_s_yel",@"live_like_s_red"];
        NSInteger index = arc4random() % 6;
        UIImage *image = [UIImage imageNamed:imageList[index]];
        
        shipLayer = [CALayer layer];
        shipLayer.contents = (id)image.CGImage;
        shipLayer.contentsScale = [UIScreen mainScreen].scale;
        shipLayer.frame = CGRectMake(self.bounds.size.width/2.0, self.bounds.size.height/2.0, 35, 35);
    }
    
    shipLayer.opacity = 1.0;
    [self.layer addSublayer:shipLayer];
    [self.keepArray addObject:shipLayer];
    
    [self animationKeyFrameWithlayer:shipLayer];
}

- (void)animationKeyFrameWithlayer:(CALayer *)layer
{
    CGFloat duration = 3 + arc4random() % 5;
    CAKeyframeAnimation *positionAnimate = [CAKeyframeAnimation animationWithKeyPath:@"position"];
    positionAnimate.repeatCount = 1;
    positionAnimate.duration = duration;
    positionAnimate.fillMode = kCAFillModeForwards;
    positionAnimate.removedOnCompletion = NO;
    
    CGPoint position = CGPointMake(self.bounds.size.width/2.0, self.bounds.size.height);
    UIBezierPath *sPath = [UIBezierPath bezierPath];
    [sPath moveToPoint:position];
    CGFloat sign = arc4random() % 2 == 1 ? 1 : -1;
    CGFloat controlPointValue = (arc4random() % 50 + arc4random() % 100) * sign;
    [sPath addCurveToPoint:CGPointMake(position.x, position.y - 300) controlPoint1:CGPointMake(position.x - controlPointValue, position.y - 150) controlPoint2:CGPointMake(position.x + controlPointValue, position.y - 150)];
    positionAnimate.path = sPath.CGPath;
    
    CABasicAnimation *scaleAnimation = [CABasicAnimation animationWithKeyPath:@"transform.scale"];
    scaleAnimation.fromValue = @(0.01);
    scaleAnimation.toValue = @(1.0);
    scaleAnimation.duration = 0.3;
    
    CABasicAnimation *alphaAnimation = [CABasicAnimation animationWithKeyPath:@"opacity"];
    alphaAnimation.fromValue = @(1.0);
    alphaAnimation.toValue = @(0);
    alphaAnimation.duration = duration;
    alphaAnimation.fillMode = kCAFillModeForwards;
    
    CAAnimationGroup *animationGroup = [CAAnimationGroup animation];
    animationGroup.repeatCount = 1;
    animationGroup.removedOnCompletion = NO;
    animationGroup.duration = duration;
    animationGroup.fillMode = kCAFillModeForwards;
    animationGroup.animations = @[scaleAnimation, positionAnimate, alphaAnimation];
    animationGroup.delegate = self;
    
//    [layer addAnimation:animationGroup forKey:[NSString stringWithFormat:@"animation%zd", self.likeCount]];
    [layer addAnimation:animationGroup forKey:@"animation"];
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    CALayer *layer = [anim valueForKey:@"animation"];
    if (layer)
    {
        [layer removeAllAnimations];
        [self.deleteArray addObject:layer];
        [layer removeFromSuperlayer];
        [self.keepArray removeObject:layer];
    }
}

@end
