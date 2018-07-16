//
//  ZegoAnchorOptionViewController.h
//  LiveDemo3
//
//  Created by Strong on 16/6/23.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kHeadSetStateChangeNotification     @"headSetStateChange"

@protocol ZegoAnchorOptionDelegate <NSObject>

- (void)onUseFrontCamera:(BOOL)use;
- (void)onEnableMicrophone:(BOOL)enabled;
- (void)onEnableTorch:(BOOL)enable;
- (void)onSelectedBeautify:(NSInteger)row;
- (void)onSelectedFilter:(NSInteger)row;
- (void)onEnableCamera:(BOOL)enabled;
- (void)onEnableAux:(BOOL)enabled;

- (void)onEnablePreviewMirror:(BOOL)enabled;
- (void)onEnableCaptureMirror:(BOOL)enable;
- (void)onEnableLoopback:(BOOL)enable;
- (void)onEnableMixEnginePlayout:(BOOL)enable;

- (void)onEnableVirtualStereo:(BOOL)enable;
- (void)onEnableReverb:(BOOL)enable;

- (BOOL)onGetUseFrontCamera;
- (BOOL)onGetEnableMicrophone;
- (BOOL)onGetEnableTorch;
- (NSInteger)onGetSelectedBeautify;
- (NSInteger)onGetSelectedFilter;
- (BOOL)onGetEnableCamera;
- (BOOL)onGetEnableAux;
- (BOOL)onGetEnablePreviewMirror;
- (BOOL)onGetEnableCaptureMirror;
- (BOOL)onGetEnableLoopback;

- (BOOL)onGetEnableVirtualStereo;
- (BOOL)onGetEnableReverb;
@end

@interface ZegoAnchorOptionSwitchCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UISwitch *switchButton;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;

@end

@interface ZegoAnchorOptionPickerCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UIPickerView *pickerView;

@end

@interface ZegoAnchorOptionViewController : UIViewController

@property (nonatomic, weak) id<ZegoAnchorOptionDelegate> delegate;

@end
