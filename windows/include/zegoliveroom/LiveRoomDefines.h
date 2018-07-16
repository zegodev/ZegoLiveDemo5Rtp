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
        
        /**
         如何确定错误码
         
         1. 先通过错误掩码 ZegoErrorMask 来判断是什么类型的错误（应该从 RoomServerErrorMask 开始判断）
         2. 如果符合房间服务错误掩码 RoomServerErrorMask，用 RoomServerErrorMask 异或原始错误码，再对应房间错误码 ZegoRoomError 查看是什么错误
         */
        
        /** 房间错误码 */
        enum ZegoRoomError
        {   
            LoginNetworkError   = 101,  /**< HTTP 连接错误 */
            LoginPushError      = 102,  /**< TCP 连接错误 */
            LoginServerError    = 103,  /**< 服务器错误 */
            LoginNetChangeError = 104,  /**< 网络切换临时状态，网络恢复后会自动重连 */
            NotLoginError       = 105,  /**< 用户没有登录 */
            RequestParamError   = 106,  /**< 请求参数错误 */
            
            SessionError        = 141,  /**< 会话错误 */
            
            DatiCommitError     = 3001, /**< 答题服务故障 */
            DatiTimeoutError    = 3002, /**< 答题时间已过 */
            DatiRepeatError     = 3003, /**< 重复答题 */
        };
        
        /** 错误掩码 */
        enum ZegoErrorMask
        {
            NetworkErrorMask      = 0x1000,   /**< 网络连接错误掩码 */
            ReloginErrorMask      = 0x10000,  /**< SDK重登录错误掩码 */
            RoomServerErrorMask   = 0x100000, /**< 房间服务错误掩码 */
        };
        
        using COMMON::ZegoStreamInfo;
        
        using COMMON::ZegoStreamUpdateType;
        
        using COMMON::LiveRoomState;
        
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
            double fps;             ///< 视频帧率
            double kbps;            ///< 视频码率(kb/s)
            double akbps;           ///< 音频码率(kb/s)
            int rtt;                ///< 延时(ms)
            int pktLostRate;        ///< 丢包率(0~255)
            
            int quality;            ///< 质量(0~3)
        };
        
        struct ZegoPlayQuality
        {
            double fps;             ///< 视频帧率
            double kbps;            ///< 视频码率(kb/s)
            double akbps;           ///< 音频码率(kb/s)
            double audioBreakRate;  ///< 音频卡顿率(次/min)
            int rtt;                ///< 延时(ms)
            int pktLostRate;        ///< 丢包率(0~255)
            
            int quality;            ///< 质量(0~3)
        };
    }
}

#endif /* ZegoLiveRoomDefines_h */
