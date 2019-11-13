//
//  ZGKeyCenter.h
//  AudioLive
//
//  Created by jeffreypeng on 2019/8/5.
//  Copyright © 2019 ZEGO. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZGKeyCenter : NSObject

// appID， 从即构主页申请
+ (unsigned int)appID;

// appSign，从即构主页申请
+ (NSData *)appSign;

// 国际版 appID
+ (unsigned int)appIDOfI18N;

// 国际版 appSign
+ (NSData *)appSignOfI18N;

@end

NS_ASSUME_NONNULL_END
