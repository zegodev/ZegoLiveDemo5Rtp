//
//  ZegoLiveRoomDefines.h
//  zegoliveroom
//
//  Copyright © 2017年 ZEGO. All rights reserved.
//

#ifndef ZegoLiveRoomDefines_h
#define ZegoLiveRoomDefines_h

#include "./AVDefines.h"
#include "./RoomDefines.h"


namespace ZEGO
{
    namespace LIVEROOM
    {
        using namespace COMMON;
        using COMMON::ZEGONetType;
        
        using COMMON::ZegoRoomRole;
        
        using COMMON::ZegoStreamInfo;
        
        using COMMON::ZegoStreamUpdateType;
        
        const int kInvalidSeq = -1;
        
        /** 本地预览视频视图的模式 */
        enum ZegoVideoViewMode
        {
            ZegoVideoViewModeScaleAspectFit = 0,    /**< 等比缩放，可能有黑边 */
            ZegoVideoViewModeScaleAspectFill = 1,   /**< 等比缩放填充整View，可能有部分被裁减 */
            ZegoVideoViewModeScaleToFill = 2,       /**< 填充整个View */
        };
        
        struct ZegoPublishQuality
        {
            double cfps;            ///< 视频帧率(采集)
            double vencFps;         ///< 视频帧率(编码)
            double fps;             ///< 视频帧率(网络发送)
            double kbps;            ///< 视频码率(kb/s)
            
            double acapFps;         ///< 音频帧率（采集）
            double afps;            ///< 音频帧率（网络发送）
            double akbps;           ///< 音频码率(kb/s)
        
            int rtt;                ///< 延时(ms)
            int pktLostRate;        ///< 丢包率(0~255)
            int quality;            ///< 质量(0~3)
            
            bool isHardwareVenc;    ///< 是否硬编
            int width;              ///< 视频宽度
            int height;             ///< 视频高度
        };
        
        struct ZegoPlayQuality
        {
            double fps;              ///< 视频帧率(网络接收)
            double vdjFps;           ///< 视频帧率(dejitter)
            double vdecFps;          ///< 视频帧率(解码)
            double vrndFps;          ///< 视频帧率(渲染)
            double kbps;             ///< 视频码率(kb/s)
            
            double afps;             ///< 音频帧率(网络接收)
            double adjFps;           ///< 音频帧率(dejitter)
            double adecFps;          ///< 音频帧率(解码)
            double arndFps;          ///< 音频帧率(渲染)
            double akbps;            ///< 音频码率(kb/s)
            
            double audioBreakRate;   ///< 音频卡顿次数
            double videoBreakRate;   ///< 视频卡顿次数
            int rtt;                 ///< 延时(ms)
            int pktLostRate;         ///< 丢包率(0~255)
            int peerToPeerDelay;     ///< 端到端延迟
            int peerToPeerPktLostRate; ///< 端到端丢包率(0~255)
            int quality;             ///< 质量(0~3)
            int delay;               ///< 语音延时(ms)
            
            bool isHardwareVdec;     ///< 是否硬解
            int width;               ///< 视频宽度
            int height;              ///< 视频高度
        };
    }
}

#endif /* ZegoLiveRoomDefines_h */
