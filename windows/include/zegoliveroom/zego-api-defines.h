//
//  zego-api-defines.h
//  zegoavkit
//
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef zego_api_defines_h
#define zego_api_defines_h


#define ZEGO_MAX_COMMON_LEN         (512)
#define ZEGO_MAX_URL_COUNT          (10)
#define ZEGO_MAX_EVENT_INFO_COUNT   (10)
#define ZEGO_MAX_MIX_INPUT_COUNT    (12)
#define ZEGO_MAX_IDENTITY_LEN       (64)

#define ZEGO_MAX_USERID_LEN         (64)
#define ZEGO_MAX_USERNAME_LEN       (256)
#define ZEGO_MAX_EXTRA_INFO_LEN     (1024)

#if defined(_MSC_VER) || defined(__BORLANDC__)
#	define _I64_				"I64"
#	define _64u_				"%I64u"
#	define _I64uw_				L"%llu"L
#	define _i64uw_				L"%llu"L
#else
#	define _I64_				"ll"
#	define _64u_				"%llu"
#	define _I64uw_				L"%llu" L
#	define _i64uw_				L"%llu" L
#	define __int64				long long
#endif

#ifdef WIN32

    #ifdef ZEGOAVKIT_EXPORTS
        #define ZEGOAVKIT_API __declspec(dllexport)
    #elif defined(ZEGOAVKIT_STATIC)
        #define ZEGOAVKIT_API // * nothing
    #else
        #define ZEGOAVKIT_API __declspec(dllimport)
    #endif

#else

    #define ZEGOAVKIT_API __attribute__((visibility("default")))

#endif

#define ZEGO_DEPRECATED     ///< 废弃标记


namespace ZEGO
{
    namespace AV
    {
        enum RemoteViewIndex
        {
            RemoteViewIndex_First = 0,
            RemoteViewIndex_Second = 1,
            RemoteViewIndex_Third = 2,
        };
        
        enum ZegoVideoViewMode
        {
            ZegoVideoViewModeScaleAspectFit = 0,    ///< 等比缩放，可能有黑边
            ZegoVideoViewModeScaleAspectFill = 1,   ///< 等比缩放填充整View，可能有部分被裁减
            ZegoVideoViewModeScaleToFill = 2,       ///< 填充整个View
        };
        
        enum ZegoVideoMirrorMode
        {
            ZegoVideoMirrorModePreviewMirrorPublishNoMirror = 0,  ///< 预览启用镜像，推流不启用镜像
            ZegoVideoMirrorModePreviewCaptureBothMirror = 1,      ///< 预览启用镜像，推流启用镜像
            ZegoVideoMirrorModePreviewCaptureBothNoMirror = 2,    ///< 预览不启用镜像，推流不启用镜像
            ZegoVideoMirrorModePreviewNoMirrorPublishMirror = 3   ///< 预览不启用镜像，推流启用镜像
        };
        
        enum VideoExternalRenderType
        {
            DECODE_RGB_SERIES = 0,   ///< 回调时，抛解码后数据，视频帧数据格式转换成RGB系列数据；设置了该类型后，SDK内部渲染无效。
            DECODE = 1,              ///< 回调时，抛解码后数据，视频帧数据格式根据回调参数决定；设置了该类型后，SDK内部渲染无效。
            NOT_DECODE = 2,           ///< 回调时，抛解码之前的帧数据给用户自解码；设置了该类型后，SDK内部渲染无效。
			DECODE_RENDER = 3		 ///< 回调时，抛解码后数据，视频帧数据格式根据回调参数决定；设置了该类型后，SDK内部渲染同时有效。
        };
        
        enum ZegoVideoCodecAvc
        {
            VIDEO_CODEC_DEFAULT = 0, ///< 不支持分层编码
            VIDEO_CODEC_MULTILAYER = 1 ///< 分层编码 要达到和VIDEO_CODEC_DEFAULT相同的编码质量，建议码率和VIDEO_CODEC_DEFAULT相比增加20%左右
        };

        
        /** 音频设备类型 */
        enum AudioDeviceType
        {
            AudioDevice_Input = 0,      /**< 输入设备 */
            AudioDevice_Output,         /**< 输出设备 */
        };
        
        struct DeviceInfo
        {
            char szDeviceId[ZEGO_MAX_COMMON_LEN];
            char szDeviceName[ZEGO_MAX_COMMON_LEN];
        };
        
        /** 设备状态 */
        enum DeviceState
        {
            Device_Added = 0,           /**< 添加设备 */
            Device_Deleted,             /**< 删除设备 */
        };
        
        enum DeviceStatus
        {
            Device_Opened = 0,          /**< 设备已打开 */
            Device_Closed,              /**< 设备已关闭 */
        };
        
        /** 音量类型 */
        enum VolumeType
        {
            Volume_EndPoint = 0,        /**< 设备音量 */
            Volume_Simple,              /**< App 音量 */
        };
        
        struct ZegoUser
        {
            char szId[ZEGO_MAX_COMMON_LEN];
            char szName[ZEGO_MAX_COMMON_LEN];
        };
        
        struct ZegoStreamInfo
        {
            ZegoStreamInfo()
            {
                uiRtmpURLCount = 0;
                uiHlsURLCount = 0;
                uiFlvURLCount = 0;
                szStreamID[0] = '\0';
                szMixStreamID[0] = '\0';
            }
            
            char szStreamID[ZEGO_MAX_COMMON_LEN];       /**< 流 ID */
            char szMixStreamID[ZEGO_MAX_COMMON_LEN];    /**< 混流 ID */
            
            char* arrRtmpURLs[ZEGO_MAX_URL_COUNT];      /**< RTMP 播放 URL 列表 */
            unsigned int uiRtmpURLCount;                /**< RTMP URL 个数 */
            
            char* arrFlvRULs[ZEGO_MAX_URL_COUNT];
            unsigned int uiFlvURLCount;
            
            char* arrHlsURLs[ZEGO_MAX_URL_COUNT];
            unsigned int uiHlsURLCount;
        };
        
        /** 转推CDN状态 */
        enum ZegoStreamRelayCDNState
        {
            RELAY_STOP = 0,                 /**< 转推停止 */
            RELAY_START = 1,                /**< 正在转推 */
            RELAY_RETRY = 2,                /**< 正在重试 */
        };
        
        enum ZegoStreamRelayCDNDetail
        {
            Relay_None = 0,                       ///< 无
            Relay_ServerError = 8,                ///< 服务器错误
            Relay_HandShakeFailed = 9,            ///< 握手失败
            Relay_AccessPointError = 10,          ///< 接入点错误
            Relay_CreateStreamFailed = 11,        ///< 创建流失败
            Relay_BadName = 12,                   ///< BAD NAME
            Relay_CDNServerDisconnected = 13,     ///< CDN服务器主动断开
            Relay_Disconnected = 14,              ///< 主动断开
        };
        
        struct ZegoStreamRelayCDNInfo
        {
            ZegoStreamRelayCDNInfo()
            {
                rtmpURL[0] = '\0';
                state = RELAY_STOP;
                stateTime = 0;
                detail = Relay_None;
            }
            
            char rtmpURL[ZEGO_MAX_COMMON_LEN];
            ZegoStreamRelayCDNState state;
            ZegoStreamRelayCDNDetail detail;   //转推停止或重试时有效
            unsigned int stateTime;
        };
        
        enum ZEGONetType
        {
            ZEGO_NT_NONE = 0,
            ZEGO_NT_LINE = 1,
            ZEGO_NT_WIFI = 2,
            ZEGO_NT_2G = 3,
            ZEGO_NT_3G = 4,
            ZEGO_NT_4G = 5,
            ZEGO_NT_UNKNOWN = 32
        };
        
        enum ZegoPublishFlag
        {
            ZEGO_JOIN_PUBLISH   = 0,        ///< 连麦
            ZEGO_MIX_STREAM     = 1 << 1,   ///< 混流，如果推出的流需要作为混流输入，请用这个模式
            ZEGO_SINGLE_ANCHOR  = 1 << 2,   ///< 单主播
        };
        
        /// \brief 混流图层信息
        struct ZegoMixStreamConfig
        {
            char szStreamID[ZEGO_MAX_COMMON_LEN];   ///< 混流ID
            struct
            {
                int top;
                int left;
                int bottom;
                int right;
            } layout;
            unsigned int uSoundLevelID;             ///< 音浪ID，用于标识用户，注意大小是32位无符号数
            int nContentControl;                    ///< 推流内容控制，0表示音视频都要，1表示只要音频，2表示只要视频。默认值：0。
            
            ZegoMixStreamConfig ()
            : uSoundLevelID(0)
            , nContentControl(0)
            {
                szStreamID[0] = '\0';
            }
            /**
             *  原点在左上角，top/bottom/left/right 定义如下：
             *
             *  (left, top)-----------------------
             *  |                                |
             *  |                                |
             *  |                                |
             *  |                                |
             *  -------------------(right, bottom)
             */
        };
        
        
        /** 完整混流配置 */
        struct ZegoCompleteMixStreamConfig
        {
            char szOutputStream[ZEGO_MAX_COMMON_LEN];   /**< 输出流名或 URL，参见 bOutputIsUrl */
            bool bOutputIsUrl;                          /**< true: szOutputStream 为完整 RTMP URL，false: szOutputStream 为流名 */
            
            int nOutputFps;                             /**< 混流输出帧率 */
            int nOutputBitrate;                         /**< 混流输出码率 */
            int nOutputAudioBitrate;                    /**< 混流输出音频码率 */
            
            int nOutputWidth;                           /**< 混流输出视频分辨率宽 */
            int nOutputHeight;                          /**< 混流输出视频分辨率高 */
            
            int nOutputAudioConfig;                     /**< 混流输出音频格式 */
            
            ZegoMixStreamConfig* pInputStreamList;      /**< 混流输入流列表 */
            int nInputStreamCount;                      /**< 混流输入流列表个数 */
            
            const unsigned char * pUserData;            /**< 用户自定义数据 */
            int nLenOfUserData;                         /**< 用户自定义数据的长度 */
            
            int nChannels;                              /**< 混流声道数，默认为单声道 */
            
            int nOutputBackgroundColor;                 /**< 混流背景颜色，前三个字节为 RGB 颜色值，即 0xRRGGBBxx */
            const char* pOutputBackgroundImage;         /**< 混流背景图，支持预设图片，如 (preset-id://xxx) */
            
            bool bWithSoundLevel;                       /**< 是否开启音浪。true：开启，false：关闭 */
            
            int nExtra;                                 /**< 扩展信息，备用 */
            
            ZegoCompleteMixStreamConfig ()
            : bOutputIsUrl(false)
            , nOutputFps(0)
            , nOutputBitrate(0)
            , nOutputAudioBitrate(0)
            , nOutputWidth(0)
            , nOutputHeight(0)
            , nOutputAudioConfig(0)
            , pInputStreamList(0)
            , nInputStreamCount(0)
            , pUserData(0)
            , nLenOfUserData(0)
            , nChannels(1)
            , nOutputBackgroundColor(0x00000000)
            , pOutputBackgroundImage(0)
            , bWithSoundLevel(false)
            , nExtra(0)
            {
                szOutputStream[0] = '\0';
            }
        };
        
        /** 混流结果消息 */
        struct ZegoMixStreamResult
        {
            unsigned int uiErrorCode;   /**< 错误码，0 表示成功，此时 oStreamInfo 有效。150 表示输入流不存在，参考 nNonExistsStreamCount 和 ppNonExistsStreamIDList */
            
            int nNonExistsStreamCount;                                      /**< 不存在的输入流个数 */
            const char* ppNonExistsStreamIDList[ZEGO_MAX_MIX_INPUT_COUNT];  /**< 不存在的输入流 ID 列表 */
            
            ZegoStreamInfo oStreamInfo;        /**< 混流输出信息 */
            
            ZegoMixStreamResult()
            : uiErrorCode(0)
            , nNonExistsStreamCount(0)
            {}
        };
        
        /** 混流结果消息扩展 */
        struct ZegoMixStreamResultEx
        {
            unsigned int uiErrorCode;   /**< 错误码，0 表示成功，此时 oStreamInfo 有效。150 表示输入流不存在，参考 nNonExistsStreamCount 和 ppNonExistsStreamIDList */
            
            int nNonExistsStreamCount;                                      /**< 不存在的输入流个数 */
            const char* ppNonExistsStreamIDList[ZEGO_MAX_MIX_INPUT_COUNT];  /**< 不存在的输入流 ID 列表 */
            
            int nStreamInfoCount;                   /**< 混流输出个数 */
            ZegoStreamInfo *pStreamInfoList;        /**< 混流输出列表 */
            
            ZegoMixStreamResultEx()
            : uiErrorCode(0)
            , nNonExistsStreamCount(0)
            , nStreamInfoCount(0)
            {}
        };
        
        enum ZegoLogLevel
        {
            Grievous = 0,
            Error = 1,
            Warning = 2,
            Generic = 3,    ///< 通常在发布产品中使用
            Debug = 4       ///< 调试阶段使用
        };
        
        
        /** SDK 事件通知 */
        enum EventType
        {
            Play_BeginRetry = 1,        /**< 开始重试拉流 */
            Play_RetrySuccess = 2,      /**< 重试拉流成功 */
            
            Publish_BeginRetry = 3,     /**< 开始重试推流 */
            Publish_RetrySuccess = 4,   /**< 重试推流成功 */
            
            Play_TempDisconnected = 5,     /**< 拉流临时中断 */
            Publish_TempDisconnected = 6,  /**< 推流临时中断 */
            
            Play_VideoBreak = 7,           /**< 视频卡顿开始 */
            Play_VideoBreakEnd = 8,        /**< 视频卡顿结束 */
            
            Play_AudioBreak = 9,           /**< 音频卡顿开始 */
            Play_AudioBreakEnd = 10,       /**< 音频卡顿结束 */

            PublishInfo_RegisterFailed = 11,   /**< 注册推流信息失败 */
            PublishInfo_RegisterSuccess = 12, /**< 注册推流信息成功 */
        };
        
        struct EventInfo
        {
            unsigned int uiInfoCount;
            const char* arrKeys[ZEGO_MAX_EVENT_INFO_COUNT];
            const char* arrValues[ZEGO_MAX_EVENT_INFO_COUNT];
        };
        
#if defined(WIN32) || defined(ANDROID)
        ZEGOAVKIT_API extern const char* kZegoDeviceCamera;
        ZEGOAVKIT_API extern const char* kZegoDeviceMicrophone;
        ZEGOAVKIT_API extern const char* kZegoStreamID;
#else
        extern const char* kZegoDeviceCamera;
        extern const char* kZegoDeviceMicrophone;
        extern const char* kZegoStreamID;
#endif
        
        /** 视频编码码率控制策略 */
        enum ZegoVideoEncoderRateControlStrategy
        {
            ZEGO_RC_ABR,                /**< 恒定码率 */
            ZEGO_RC_CBR,                /**< 恒定码率 */
            ZEGO_RC_VBR,                /**< 恒定质量, 仅用于研究目的 */
            ZEGO_RC_CRF,                /**< 恒定质量 */
        };
        
        /** 视频采集缩放时机 */
        enum ZegoCapturePipelineScaleMode
        {
            ZegoCapturePipelinePreScale = 0,        /**< 采集后立即进行缩放，默认 */
            ZegoCapturePipelinePostScale = 1,       /**< 编码时进行缩放 */
        };
        
        /** 音频设备模式 */
        enum ZegoAVAPIAudioDeviceMode
        {
            ZEGO_AUDIO_DEVICE_MODE_COMMUNICATION = 1,    /**< 开启系统回声消除 */
            ZEGO_AUDIO_DEVICE_MODE_GENERAL = 2,          /**< 关闭系统回声消除 */
            ZEGO_AUDIO_DEVICE_MODE_AUTO = 3,             /**< 根据场景自动选择是否开启系统回声消除 */
            ZEGO_AUDIO_DEVICE_MODE_COMMUNICATION2 = 4,   /**< 开启系统回声消除，与communication相比，communication2会始终占用麦克风设备 */
        };
        
        /** 延迟模式 */
        enum ZegoAVAPILatencyMode
        {
            ZEGO_LATENCY_MODE_NORMAL = 0,               /**< 普通延迟模式 */
            ZEGO_LATENCY_MODE_LOW,                      /**< 低延迟模式，无法用于 RTMP 流 */
            ZEGO_LATENCY_MODE_NORMAL2,                  /**< 普通延迟模式，最高码率可达 192K */
            ZEGO_LATENCY_MODE_LOW2,                     /**< 低延迟模式，无法用于 RTMP 流。相对于 ZEGO_LATENCY_MODE_LOW 而言，CPU 开销稍低 */
            ZEGO_LATENCY_MODE_LOW3,                     /**< 低延迟模式，无法用于 RTMP 流。支持WebRTC必须使用此模式 */
            ZEGO_LATENCY_MODE_NORMAL3,                  /**< 普通延迟模式，使用此模式前先咨询即构技术支持 */
        };
        
        /** 流量控制属性 */
        enum ZegoTrafficControlProperty
        {
            /**< 基本流量控制，只有码率控制，不带自适应帧率和分辨率 */
            ZEGO_TRAFFIC_CONTROL_BASIC = 0,
            /**< 自适应帧率 */
            ZEGO_TRAFFIC_CONTROL_ADAPTIVE_FPS = 1,
            /**< 自适应分辨率 */
            ZEGO_TRAFFIC_CONTROL_ADAPTIVE_RESOLUTION = 1 << 1,
            
            /**< 音频流量控制*/
            ZEGO_TRAFFIC_CONTROL_ADAPTIVE_AUDIO_BITRATE = 1 << 2,
            
            /**< 废弃 */
            ZEGO_TRAFFIC_NONE = ZEGO_TRAFFIC_CONTROL_BASIC,
            ZEGO_TRAFFIC_FPS = ZEGO_TRAFFIC_CONTROL_ADAPTIVE_FPS,
            ZEGO_TRAFFIC_RESOLUTION = ZEGO_TRAFFIC_CONTROL_ADAPTIVE_RESOLUTION,
        };
        
        enum ZegoTrafficControlMinVideoBitrateMode
        {
            /** 低于设置的最低码率时，停止视频发送 */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_NO_VIDEO = 0,
            /** 低于设置的最低码率时，视频以极低的频率发送 （不超过2FPS) */
            ZEGO_TRAFFIC_CONTROL_MIN_VIDEO_BITRATE_ULTRA_LOW_FPS
        };
        
        /** 音频录制类型 */
        enum ZegoAVAPIAudioRecordMask
        {
            ZEGO_AUDIO_RECORD_NONE      = 0x0,  /**< 关闭音频录制 */
            ZEGO_AUDIO_RECORD_CAP       = 0x01, /**< 打开采集录制 */
            ZEGO_AUDIO_RECORD_RENDER    = 0x02, /**< 打开渲染录制 */
            ZEGO_AUDIO_RECORD_MIX       = 0x04  /**< 打开采集和渲染混音结果录制 */
        };
        
        enum LiveStreamQuality
        {
            Excellent   = 0,
            Good        = 1,
            Middle      = 2,
            Poor        = 3,
            Die         = 4,
            MaxGrade,
        };
        
        struct PublishQuality
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
        
        struct PlayQuality
        {
            double fps;                     ///< 视频帧率(网络接收)
            double vdjFps;                  ///< 视频帧率(dejitter)
            double vdecFps;                 ///< 视频帧率(解码)
            double vrndFps;                 ///< 视频帧率(渲染)
            double kbps;                    ///< 视频码率(kb/s)
            
            double afps;                    ///< 音频帧率(网络接收)
            double adjFps;                  ///< 音频帧率(dejitter)
            double adecFps;                 ///< 音频帧率(解码)
            double arndFps;                 ///< 音频帧率(渲染)
            double akbps;                   ///< 音频码率(kb/s)
            
            double audioBreakRate;          ///< 音频卡顿次数
            double videoBreakRate;          ///< 视频卡顿次数
            int rtt;                        ///< 延时(ms)
            int pktLostRate;                ///< 丢包率(0~255)
            int peerToPeerDelay;            ///< 端到端延迟
            int peerToPeerPktLostRate;      ///< 端到端丢包率(0~255)
            int quality;                    ///< 质量(0~3)
            int delay;                      ///< 语音延迟(ms)
            
            bool isHardwareVdec;            ///< 是否硬解
            int width;                      ///< 视频宽度
            int height;                     ///< 视频高度
        };
        
        /** 推流通道 */
        enum PublishChannelIndex
        {
            PUBLISH_CHN_MAIN = 0,                       /**< 主推流通道，默认 */
            PUBLISH_CHN_AUX,                            /**< 第二路推流通道，无法推出声音 */
        };
        
        /** 视频分层类型 */
        enum VideoStreamLayer
        {
            VideoStreamLayer_Auto = -1,            /**< 根据网络状态选择图层  */
            VideoStreamLayer_BaseLayer = 0,        /**< 指定拉基本层（小分辨率） */
            VideoStreamLayer_ExtendLayer = 1       /**< 指定拉扩展层（大分辨率)  */
        };
        
        /** MediaInfo类型 */
        enum MediaInfoType
        {
            SideInfoZegoDefined = 0,            /**< side info  */
            SeiZegoDefined = 1,                 /**< sei (nalu type = 6,payload type = 243), sei recommend useing this  */
            SeiUserUnregisted = 2               /**< sei (nalu type = 6,payload type = 5) */
        };

        /** SEI发送类型 */
        enum SeiSendType
        {
            SeiSendSingleFrame = 0,             /**< sei send single frame  */
            SeiSendInVideoFrame = 1             /**< sei send in any video frame(IDR, B, P)  */
        };
        
        struct SoundLevelInfo
        {
            unsigned int soundLevelID;          ///< soundlevel ID
            unsigned char soundLevel;           ///< soundlevel 的值
        };
        
        /** 回声消除模式 */
        enum ZegoAECMode
        {
            AEC_MODE_AGGRESSIVE,
            AEC_MODE_MEDIUM,
            AEC_MODE_SOFT
        };
    }
}

#ifdef __cplusplus
extern "C" {
#endif
    
    struct ZegoStreamExtraPlayInfo;
    ZEGOAVKIT_API struct ZegoStreamExtraPlayInfo* zego_stream_extra_info_create();
    ZEGOAVKIT_API void zego_stream_extra_info_destroy(struct ZegoStreamExtraPlayInfo* info);
    
    ZEGOAVKIT_API void zego_stream_extra_info_add_rtmp_url(struct ZegoStreamExtraPlayInfo* info, const char* url);
    ZEGOAVKIT_API void zego_stream_extra_info_add_flv_url(struct ZegoStreamExtraPlayInfo* info, const char* url);
    ZEGOAVKIT_API void zego_stream_extra_info_set_params(struct ZegoStreamExtraPlayInfo* info, const char* params);
    ZEGOAVKIT_API void zego_stream_extra_info_should_switch_server(struct ZegoStreamExtraPlayInfo* info, bool should);
    
#ifdef __cplusplus
} // __cplusplus defined.
#endif

#endif /* zego_api_defines_h */
