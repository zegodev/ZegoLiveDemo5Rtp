//
//  ZegoNavigationViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoNavigationViewController.h"


@interface ZegoNavigationViewController ()

@end

@implementation ZegoNavigationViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
}

- (BOOL)shouldAutorotate
{
    if ([self.topViewController respondsToSelector:@selector(shouldAutorotate)])
        return [self.topViewController shouldAutorotate];
    
    return YES;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    if ([self.topViewController respondsToSelector:@selector(supportedInterfaceOrientations)])
        return [self.topViewController supportedInterfaceOrientations];
    
    return UIInterfaceOrientationMaskAllButUpsideDown;
}

@end
