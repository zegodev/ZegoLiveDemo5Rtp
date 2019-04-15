//
//  ZegoRoomViewController.m
//  LiveDemo3
//
//  Created by Strong on 16/6/22.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import "ZegoRoomViewController.h"
#import "ZegoRoomInfo.h"
#import "ZegoAVKitManager.h"
#import "ZegoAudienceViewController.h"
#import "ZegoMoreAudienceViewController.h"
#import "ZegoMixStreamAudienceViewController.h"
#import "ZegoRenderAudienceViewController.h"
#import <Foundation/NSURLSession.h>
#import "ZegoSettings.h"
#import <ZGAppSupport/ZGAppSupportHelper.h>
#import <ZGAppSupport/ZGRoomListUpdateListener.h>
#import "ZegoAVKitManager.h"

@implementation ZegoRoomTableViewCell

@end

@interface ZegoRoomViewController () <UITableViewDataSource, UITableViewDelegate, ZGRoomListUpdateListener>
@property (weak, nonatomic) IBOutlet UITableView *liveView;

@property (nonatomic, strong) NSMutableArray<ZegoRoomInfo *>* roomList;

@property (nonatomic, strong) UIRefreshControl *refreshControl;

@property (strong, nonatomic) ZGAppSupport *appSupport;

@end

@implementation ZegoRoomViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _roomList = [NSMutableArray array];
    
    _appSupport = ({
        ZGAppSupport *api = ZGAppSupportHelper.sharedInstance.api;
        [api setAutoConfigParams:ZGAppTypeLiveDemo5 configId:@""];
        [api setRoomListUpdateListener:self];
        api;
    });
    
    _refreshControl = [[UIRefreshControl alloc] init];
    [self.refreshControl addTarget:self action:@selector(handleRefresh:) forControlEvents:UIControlEventValueChanged];
    [self.liveView insertSubview:self.refreshControl atIndex:0];
    
    self.liveView.tableFooterView = [[UIView alloc] init];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onApplicationActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onRoomInstanceClear:)
                                                 name:@"RoomInstanceClear"
                                               object:nil];
    [NSNotificationCenter.defaultCenter addObserver:self
                                           selector:@selector(onReceiveZegoLiveRoomApiInitCompleteNotification)
                                               name:ZegoLiveRoomApiInitCompleteNotification
                                             object:nil];
    
    [self getLiveRoom];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.refreshControl endRefreshing];
    self.refreshControl.hidden = YES;
}

- (void)refreshRoomList
{
    if ([self.refreshControl isRefreshing])
        return;
    
    [self.roomList removeAllObjects];
    [self getLiveRoom];
}

- (void)handleRefresh:(UIRefreshControl *)refreshControl
{
    [self.roomList removeAllObjects];
    [self getLiveRoom];
}

- (void)onApplicationActive:(NSNotification *)notification
{
    [self handleRefresh:self.refreshControl];
}

- (void)onRoomInstanceClear:(NSNotification *)notification
{
    [self getLiveRoom];
}

- (void)onReceiveZegoLiveRoomApiInitCompleteNotification {
    [self getLiveRoom];
}

- (BOOL)isWereWolfRoom:(NSString *)roomID
{
    if ([roomID hasPrefix:@"#i-"] || [roomID hasPrefix:@"#w-"])
        return YES;
    
    return NO;
}

- (void)getLiveRoom
{
    [self.refreshControl beginRefreshing];
    NSLog(@"%d",ZegoDemoHelper.appID);
    [self.appSupport updateRoomList:ZegoDemoHelper.appID];
}

#pragma mark - ZGRoomListUpdateListener
- (void)onUpdateRoomList:(NSArray<ZGRoomInfo *> *)roomList {
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.refreshControl isRefreshing])
            [self.refreshControl endRefreshing];
        
        if ([self.delegate respondsToSelector:@selector(onRefreshRoomListFinished)])
            [self.delegate onRefreshRoomListFinished];
        
        [self.roomList removeAllObjects];
        
        for (ZGRoomInfo *info in roomList) {
            ZegoRoomInfo *roomInfo = [ZegoRoomInfo new];
            roomInfo.roomID = info.roomId;
            roomInfo.roomName = info.roomName;
            roomInfo.anchorID = info.anchorIdName;
            roomInfo.anchorName = info.anchorNickName;
            roomInfo.streamInfo = @[].mutableCopy;
            for (ZGStreamInfo *stream in info.streamInfo) {
                [roomInfo.streamInfo addObject:stream.streamId];
            }
            
            [self.roomList addObject:roomInfo];
        }
        
        [self.liveView reloadData];
    });
}

- (void)onUpdateRoomListError {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"onUpdateRoomListError");
        
        if ([self.refreshControl isRefreshing])
            [self.refreshControl endRefreshing];
        
        if ([self.delegate respondsToSelector:@selector(onRefreshRoomListFinished)])
            [self.delegate onRefreshRoomListFinished];
    });
}

#pragma mark UITableViewDataSource & UITableViewDelegate
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.roomList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ZegoRoomTableViewCell *cell = (ZegoRoomTableViewCell *)[tableView dequeueReusableCellWithIdentifier:@"roomListID" forIndexPath:indexPath];
    
    if (indexPath.row >= self.roomList.count)
        return cell;
    
    ZegoRoomInfo *info = self.roomList[indexPath.row];
    
    if (info.roomName.length == 0)
    {
        if (info.anchorName.length == 0)
            cell.publishTitleLabel.text = info.roomID;
        else
            cell.publishTitleLabel.text = info.anchorName;
    }
    else
    {
        cell.publishTitleLabel.text = info.roomName;
    }
    
    cell.anchorLabel.text = info.anchorName;
    
//    if (info.livesCount > 1)
//    {
//        cell.livesCountLabel.text = [NSString stringWithFormat:NSLocalizedString(@"%lu人正在连麦", nil), (unsigned long)info.livesCount];
//        cell.livesCountLabel.hidden = NO;
//    }
//    else
    {
        cell.livesCountLabel.text = @"";
        cell.livesCountLabel.hidden = YES;
    }
    
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (indexPath.row >= self.roomList.count)
        return;
    
    ZegoRoomInfo *info = [self.roomList objectAtIndex:indexPath.row];
    
    UIViewController *controller = [[ZegoSettings sharedInstance] getViewControllerFromRoomInfo:info];
    if (controller)
        [self presentViewController:controller animated:YES completion:nil];
    
}

@end
