//
//  ZGAppSupportHelper.h
//  ZGAppSupportHelper
//
//  Created by Randy Qiu on 2019/1/4.
//

#import <Foundation/Foundation.h>
#import "ZGAppSupport.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZGAppSupportHelper : NSObject

+ (instancetype)sharedInstance;
- (ZGAppSupport*)api;

@end

NS_ASSUME_NONNULL_END
