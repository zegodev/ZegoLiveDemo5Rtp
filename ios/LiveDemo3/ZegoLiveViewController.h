//
//  ZegoLiveViewController.h
//  LiveDemo3
//
//  Created by Strong on 16/6/28.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZegoAVKitManager.h"
#import "ZegoAnchorOptionViewController.h"

#define kRtmpKey        @"rtmp"
#define kHlsKey         @"Hls"
#define kFirstAnchor    @"first"
#define kMixStreamID    @"mixStreamID"

@interface ZegoLiveViewController : UIViewController <ZegoAnchorOptionDelegate>

//YES 启用摄像头
@property (nonatomic, assign) BOOL enableCamera;
//YES 使用前置摄像头
@property (nonatomic, assign) BOOL useFrontCamera;
//预览镜像
@property (nonatomic, assign) BOOL enablePreviewMirror;
//采集镜像
@property (nonatomic, assign) BOOL enableCaptureMirror;
//YES 开启麦克风
@property (nonatomic, assign) BOOL enableMicrophone;
//YES 开启手电筒
@property (nonatomic, assign) BOOL enableTorch;
//采集监听
@property (nonatomic, assign) BOOL enableLoopback;
//设置美颜效果
@property (nonatomic, assign) ZegoBeautifyFeature beautifyFeature;
//设置滤镜
@property (nonatomic, assign) ZegoFilter filter;
//设置是否支持预览
@property (nonatomic, assign) BOOL enablePreview;
//设置视频view格式（等比缩放，等比缩放填充，填充整个视图等)
@property (nonatomic, assign) ZegoVideoViewMode viewMode;
//YES 扬声器打开
@property (nonatomic, assign) BOOL enableSpeaker;
//YES 混音
@property (nonatomic, assign) BOOL enableAux;
//YES 合唱
@property (nonatomic, assign) BOOL enableMixEnginePlayout;
//虚拟立体声
@property (nonatomic, assign) BOOL enableVirtualStereo;
//混响
@property (nonatomic, assign) BOOL enableReverb;
//日志记录
@property (nonatomic, strong) NSMutableArray *logArray;
//帧率，码率信息
@property (nonatomic, strong) NSMutableArray *staticsArray;
//支持的最大流数量
@property (nonatomic, assign, readonly) NSUInteger maxStreamCount;

// getRoomList 时获取到的 streamId
@property (nonatomic, copy) NSArray *streamIdList;

// 设置主播配置
- (void)setAnchorConfig:(UIView *)publishView;

// 设备是否为 iOS7 系统
- (BOOL)isDeviceiOS7;

// 设置更新视图约束
- (BOOL)setContainerConstraints:(UIView *)view containerView:(UIView *)containerView viewCount:(NSUInteger)viewCount;
- (void)updateContainerConstraintsForTap:(UIView *)tapView containerView:(UIView *)containerView;
- (void)updateContainerConstraintsForRemove:(UIView *)removeView containerView:(UIView *)containerView;

- (void)showPublishOption;
- (void)showLogViewController;

//收到请求连麦消息，弹框提示
- (void)requestPublishAlert:(ZegoUser *)requestUser seq:(int)seq;
//被主播拒绝后的提示
- (void)requestPublishResultAlert:(NSString *)fromUserName;

- (BOOL)shouldShowPublishAlert;

// 主播端处理收到连麦请求
- (void)onReceiveJoinLive:(NSString *)userId userName:(NSString *)userName seq:(int)seq;
// 主播端响应连麦请求
- (void)sendRequestPublishRespond:(BOOL)agreed seq:(int)seq requestPublisher:(ZegoUser *)requestUser;

// 观众端处理收到的邀请连麦请求
- (void)onReceiveRequestJoinLive:(NSString *)userId userName:(NSString *)userName seq:(int)seq;
// 观众端响应邀请连麦请求
- (void)sendInviteRequestRespond:(BOOL)agreed seq:(int)seq requestPublisher:(ZegoUser *)requestUser;

// 保持屏幕常亮
- (void)setIdelTimerDisable:(BOOL)disable;

// 电话监听处理函数
- (void)audioSessionWasInterrupted:(NSNotification *)notification;
// 添加 log（可在日志界面更新）
- (void)addLogString:(NSString *)logString;
// 更新直播质量
- (void)updateQuality:(int)quality detail:(NSString *)detail onView:(UIView *)playerView;

// 混流时的回调实现
- (void)auxCallback:(void *)pData dataLen:(int *)pDataLen sampleRate:(int *)pSampleRate channelCount:(int *)pChannelCount;

// 获取第一个view
- (UIView *)getFirstViewInContainer:(UIView *)containerView;

// 分享到QQ
- (void)shareToQQ:(NSString *)hls rtmp:(NSString *)rtmp bizToken:(NSString *)bizToken bizID:(NSString *)bizID streamID:(NSString *)streamID;

- (NSString *)encodeDictionaryToJSON:(NSDictionary *)dictionary;
- (NSDictionary *)decodeJSONToDictionary:(NSString *)json;

- (NSString *)addStaticsInfo:(BOOL)publish stream:(NSString *)streamID fps:(double)fps kbs:(double)kbs akbs:(double)akbs rtt:(int)rtt pktLostRate:(int)pktLostRate;

@end


