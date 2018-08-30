//
//  PgyUpdateManager.h
//  Pods
//
//  Created by Scott Lei on 15/9/16.
//
//

#import <Foundation/Foundation.h>

@interface PgyUpdateManager : NSObject

+ (PgyUpdateManager *)sharedPgyManager;

/**
 *  Start update manager.
 *  @param appId App ID，you will find it in the website.
 */
- (void)startManagerWithAppId:(NSString *)appId;

/**
 *  Check is there new version that developer uploaded. 
 *  If a new version has been uploaded, user will be prompted to download new version after this 
 *  method was called.
 */
- (void)checkUpdate;

/**
 *  Check is there new version with customized delegate method.
 *
 *  @param delegate Delegate of checkupdate.
 *  @param updateMethodWithDictionary When checkUpdateWithDelegete was called, this delegate method 
 *  will be called, the dicitonary which coantains version information will be passed to this method also.
 *  If there isn't new version ,the dictionary will be null.
 */
- (void)checkUpdateWithDelegete:(id)delegate selector:(SEL)updateMethodWithDictionary;

@end
