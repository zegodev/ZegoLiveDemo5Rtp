//
//  ZGKeyCenter.m
//  AudioLive
//
//  Created by jeffreypeng on 2019/8/5.
//  Copyright © 2019 ZEGO. All rights reserved.
//

#import "ZGKeyCenter.h"

@implementation ZGKeyCenter

+ (unsigned int)appID {
    return <#请输入自己的AppID#>;
}

// 从即构主页申请
+ (NSData *)appSign {
    Byte signKey[] = <#请输入自己的 appSign#>;
    NSData* sign = [NSData dataWithBytes:signKey length:32];
    return sign;
}

// 国际版 appID
+ (unsigned int)appIDOfI18N {
    // <#请输入自己的 appID#>
    return 1234567890;
}

// 国际版 appSign
+ (NSData *)appSignOfI18N {
    // <#请输入自己的 appSign#>
    Byte signKey[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    NSData* sign = [NSData dataWithBytes:signKey length:32];
    return sign;
}

@end
