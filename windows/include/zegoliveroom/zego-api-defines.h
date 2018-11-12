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
        
        const unsigned int SEG_PUBLISH_FATAL_ERROR = 0x0001 << 16;   ///< 推流严重错误段
        const unsigned int SEG_PUBLISH_NORMAL_ERROR = 0x0002 << 16;  ///< 推流普通错误段
        const unsigned int SEG_PLAY_FATAL_ERROR = 0x0003 << 16;      ///< 拉流严重错误段
        const unsigned int SEG_PLAY_NORMAL_ERROR = 0x0004 << 16;     ///< 拉流普通错误段
        
        enum ZegoAVAPIState
        {
            AVStateBegin = 0,               ///< 直播开始
            AVStateEnd = 1,                 ///< 直播正常停止
            TempBroken = 2 ZEGO_DEPRECATED, ///< 直播异常中断
            FatalError = 3,                 ///< 直播遇到严重的问题（如出现，请联系 ZEGO 技术支持）
            
            CreateStreamError = 4,          ///< 创建直播流失败
            FetchStreamError = 5,           ///< 获取流信息失败
            NoStreamError = 6,              ///< 无流信息
            MediaServerNetWorkError = 7,    ///< 媒体服务器连接失败
            DNSResolveError = 8,            ///< DNS 解析失败
            
            NotLoginError = 9,              ///< 未登陆
            LogicServerNetWrokError = 10,   ///< 逻辑服务器网络错误
            
            InitConfigError = 11,           ///< 初始化配置失败
            
            PublishBadNameError = 105,
            HttpDNSResolveError = 106 ZEGO_DEPRECATED,
            
            PublishForbidError = (SEG_PUBLISH_FATAL_ERROR | 0x03f3),             ///< 禁止推流, 低8位为服务端返回错误码：1011
            
            PublishStopError = (SEG_PUBLISH_FATAL_ERROR | 0x03f6),             ///< 停止推流, 低8位为服务端返回错误码：1014
            
            PublishDeniedError = (SEG_PUBLISH_NORMAL_ERROR | 0x1),              ///< 推流被拒绝

            PlayStreamNotExistError = (SEG_PLAY_FATAL_ERROR | 0x03ec),          ///< 拉的流不存在, 低8位为服务端返回错误码：1004
            PlayForbidError = (SEG_PLAY_FATAL_ERROR | 0x03f3),                  ///< 禁止拉流, 低8位为服务端返回错误码：1011
            
            PlayDeniedError = (SEG_PLAY_NORMAL_ERROR | 0x1),                   ///< 拉流被拒绝
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
            
            Play_VideoBreak = 7,           /**< 拉流卡顿(视频) */
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
            ZEGO_RC_VBR,                /**< 恒定质量 */
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
            ZEGO_AUDIO_DEVICE_MODE_COMMUNICATION = 1,    /**< 开启硬件回声消除 */
            ZEGO_AUDIO_DEVICE_MODE_GENERAL = 2,          /**< 关闭硬件回声消除 */
            ZEGO_AUDIO_DEVICE_MODE_AUTO = 3              /**< 根据场景自动选择是否开启硬件回声消除 */
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
            
            /**< 废弃 */
            ZEGO_TRAFFIC_NONE = ZEGO_TRAFFIC_CONTROL_BASIC,
            ZEGO_TRAFFIC_FPS = ZEGO_TRAFFIC_CONTROL_ADAPTIVE_FPS,
            ZEGO_TRAFFIC_RESOLUTION = ZEGO_TRAFFIC_CONTROL_ADAPTIVE_RESOLUTION,
        };
        
        /** 音频录制类型 */
        enum ZegoAVAPIAudioRecordMask
        {
            ZEGO_AUDIO_RECORD_NONE      = 0x0,  /**< 关闭音频录制 */
            ZEGO_AUDIO_RECORD_CAP       = 0x01, /**< 打开采集录制 */
            ZEGO_AUDIO_RECORD_RENDER    = 0x02, /**< 打开渲染录制 */
            ZEGO_AUDIO_RECORD_MIX       = 0x04  /**< 打开采集和渲染混音结果录制 */
        };
        
        struct PublishQuality
        {
            double fps;             ///< 视频帧率(编码/网络发送)
            double cfps;            ///< 视频采集帧率
            double kbps;            ///< 视频码率(kb/s)
            double akbps;           ///< 音频码率(kb/s)
            int rtt;                ///< 延时(ms)
            int pktLostRate;        ///< 丢包率(0~255)
            
            int quality;            ///< 质量(0~4)
        };
        
        struct PlayQuality
        {
            double fps;                      ///< 视频帧率
            double kbps;                     ///< 视频码率(kb/s)
            double akbps;                   ///< 音频码率(kb/s)
            double audioBreakRate;          ///< 音频卡顿率(次/min)
            int rtt;                        ///< 延时(ms)
            int pktLostRate;                ///< 丢包率(0~255)
            
            int quality;                    ///< 质量(0~4)
            int delay;                      ///< 语音延迟(ms)
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
        
        struct SoundLevelInfo
        {
            unsigned int soundLevelID;          ///< soundlevel ID
            unsigned char soundLevel;           ///< soundlevel 的值
        };
    }
}

/** 接口调用返回错误码 */
enum ZegoErrorCode
{
    kZegoErrorCodeOK = 0,    /**< 没有错误 */
    kZegoErrorCodeInvalidParameter = 1,  /** 调用输入参数错误 */
    
    // * 5101 外部音频设备
    kZegoErrorCodeExternalAudioDeviceWasNotEnabled = 5101, /** 没有启用外部音频设备 */
    kZegoErrorCodeExternalAudioDeviceEngineError = 5102, /** 处理音频数据异常 */
};


#ifdef __cplusplus
extern "C" {
#endif
    
    struct ZegoStreamExtraPlayInfo;
    ZEGOAVKIT_API struct ZegoStreamExtraPlayInfo* zego_stream_extra_info_create();
    ZEGOAVKIT_API void zego_stream_extra_info_destroy(struct ZegoStreamExtraPlayInfo* info);
    
    ZEGOAVKIT_API void zego_stream_extra_info_add_rtmp_url(struct ZegoStreamExtraPlayInfo* info, const char* url);
    ZEGOAVKIT_API void zego_stream_extra_info_add_flv_url(struct ZegoStreamExtraPlayInfo* info, const char* url);
    ZEGOAVKIT_API void zego_stream_extra_info_set_params(struct ZegoStreamExtraPlayInfo* info, const char* params);
    
#ifdef __cplusplus
} // __cplusplus defined.
#endif

#endif /* zego_api_defines_h */
