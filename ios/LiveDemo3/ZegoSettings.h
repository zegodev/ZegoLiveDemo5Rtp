//
//  ZegoSettings.h
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZegoAVKitManager.h"
#import "ZegoRoomInfo.h"

@interface ZegoSettings : NSObject
{
    ZegoAVConfig *_currentConfig;
}

+ (instancetype)sharedInstance;

@property (nonatomic, copy) NSString *userID;
@property (nonatomic, copy) NSString *userName;

@property (nonatomic, readonly) NSArray *appTypeList;

@property (readonly) NSArray *presetVideoQualityList;
@property (nonatomic, strong) ZegoAVConfig *currentConfig;
@property (readonly) NSInteger presetIndex;
@property (nonatomic, assign) int beautifyFeature;
@property (readonly) CGSize currentResolution;

- (BOOL)selectPresetQuality:(NSInteger)presetIndex;
- (ZegoUser *)getZegoUser;
- (UIImage *)getBackgroundImage:(CGSize)viewSize withText:(NSString *)text;
- (NSUserDefaults *)myUserDefaults;

- (UIViewController *)getViewControllerFromRoomInfo:(ZegoRoomInfo *)roomInfo;

@end
