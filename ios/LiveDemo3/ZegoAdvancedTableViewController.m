//
//  ZegoAdvancedTableViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/30.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoAdvancedTableViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"

@interface ZegoAdvancedTableViewController () <UITextFieldDelegate, UITextViewDelegate>

@property (weak, nonatomic) IBOutlet UISwitch *captureSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *renderSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *filterSwitch;

@property (weak, nonatomic) IBOutlet UISwitch *encodeSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *decodeSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *rateControlSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *reverbSwitch;

@property (weak, nonatomic) IBOutlet UISwitch *timeSwitch;

@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;

@end

@implementation ZegoAdvancedTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self updateUIView];
    
    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onAlphaEnv:)];
    gesture.numberOfTapsRequired = 5;
    [self.tableView addGestureRecognizer:gesture];
}

- (void)onAlphaEnv:(UIGestureRecognizer *)gesture
{
    BOOL alpha = [ZegoDemoHelper usingAlphaEnv];    
    [ZegoDemoHelper setUsingAlphaEnv:(!alpha)];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"测试环境" message:alpha ? @"关闭Alpha环境" : @"打开Alpha环境" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}

- (IBAction)toggleCapture:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingExternalCapture:s.on];
}

- (IBAction)toggleRender:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingExternalRender:s.on];
}

- (IBAction)toggleFilter:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingExternalFilter:s.on];
}

- (IBAction)toggleEncode:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingHardwareEncode:s.on];
    [self updateUIView];
}

- (IBAction)toggleDecode:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingHardwareDecode:s.on];
}

- (IBAction)toggleRateControl:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setEnableRateControl:s.on];
    [self updateUIView];
}

- (IBAction)toggleReverb:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setEnableReverb:s.on];
}

- (IBAction)toggleTime:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setRecordTime:s.on];
    [self updateUIView];
}

- (IBAction)toggleInternational:(id)sender
{
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingInternationDomain:s.on];
}

- (void)updateUIView
{

#if TARGET_OS_SIMULATOR
    self.captureSwitch.enabled = NO;
#endif
    
    self.captureSwitch.on = [ZegoDemoHelper usingExternalCapture];
    self.renderSwitch.on = [ZegoDemoHelper usingExternalRender];
    self.filterSwitch.on = [ZegoDemoHelper usingExternalFilter];
    
    self.encodeSwitch.on = [ZegoDemoHelper usingHardwareEncode];
    self.decodeSwitch.on = [ZegoDemoHelper usingHardwareDecode];
    self.rateControlSwitch.on = [ZegoDemoHelper rateControlEnabled];
    
    self.reverbSwitch.on = [ZegoDemoHelper reverbEnabled];
    
    self.timeSwitch.on = [ZegoDemoHelper recordTime];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    
}

- (void)onTapTableView:(UIGestureRecognizer *)gesture
{
    [self.view endEditing:YES];
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (self.tapGesture == nil)
        self.tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapTableView:)];
    
    [self.tableView addGestureRecognizer:self.tapGesture];
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    if (self.tapGesture)
    {
        [self.tableView removeGestureRecognizer:self.tapGesture];
        self.tapGesture = nil;
    }
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if ([text isEqualToString:@"\n"])
    {
        [textView resignFirstResponder];
        return NO;
    }
    
    return YES;
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    if (self.tapGesture == nil)
        self.tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapTableView:)];
    
    [self.tableView addGestureRecognizer:self.tapGesture];
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    if (self.tapGesture)
    {
        [self.tableView removeGestureRecognizer:self.tapGesture];
        self.tapGesture = nil;
    }
}

@end
