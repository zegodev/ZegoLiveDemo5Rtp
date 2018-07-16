//
//  ZegoShareLogViewController.m
//  LiveDemo3
//
//  Created by summery on 31/08/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

#import "ZegoShareLogViewController.h"
#import <SSZipArchive/SSZipArchive.h>

@interface ZegoShareLogViewController () <UITableViewDelegate,UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *logTableView;

@property (nonatomic, strong) NSMutableDictionary *logFiles;    // 用于展示 log 界面条目（日志文件名: 日志文件路径）

@property (nonatomic, strong) NSMutableArray *srcLogFilePaths;  // 日志文件路径，需要压缩为一个文件
@property (nonatomic, copy) NSString *dstLogFilePath;           // 压缩后的文件路径

@property (nonatomic, strong) UIDocumentInteractionController *documentController;

@end

@implementation ZegoShareLogViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.logTableView.tableFooterView = [[UIView alloc] init];
    
    // 处理各种 path
    NSString *cachesPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject];
    NSString *zegologs = [cachesPath stringByAppendingString:@"/ZegoLogs"];
    
    // 日志压缩文件路径
    self.dstLogFilePath = [zegologs stringByAppendingPathComponent:@"/zegoavlog.zip"];
    
    // 获取 Library/Caches/ZegoLogs 目录下的所有文件
    NSFileManager *manager = [NSFileManager defaultManager];
    NSArray *files = [manager subpathsAtPath:zegologs];
    
    NSMutableDictionary *logFiles = [NSMutableDictionary dictionaryWithCapacity:1];
    NSMutableArray *srcLogs = [NSMutableArray arrayWithCapacity:1];
    [files enumerateObjectsUsingBlock:^(NSString *obj, NSUInteger idx, BOOL * stop) {
        // 取出 ZegoLogs 下的 txt 日志文件
        if ([obj hasSuffix:@".txt"]) {
            NSString *logFileDir = [NSString stringWithFormat:@"%@/%@", zegologs, obj];
            [srcLogs addObject:logFileDir];
            [logFiles setObject:logFileDir forKey:obj];
        }
    }];
    
    self.logFiles = logFiles;
    self.srcLogFilePaths = srcLogs;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)dealloc {
    // 清理环境，删除当次的 zip 文件
    NSError *error;
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:self.dstLogFilePath]) {
        [[NSFileManager defaultManager] removeItemAtPath:self.dstLogFilePath error:&error];
        if (error) {
            NSLog(@"分享日志界面销毁，删除日志 zip 文件失败");
        } else {
            NSLog(@"分享日志界面销毁，删除日志 zip 文件成功");
        }
    } else {
         NSLog(@"分享日志界面销毁，日志 zip 文件不存在，不需要删除");
    }

}

#pragma mark - Event response
- (IBAction)close:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)share:(id)sender {
    // 压缩日志文件为 zip 格式
    if ([SSZipArchive createZipFileAtPath:self.dstLogFilePath withFilesAtPaths:self.srcLogFilePaths]) {
        UIDocumentInteractionController *controller = [UIDocumentInteractionController interactionControllerWithURL:[NSURL fileURLWithPath:self.dstLogFilePath]];
        self.documentController = controller;
        [self.documentController presentOpenInMenuFromRect:self.view.bounds inView:self.view animated:YES];
    } else {
        [self showAlert:NSLocalizedString(@"分享日志文件失败", nil) message:NSLocalizedString(@"压缩日志文件失败，请稍后重试", nil)];
    }
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

#pragma mark - UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.logFiles allKeys].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"logFileIdentifier"];
    [cell.textLabel setText:[self.logFiles allKeys][indexPath.row]];
    [cell.detailTextLabel setText:[self.logFiles allValues][indexPath.row]];
    
    return cell;
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 80;
}

@end
