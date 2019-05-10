//
//  ZegoSetTableViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoSetTableViewController.h"
#import "ZegoAVKitManager.h"
#import "ZegoSettings.h"
#import "ZegoTestPullViewController.h"
#import "ZegoTestPushViewController.h"
#import <MessageUI/MessageUI.h>
#import <SafariServices/SFSafariViewController.h>
#import <SSZipArchive/SSZipArchive.h>
#import <QRCodeReaderViewController/QRCodeReaderViewController.h>
#import <QRCodeReaderViewController/QRCodeReader.h>
#import "ZegoShareLogViewController.h"

@interface ZegoSetTableViewController () <UITextFieldDelegate, MFMailComposeViewControllerDelegate, QRCodeReaderDelegate>

@property (weak, nonatomic) IBOutlet UILabel *appVersion;
@property (weak, nonatomic) IBOutlet UILabel *sdkVersion;
@property (weak, nonatomic) IBOutlet UILabel *veVersion;

@property (weak, nonatomic) IBOutlet UISwitch *testEnvSwitch;
@property (weak, nonatomic) IBOutlet UIPickerView *appTypePicker;

@property (weak, nonatomic) IBOutlet UITextField *userID;
@property (weak, nonatomic) IBOutlet UITextField *userName;

@property (weak, nonatomic) IBOutlet UIPickerView *presetPicker;
@property (weak, nonatomic) IBOutlet UILabel *videoResolution;
@property (weak, nonatomic) IBOutlet UILabel *videoFrameRate;
@property (weak, nonatomic) IBOutlet UILabel *videoBitRate;
@property (weak, nonatomic) IBOutlet UISlider *videoResolutionSlider;
@property (weak, nonatomic) IBOutlet UISlider *videoFrameRateSlider;
@property (weak, nonatomic) IBOutlet UISlider *videoBitRateSlider;

@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;

@end

@implementation ZegoSetTableViewController

#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.videoResolutionSlider.maximumValue = 5;
    
    self.tableView.contentInset = UIEdgeInsetsMake(0, 0, 44, 0);
    
    // 测试推拉流彩蛋
    UILongPressGestureRecognizer *longPressGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(testPullAndPushStream:)];
    [self.tableView addGestureRecognizer:longPressGesture];
    
    // 发送日志邮件彩蛋
//    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(shareLogFile)];
//    gesture.numberOfTapsRequired = 5;
//    [self.tableView addGestureRecognizer:gesture];

}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self loadEnvironmentSettings];
    [self loadVideoSettings];
    [self loadAccountSettings];
}

- (void)viewWillDisappear:(BOOL)animated {
    if (self.userID.text.length != 0 && self.userName.text.length != 0)
    {
        [ZegoSettings sharedInstance].userID = self.userID.text;
        [ZegoSettings sharedInstance].userName = self.userName.text;
    }
    
    [super viewWillDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardWillHideNotification
                                                  object:nil];
}

- (void)dealloc {

}

#pragma mark - Event response

- (void)onTapTableView:(UIGestureRecognizer *)gesture
{
    [self.view endEditing:YES];
}

- (IBAction)toggleTestEnv:(id)sender {
    UISwitch *s = (UISwitch *)sender;
    [ZegoDemoHelper setUsingTestEnv:s.on];
}

- (IBAction)sliderDidChange:(id)sender {
    // 手动变更slider数值后，presetPicker自动切换到自定义模式
    [self.presetPicker selectRow:[ZegoSettings sharedInstance].presetVideoQualityList.count - 1 inComponent:0 animated:YES];
    
    ZegoAVConfig *config = [ZegoSettings sharedInstance].currentConfig;
    
    if (sender == self.videoResolutionSlider) {
        int v = (int)self.videoResolutionSlider.value;
        CGSize resolution = CGSizeMake(360, 640);
        switch (v)
        {
            case 0:
                resolution = CGSizeMake(180, 320);
                break;
            case 1:
                resolution = CGSizeMake(270, 480);
                break;
            case 2:
                resolution = CGSizeMake(360, 640);
                break;
            case 3:
                resolution = CGSizeMake(540, 960);
                break;
            case 4:
                resolution = CGSizeMake(720, 1280);
                break;
            case 5:
                resolution = CGSizeMake(1080, 1920);
                break;
                
            default:
                break;
        }
        config.videoEncodeResolution = resolution;
        config.videoCaptureResolution = resolution;
    } else if (sender == self.videoFrameRateSlider) {
        int v = (int)self.videoFrameRateSlider.value;
        config.fps = v;
    } else if (sender == self.videoBitRateSlider) {
        int v = (int)self.videoBitRateSlider.value;
        config.bitrate = v;
    }
    
    [ZegoSettings sharedInstance].currentConfig = config;
    [self updateVideoSettingUI];
}

#pragma mark -- Test egg

- (void)testPullAndPushStream:(UIGestureRecognizer *)gesture {
    if (gesture.state == UIGestureRecognizerStateEnded) {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"指定ID拉/推流", nil) message:nil preferredStyle:UIAlertControllerStyleActionSheet];
        
        UIAlertAction *testPullStream  = [UIAlertAction actionWithTitle:NSLocalizedString(@"指定ID拉流", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [self testPullStream];
        }];
        
        UIAlertAction *testPushStream  = [UIAlertAction actionWithTitle:NSLocalizedString(@"指定ID推流", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [self testPushStream];
        }];
        
        UIAlertAction *cancel = [UIAlertAction actionWithTitle:NSLocalizedString(@"取消", nil) style:UIAlertActionStyleCancel handler:nil];
        
        [alertController addAction:testPullStream];
        [alertController addAction:testPushStream];
        [alertController addAction:cancel];
        
        [self presentViewController:alertController animated:YES completion:nil];
    }
}

- (void)testPullStream {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"指定ID拉流",nil)message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = NSLocalizedString(@"输入Room ID，不可为空",nil);
        textField.clearButtonMode = UITextFieldViewModeWhileEditing;
        textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    }];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = NSLocalizedString(@"输入Stream ID，不可为空",nil);
        textField.clearButtonMode = UITextFieldViewModeWhileEditing;
        textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    }];
    
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:NSLocalizedString(@"确定",nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {

        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        ZegoTestPullViewController *testViewController = (ZegoTestPullViewController *)[storyboard instantiateViewControllerWithIdentifier:@"testPullID"];
        testViewController.roomID = alertController.textFields[0].text;
        testViewController.streamID = alertController.textFields[1].text;
        
        [self presentViewController:testViewController animated:YES completion:nil];
    }];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:NSLocalizedString(@"取消",nil) style:UIAlertActionStyleCancel handler:nil];
    
    [alertController addAction:confirm];
    [alertController addAction:cancel];
    
    [self presentViewController:alertController animated:YES completion:nil];
}

- (void)testPushStream {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"请选择推流模式",nil)message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    
    UIAlertAction *singleAnchorMode  = [UIAlertAction actionWithTitle:NSLocalizedString(@"无连麦模式", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self pushStreamWithFlag:ZEGOAPI_SINGLE_ANCHOR];
    }];
    
    UIAlertAction *multiAnchorMode  = [UIAlertAction actionWithTitle:NSLocalizedString(@"连麦模式", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self pushStreamWithFlag:ZEGOAPI_JOIN_PUBLISH];
    }];
    
    UIAlertAction *mixStreamMode  = [UIAlertAction actionWithTitle:NSLocalizedString(@"混流模式", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self pushStreamWithFlag:ZEGOAPI_MIX_STREAM];
    }];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:NSLocalizedString(@"取消", nil) style:UIAlertActionStyleCancel handler:nil];
    
    [alertController addAction:singleAnchorMode];
    [alertController addAction:multiAnchorMode];
    [alertController addAction:mixStreamMode];
    [alertController addAction:cancel];
    
    [self presentViewController:alertController animated:YES completion:nil];
}

- (void)pushStreamWithFlag:(ZegoAPIPublishFlag)flag {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"指定ID推流",nil)message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = NSLocalizedString(@"输入直播标题",nil);
        textField.clearButtonMode = UITextFieldViewModeWhileEditing;
        textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    }];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = NSLocalizedString(@"输入Room ID，不可为空",nil);
        textField.clearButtonMode = UITextFieldViewModeWhileEditing;
        textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    }];
    
    [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        textField.placeholder = NSLocalizedString(@"输入Stream ID，不可为空",nil);
        textField.clearButtonMode = UITextFieldViewModeWhileEditing;
        textField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
    }];
    
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:NSLocalizedString(@"确定",nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        ZegoTestPushViewController *testViewController = (ZegoTestPushViewController *)[storyboard instantiateViewControllerWithIdentifier:@"testPushID"];
        testViewController.liveTitle = [alertController.textFields[0].text isEqualToString:@""] ? @"指定ID推流测试" : alertController.textFields[0].text;
        testViewController.roomID = alertController.textFields[1].text;
        testViewController.streamID = alertController.textFields[2].text;
        testViewController.flag = flag;
        
        [self presentViewController:testViewController animated:YES completion:nil];
        
    }];
    
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:NSLocalizedString(@"取消",nil) style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
    }];
    
    [alertController addAction:confirm];
    [alertController addAction:cancel];
    
    [self presentViewController:alertController animated:YES completion:nil];
}

#pragma mark - Private method

- (void)loadEnvironmentSettings {
    self.testEnvSwitch.on = [ZegoDemoHelper usingTestEnv];
    [self.appTypePicker selectRow:[ZegoDemoHelper appType] inComponent:0 animated:NO];
    
    [self loadAppID];
}

- (void)loadAppID {
    ZegoAppType type = [ZegoDemoHelper appType];
    
    // 导航栏标题随设置变化
    NSString *title = [NSString stringWithFormat:@"ZEGO(%@)", [ZegoSettings sharedInstance].appTypeList[type]];
    self.tabBarController.navigationItem.title =  NSLocalizedString(title, nil);
}

- (void)loadAccountSettings {
    self.userID.text = [ZegoSettings sharedInstance].userID;
    self.userName.text = [ZegoSettings sharedInstance].userName;
}

- (void)loadVideoSettings {
    self.appVersion.text = [NSString stringWithFormat:@"App: %@", [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]];
    self.sdkVersion.text = [NSString stringWithFormat:@"SDK: %@", [ZegoLiveRoomApi version]];
    self.veVersion.text = [NSString stringWithFormat:@"VE: %@", [ZegoLiveRoomApi version2]];
    
    [self.presetPicker selectRow:[ZegoSettings sharedInstance].presetIndex inComponent:0 animated:YES];
    [self updateVideoSettingUI];
}

- (void)updateVideoSettingUI {
    ZegoAVConfig *config = [[ZegoSettings sharedInstance] currentConfig];
    
    CGSize r = [ZegoSettings sharedInstance].currentResolution;
    self.videoResolution.text = [NSString stringWithFormat:@"%d X %d", (int)r.width, (int)r.height];
    switch ((int)r.height) {
        case 320:
            self.videoResolutionSlider.value = 0;
            break;
        case 480:
        case 352:   // 兼容老版本 288x352
            self.videoResolutionSlider.value = 1;
            break;
        case 640:
            self.videoResolutionSlider.value = 2;
            break;
        case 960:
            self.videoResolutionSlider.value = 3;
            break;
        case 1280:
            self.videoResolutionSlider.value = 4;
            break;
        case 1920:
            self.videoResolutionSlider.value = 5;
            break;
        default:
            break;
    }
    
    self.videoFrameRateSlider.value = config.fps;
    self.videoFrameRate.text = [NSString stringWithFormat:@"%d", config.fps];
    
    self.videoBitRateSlider.value = config.bitrate;
    self.videoBitRate.text = [NSString stringWithFormat:@"%d", config.bitrate];
}

- (void)showUploadAlertView
{
    NSString *message = [NSString stringWithFormat:NSLocalizedString(@"Log Uploaded", nil)];
    //    if ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0)
    {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [alertView show];
    }
}

- (void)shareLogFile {
    [self performSegueWithIdentifier:@"uploadLogIdentifier" sender:nil];
}

- (void)sendEmail {
    if ([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *mailCompose = [[MFMailComposeViewController alloc] init];
        [mailCompose setMailComposeDelegate:self];
        
        // 主体
        NSDate *date = [NSDate date]; //date: 2016-07-07 08:00:04 UTC
        NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
        [formatter setDateFormat:@"YYYYMMddHHmmss"];
        NSString *dateString = [formatter stringFromDate:date]; //dateString: 20160707160333
        
        NSString *subject = [NSString stringWithFormat:@"%d-%@-%@", [ZegoDemoHelper appID], [ZegoSettings sharedInstance].userID, dateString];
        [mailCompose setSubject:[NSString stringWithFormat:@"手动发送日志提醒【%@】", subject]];
        
        // 收件人
        [mailCompose setToRecipients:@[@"zegosdklog@zego.im"]];
        
        // 正文
        NSString *mailContent = @"手动发送日志邮件";
        [mailCompose setMessageBody:mailContent isHTML:NO];
        
        // 附件
        [mailCompose addAttachmentData:[self zipArchiveWithFiles] mimeType:@"application/zip" fileName:@"zegoavlog.zip"];
        
        [self presentViewController:mailCompose animated:YES completion:nil];
        
        // 清理环境，删除当次的 zip 文件
        NSString *zipPath = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingString:@"/ZegoLogs/zegoavlog.zip"];
        NSError *error;
        [[NSFileManager defaultManager] removeItemAtPath:zipPath error:&error];
        if (error) {
            NSLog(@"删除日志 zip 文件失败");
        }
    } else {
        [self showAlert:NSLocalizedString(@"无法发送邮件", nil) message:NSLocalizedString(@"请先在手机的 [设置>邮件] 中添加可使用账户并开启邮件服务!", nil)];
    }
}

- (NSData *)zipArchiveWithFiles {
    NSString *cachesPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject];
    NSString *zegologs = [cachesPath stringByAppendingString:@"/ZegoLogs"];
    
    // 获取 Library/Caches/ZegoLogs 目录下的所有文件
    NSFileManager *manager = [NSFileManager defaultManager];
    NSArray *files = [manager subpathsAtPath:zegologs];
    
    NSMutableArray *logFiles = [NSMutableArray arrayWithCapacity:1];
    [files enumerateObjectsUsingBlock:^(NSString *obj, NSUInteger idx, BOOL * stop) {
        // 取出 ZegoLogs 下的 txt 日志文件
        if ([obj hasSuffix:@".txt"]) {
            NSString *logFile = [NSString stringWithFormat:@"%@/%@", zegologs, obj];
            [logFiles addObject:logFile];
        }
    }];
    
    // 压缩文件
    NSString *zipPath = [zegologs stringByAppendingPathComponent:@"/zegoavlog.zip"];
    BOOL zipSuccess = [SSZipArchive createZipFileAtPath:zipPath withFilesAtPaths:logFiles];

    if (zipSuccess) {
        NSData *data = [[NSData alloc] initWithContentsOfFile:zipPath];
        if (data) {
            return data;
        }
    } else {
        [self showAlert:NSLocalizedString(@"无法发送邮件", nil) message:NSLocalizedString(@"日志文件压缩失败", nil)];
    }
    
    return nil;
    
}

- (void)showAlert:(NSString *)title message:(NSString *)message {
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                   message:message
                                                            preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            [self dismissViewControllerAnimated:YES completion:nil];
    }];
    
    [alert addAction:confirm];
    [self presentViewController:alert animated:NO completion:nil];
}

#pragma mark - UIPickerViewDelegate, UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    if (pickerView == self.presetPicker) {
        return [ZegoSettings sharedInstance].presetVideoQualityList.count;
    } else if (pickerView == self.appTypePicker) {
        return [ZegoSettings sharedInstance].appTypeList.count;
    } else {
        return 0;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    if (pickerView == self.presetPicker)
    {
        if (row >= [ZegoSettings sharedInstance].presetVideoQualityList.count) {
            return ;
        }
        
        NSLog(@"%s: %@", __func__, [ZegoSettings sharedInstance].presetVideoQualityList[row]);
        
        [[ZegoSettings sharedInstance] selectPresetQuality:row];
        
        [self updateVideoSettingUI];
    } else if (pickerView == self.appTypePicker) {
        if (row >= [ZegoSettings sharedInstance].appTypeList.count) {
            return ;
        }
        
        NSLog(@"%s: %@", __func__, [ZegoSettings sharedInstance].appTypeList[row]);

        [ZegoDemoHelper setAppType:(ZegoAppType)row];
        [self loadAppID];
    }
    
    return;
}

//返回当前行的内容,此处是将数组中数值添加到滚动的那个显示栏上
- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    if (pickerView == self.presetPicker)
    {
        if (row >= [ZegoSettings sharedInstance].presetVideoQualityList.count) {
            return @"ERROR";
        }
    
        return [[ZegoSettings sharedInstance].presetVideoQualityList objectAtIndex:row];
    } else if (pickerView == self.appTypePicker) {
        if (row >= [ZegoSettings sharedInstance].appTypeList.count) {
            return @"ERROR";
        }
        
        return [[ZegoSettings sharedInstance].appTypeList objectAtIndex:row];
    }
    return nil;
}

#pragma mark - UITableView delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.section == 1)
    {
        if (indexPath.row == 0)
        {
            [ZegoLiveRoomApi uploadLog];
            [self showUploadAlertView];
        }

    }
    else if (indexPath.section == [self.tableView numberOfSections] - 1)
    {
        SFSafariViewController *safariViewController = [[SFSafariViewController alloc] initWithURL:[NSURL URLWithString:@"https://www.zego.im"]];
        [self presentViewController:safariViewController animated:YES completion:nil];
    }
}

#pragma mark - UIScrollViewDelegate

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
//    if (!self.userID.isEditing && !self.userName.isEditing) {
//        [self.view endEditing:YES];
//    }
//    
//    if (!self.appSignText.isEditing && ![self.appIDText isFirstResponder]) {
//        [self.view endEditing:YES];
//    }
}

#pragma mark - UITextField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (textField.text.length != 0)
    {
        [textField resignFirstResponder];
        return YES;
    } else {
        [self showAlert:NSLocalizedString(@"请重新输入！", nil) message:NSLocalizedString(@"该字段不可为空", nil)];
        [textField becomeFirstResponder];
        return NO;
    }
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

#pragma mark - MFMailComposeViewControllerDelegate

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error {
    switch (result) {
        case MFMailComposeResultCancelled:
            [controller dismissViewControllerAnimated:YES completion:nil];
            break;
        case MFMailComposeResultSaved:
            [controller dismissViewControllerAnimated:YES completion:nil];
            break;
        case MFMailComposeResultSent:
        {
            NSLog(@"日志邮件发送成功");
            
            // 弹框提示
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"日志邮件发送成功", nil)
                                                                           message:nil
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [controller dismissViewControllerAnimated:YES completion:nil];
            }];
            
            [alert addAction:confirm];
            
            [controller presentViewController:alert animated:NO completion:nil];
           
        }
            break;
        case MFMailComposeResultFailed:
        {
            NSLog(@"日志邮件发送失败");
            // 弹框提示
            UIAlertController *alert = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"日志邮件发送失败", nil)
                                                                           message:NSLocalizedString(@"请稍后重试", nil)
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            UIAlertAction *confirm = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                [controller dismissViewControllerAnimated:YES completion:nil];
            }];
            
            [alert addAction:confirm];
            
            [controller presentViewController:alert animated:NO completion:nil];
        }
            break;
    }
}

#pragma mark - QRCode

- (void)beginQRCodeScan {
    if ([QRCodeReader supportsMetadataObjectTypes:@[AVMetadataObjectTypeQRCode]]) {
        static QRCodeReaderViewController *vc = nil;
        static dispatch_once_t onceToken;
        
        dispatch_once(&onceToken, ^{
            QRCodeReader *reader = [QRCodeReader readerWithMetadataObjectTypes:@[AVMetadataObjectTypeQRCode]];
            vc                   = [QRCodeReaderViewController readerWithCancelButtonTitle:@"Cancel" codeReader:reader startScanningAtLoad:YES showSwitchCameraButton:YES showTorchButton:YES];
            vc.modalPresentationStyle = UIModalPresentationFormSheet;
        });
        vc.delegate = self;
        
        //        [vc setCompletionWithBlock:^(NSString *resultAsString) {
        //            NSLog(@"Completion with result: %@", resultAsString);
        //        }];
        
        [self presentViewController:vc animated:YES completion:NULL];
    }
    else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Reader not supported by the current device" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        
        [alert show];
    }
}

@end
