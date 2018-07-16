//
//  AppDelegate.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "AppDelegate.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoAnchorViewController.h"
#import "ZegoAudienceViewController.h"

#import <TencentOpenAPI/QQApiInterface.h>
#import <TencentOpenAPI/TencentOAuth.h>
#import <Bugly/Bugly.h>

@interface AppDelegate () <UISplitViewControllerDelegate>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [ZegoDemoHelper api];
    
#if !TARGET_OS_SIMULATOR
    (void)[[TencentOAuth alloc] initWithAppId:@"1106054568" andDelegate:nil];
#endif
    
    [self setupBugly];
    return YES;
}

-(void) setupBugly{
    // Get the default config
    BuglyConfig * config = [[BuglyConfig alloc] init];
    
    // Open the debug mode to print the sdk log message.
    // Default value is NO, please DISABLE it in your RELEASE version.
#if DEBUG
    config.debugMode = YES;
#endif
    
    // Open the customized log record and report, BuglyLogLevelWarn will report Warn, Error log message.
    // Default value is BuglyLogLevelSilent that means DISABLE it.
    // You could change the value according to you need.
    config.reportLogLevel = BuglyLogLevelWarn;
    
    // Open the STUCK scene data in MAIN thread record and report.
    // Default value is NO
    config.blockMonitorEnable = YES;
    
    // Set the STUCK THRESHOLD time, when STUCK time > THRESHOLD it will record an event and report data when the app launched next time.
    // Default value is 3.5 second.
    config.blockMonitorTimeout = 1.5;
    
    // Set the app channel to deployment
    config.channel = @"Bugly";
    
    // NOTE:Required
    // Start the Bugly sdk with APP_ID and your config
    [Bugly startWithAppId:@"f5bd615274"
#if DEBUG
        developmentDevice:YES
#endif
                   config:config];
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    if ([url.absoluteString hasPrefix:@"tencent"])
    {
#if !TARGET_OS_SIMULATOR
        return [QQApiInterface handleOpenURL:url delegate:nil];
#else
        return NO;
#endif
    }
    else if ([url.absoluteString hasPrefix:@"ZegoLiveShare2"])
        return [self handleOpenLive:url];
    
    return NO;
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options
{
    if ([url.absoluteString hasPrefix:@"tencent"])
    {
#if !TARGET_OS_SIMULATOR
        return [QQApiInterface handleOpenURL:url delegate:nil];
#else
        return NO;
#endif
    }
    else if ([url.absoluteString hasPrefix:@"zegoliveshare2"])
        return [self handleOpenLive:url];
    
    return NO;
}

- (BOOL)handleOpenLive:(NSURL *)url
{
    UINavigationController *navigationController = (UINavigationController *)self.window.rootViewController;
    if ([navigationController.topViewController isKindOfClass:[ZegoAnchorViewController class]] ||
        [navigationController.topViewController isKindOfClass:[ZegoAudienceViewController class]])
        return YES;
    
    NSMutableDictionary *queryStringDict = [NSMutableDictionary dictionary];
    NSString *urlParams = [[url.absoluteString componentsSeparatedByString:@"?"] lastObject];
    NSArray *urlComponents = [urlParams componentsSeparatedByString:@"&"];
    
    for (NSString *keyValuePair in urlComponents)
    {
        NSArray *pairComponents = [keyValuePair componentsSeparatedByString:@"="];
        NSString *key = [[pairComponents firstObject] stringByRemovingPercentEncoding];
        NSString *value = [[pairComponents lastObject] stringByRemovingPercentEncoding];
        
        [queryStringDict setObject:value forKey:key];
    }
    
    NSLog(@"%@", queryStringDict);
    
    NSString *roomID = queryStringDict[@"id"];
    if (roomID.length == 0)
        return YES;
    
    ZegoRoomInfo *info = [ZegoRoomInfo new];
    info.roomID = roomID;
    
    UIViewController *controller = [[ZegoSettings sharedInstance] getViewControllerFromRoomInfo:info];
    if (controller)
        [self.window.rootViewController presentViewController:controller animated:YES completion:nil];
    
    return YES;
}
@end
