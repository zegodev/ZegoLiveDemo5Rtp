//
//  ZegoAnchorOptionViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/23.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoAnchorOptionViewController.h"
#import "ZegoAVKitManager.h"

@interface ZegoAnchorOptionSwitchCell ()

@end

@implementation ZegoAnchorOptionSwitchCell

@end

@interface ZegoAnchorOptionPickerCell ()

@end

@implementation ZegoAnchorOptionPickerCell

@end

@interface ZegoAnchorOptionViewController () <UIPickerViewDelegate, UIPickerViewDataSource, UITableViewDataSource, UITableViewDelegate>

@property (readonly) NSArray *beautifyList;
@property (readonly) NSArray *filterList;

@property (nonatomic, weak) UIPickerView *beautifyPicker;
@property (nonatomic, weak) UIPickerView *filterPicker;

@property (nonatomic, weak) IBOutlet UITableView *tableView;

@property (nonatomic, assign, readonly) BOOL useFrontCamera;
@property (nonatomic, assign, readonly) BOOL enableMicrophone;
@property (nonatomic, assign, readonly) BOOL enableTorch;
@property (nonatomic, assign, readonly) NSUInteger beautifyRow;
@property (nonatomic, assign, readonly) NSUInteger filterRow;
@property (nonatomic, assign, readonly) BOOL enableCamera;
@property (nonatomic, assign, readonly) BOOL enableAux;

@property (nonatomic, assign, readonly) BOOL enablePreviewMirror;
@property (nonatomic, assign, readonly) BOOL enableCaptureMirror;
@property (nonatomic, assign, readonly) BOOL enableLoopback;
@property (nonatomic, assign, readonly) BOOL enableMixEnginePlayout;

@property (nonatomic, assign, readonly) BOOL enableVirtualStereo;
@property (nonatomic, assign, readonly) BOOL enableReverb;
@end

@implementation ZegoAnchorOptionViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
    _beautifyList = @[
                      NSLocalizedString(@"无美颜", nil),
                      NSLocalizedString(@"磨皮", nil),
                      NSLocalizedString(@"全屏美白", nil),
                      NSLocalizedString(@"磨皮＋全屏美白", nil),
                      NSLocalizedString(@"磨皮+皮肤美白", nil)
                      ];
    
    _filterList = @[
                    NSLocalizedString(@"无滤镜", nil),
                    NSLocalizedString(@"简洁", nil),
                    NSLocalizedString(@"黑白", nil),
                    NSLocalizedString(@"老化", nil),
                    NSLocalizedString(@"哥特", nil),
                    NSLocalizedString(@"锐色", nil),
                    NSLocalizedString(@"淡雅", nil),
                    NSLocalizedString(@"酒红", nil),
                    NSLocalizedString(@"青柠", nil),
                    NSLocalizedString(@"浪漫", nil),
                    NSLocalizedString(@"光晕", nil),
                    NSLocalizedString(@"蓝调", nil),
                    NSLocalizedString(@"梦幻", nil),
                    NSLocalizedString(@"夜色", nil)
                    ];
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onClose:)];
    [self.view addGestureRecognizer:tapGesture];
    
    self.tableView.layer.cornerRadius = 5.0;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onHeadSetStateChange:) name:kHeadSetStateChangeNotification object:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onClose:(UITapGestureRecognizer *)recognizer {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)onHeadSetStateChange:(NSNotification *)notification
{
    [self.tableView reloadData];
}

#pragma mark getter
- (BOOL)useFrontCamera
{
    if ([self.delegate respondsToSelector:@selector(onGetUseFrontCamera)])
        return [self.delegate onGetUseFrontCamera];
    
    return NO;
}

- (BOOL)enableMicrophone
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableMicrophone)])
        return [self.delegate onGetEnableMicrophone];
    
    return NO;
}

- (BOOL)enableTorch
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableTorch)])
        return [self.delegate onGetEnableTorch];
    
    return NO;
}

- (NSUInteger)beautifyRow
{
    if ([self.delegate respondsToSelector:@selector(onGetSelectedBeautify)])
        return [self.delegate onGetSelectedBeautify];
    
    return 0;
}

- (NSUInteger)filterRow
{
    if ([self.delegate respondsToSelector:@selector(onGetSelectedFilter)])
        return [self.delegate onGetSelectedFilter];
    
    return 0;
}

- (BOOL)enableCamera
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableCamera)])
        return [self.delegate onGetEnableCamera];
    
    return NO;
}

- (BOOL)enableAux
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableAux)])
        return [self.delegate onGetEnableAux];
    
    return NO;
}

- (BOOL)enablePreviewMirror
{
    if ([self.delegate respondsToSelector:@selector(onGetEnablePreviewMirror)])
        return [self.delegate onGetEnablePreviewMirror];
    
    return NO;
}

- (BOOL)enableCaptureMirror
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableCaptureMirror)])
        return [self.delegate onGetEnableCaptureMirror];
    
    return NO;
}

- (BOOL)enableLoopback
{
    if ([self.delegate respondsToSelector:@selector(onGetEnableLoopback)])
        return [self.delegate onGetEnableLoopback];
    
    return NO;
}

- (BOOL)enableVirtualStereo
{
    if([self.delegate respondsToSelector:@selector(onGetEnableVirtualStereo)])
        return [self.delegate onGetEnableVirtualStereo];
    
    return NO;
}

- (BOOL)enableReverb
{
    if([self.delegate respondsToSelector:@selector(onGetEnableReverb)])
        return [self.delegate onGetEnableReverb];
    
    return NO;
}

#pragma mark -- UIPickerViewDelegate, UIPickerViewDataSource
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    if (pickerView == self.beautifyPicker) {
        return self.beautifyList.count;
    } else {
        return self.filterList.count;
    }
}

- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    NSArray *dataList = nil;
    if (pickerView == self.beautifyPicker) {
        dataList = self.beautifyList;
    } else {
        dataList = _filterList;
    }
    
    if (row >= dataList.count) {
        return @"Error";
    }
    
    return [dataList objectAtIndex:row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    if (pickerView == self.beautifyPicker)
    {
        if ([self.delegate respondsToSelector:@selector(onSelectedBeautify:)])
            [self.delegate onSelectedBeautify:row];
    }
    else
    {
        if ([self.delegate respondsToSelector:@selector(onSelectedFilter:)])
            [self.delegate onSelectedFilter:row];
    }
}

- (IBAction)toggleFrontCamera:(id)sender
{
    UISwitch *switchCamera = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onUseFrontCamera:)])
        [self.delegate onUseFrontCamera:switchCamera.on];
    
    [self.tableView reloadData];
}

- (IBAction)toggleMicrophone:(id)sender
{
    UISwitch *switchMicrophone = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableMicrophone:)])
        [self.delegate onEnableMicrophone:switchMicrophone.on];
}

- (IBAction)toggleTorch:(id)sender
{
    UISwitch *switchTorch = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableTorch:)])
        [self.delegate onEnableTorch:switchTorch.on];
}

- (IBAction)toggleCamera:(id)sender
{
    UISwitch *switchTorch = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableCamera:)])
        [self.delegate onEnableCamera:switchTorch.on];
    
    [self.tableView reloadData];
}

- (IBAction)toggleAux:(id)sender
{
    UISwitch *switchAux = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableAux:)])
        [self.delegate onEnableAux:switchAux.on];
}

- (IBAction)togglePreviewMirror:(id)sender
{
    UISwitch *switchPreview = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnablePreviewMirror:)])
        [self.delegate onEnablePreviewMirror:switchPreview.on];
}

- (IBAction)toggleCaptureMirror:(id)sender
{
    UISwitch *switchCapture = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableCaptureMirror:)])
        [self.delegate onEnableCaptureMirror:switchCapture.on];
}

- (IBAction)toggleLoopback:(id)sender
{
    UISwitch *switchLoop = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableLoopback:)])
        [self.delegate onEnableLoopback:switchLoop.on];
}

- (IBAction)toggleMixEnginePlayout:(id)sender
{
    UISwitch *switchMix = (UISwitch *)sender;
    if ([self.delegate respondsToSelector:@selector(onEnableMixEnginePlayout:)])
        [self.delegate onEnableMixEnginePlayout:switchMix.on];
}


- (IBAction)toggleVirtualStereo:(id)sender {
    
    UISwitch *switchVirtualStereo = (UISwitch *)sender;
    if([self.delegate respondsToSelector:@selector(onEnableVirtualStereo:)])
        [self.delegate onEnableVirtualStereo:switchVirtualStereo.on];
}

- (IBAction)toggleReverb:(id)sender {
    
    UISwitch *switchReverb = (UISwitch *)sender;
    if([self.delegate respondsToSelector:@selector(onEnableReverb:)])
        [self.delegate onEnableReverb:switchReverb.on];
}

#pragma mark UITableViewDataSource & Delegate
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0)
        return 11;
    
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
        return 44.0;
    else
        return 132.0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0)
        return NSLocalizedString(@"设置", nil);
    else if (section == 1)
        return NSLocalizedString(@"美颜", nil);
    else if (section == 2)
        return NSLocalizedString(@"滤镜", nil);
    
    return nil;
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    return NO;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        ZegoAnchorOptionSwitchCell *cell = (ZegoAnchorOptionSwitchCell *)[tableView dequeueReusableCellWithIdentifier:@"OptionSwitchCell" forIndexPath:indexPath];
        if (indexPath.row == 0)
        {
            cell.titleLabel.text = NSLocalizedString(@"启用摄像头", nil);
            cell.switchButton.on = self.enableCamera;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleCamera:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 1)
        {
            cell.titleLabel.text = NSLocalizedString(@"前置摄像头", nil);
            cell.switchButton.on = self.useFrontCamera;
            cell.switchButton.enabled = YES;
            if (self.enableCamera == NO)
                cell.switchButton.enabled = NO;
            
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleFrontCamera:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 2)
        {
            cell.titleLabel.text = NSLocalizedString(@"预览切换镜像", nil);
            cell.switchButton.on = self.enablePreviewMirror;
            cell.switchButton.enabled = YES;
            if (self.enableCamera == NO)
                cell.switchButton.enabled = NO;
            if (self.useFrontCamera == NO)
                cell.switchButton.enabled = NO;
            
            if ([ZegoDemoHelper recordTime])
                cell.switchButton.enabled = NO;
            
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(togglePreviewMirror:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 3)
        {
            cell.titleLabel.text = NSLocalizedString(@"采集镜像", nil);
            cell.switchButton.on = self.enableCaptureMirror;
            cell.switchButton.enabled = YES;
            if (self.enableCamera == NO)
                cell.switchButton.enabled = NO;
            
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleCaptureMirror:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 4)
        {
            cell.titleLabel.text = NSLocalizedString(@"麦克风", nil);
            cell.switchButton.on = self.enableMicrophone;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleMicrophone:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 5)
        {
            cell.titleLabel.text = NSLocalizedString(@"手电筒", nil);
            cell.switchButton.on = self.enableTorch;
            cell.switchButton.enabled = YES;
            if (self.enableCamera == NO)
                cell.switchButton.enabled = NO;
            
            if (self.useFrontCamera)
                cell.switchButton.enabled = NO;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleTorch:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 6)
        {
            cell.titleLabel.text = NSLocalizedString(@"混音", nil);
            cell.switchButton.on = self.enableAux;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleAux:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 7)
        {
            cell.titleLabel.text = NSLocalizedString(@"采集监听", nil);
            cell.switchButton.on = self.enableLoopback;
            cell.switchButton.enabled = YES;
            
            if (![ZegoDemoHelper useHeadSet])
            {
                cell.switchButton.enabled = NO;
            }
            
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleLoopback:) forControlEvents:UIControlEventValueChanged];
        }
        else if (indexPath.row == 8)
        {
            cell.titleLabel.text = NSLocalizedString(@"合唱", nil);
            cell.switchButton.on = self.enableMixEnginePlayout;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleMixEnginePlayout:) forControlEvents:UIControlEventValueChanged];
            
        }
        else if (indexPath.row == 9)
        {
            cell.titleLabel.text = NSLocalizedString(@"虚拟立体声", nil);
            cell.switchButton.on = self.enableVirtualStereo;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleVirtualStereo:) forControlEvents:UIControlEventValueChanged];
            
        }
        else if (indexPath.row == 10)
        {
            cell.titleLabel.text = NSLocalizedString(@"混响", nil);
            cell.switchButton.on = self.enableReverb;
            cell.switchButton.enabled = YES;
            [cell.switchButton removeTarget:self action:NULL forControlEvents:UIControlEventValueChanged];
            [cell.switchButton addTarget:self action:@selector(toggleReverb:) forControlEvents:UIControlEventValueChanged];
            
        }
        return cell;
    }
    else
    {
        ZegoAnchorOptionPickerCell *cell = (ZegoAnchorOptionPickerCell *)[tableView dequeueReusableCellWithIdentifier:@"OptionPickerCell" forIndexPath:indexPath];
        cell.pickerView.dataSource = self;
        cell.pickerView.delegate = self;
        
        if (indexPath.section == 1)
        {
            self.beautifyPicker = cell.pickerView;
            [cell.pickerView selectRow:self.beautifyRow inComponent:0 animated:NO];
        }
        else
        {
            self.filterPicker = cell.pickerView;
            [cell.pickerView selectRow:self.filterRow inComponent:0 animated:NO];
        }
        
        return cell;
    }
}

@end
