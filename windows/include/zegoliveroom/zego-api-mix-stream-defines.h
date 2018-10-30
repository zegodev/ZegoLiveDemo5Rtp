//
//  zego-api-mix-stream-defines.h
//
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_mix_stream_defines_h
#define zego_api_mix_stream_defines_h

#include "zego-api-defines.h"

namespace ZEGO
{
namespace MIXSTREAM
{
    
    /**
     混流输入配置
     */
    struct ZegoMixStreamInput
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
        
        ZegoMixStreamInput ()
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
    
    /**
     混流输出目的地
     */
    struct ZegoMixStreamOutput
    {
        /**< true: target 为完整 RTMP URL，false: target 为流名 */
        bool isUrl;
        /**< 输出流名或 URL，参见 isUrl */
        char target[ZEGO_MAX_COMMON_LEN];
    };
    
    /**
     混流水印信息
     */
    struct ZegoMixStreamWatermark
    {
        /** 水印图片 */
        char image[ZEGO_MAX_COMMON_LEN];
        
        struct
        {
            int top;
            int left;
            int bottom;
            int right;
        } layout;
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
    
    
    /**
     混流配置
     */
    struct ZegoMixStreamConfig
    {
        int nOutputFps;                             /**< 混流输出帧率 */
        int nOutputRateControlMode;                 /**< 混流输出码率控制模式，0 表示 CBR 恒定码率，1 表示 CRF 恒定质量，默认为 0 */
        int nOutputBitrate;                         /**< 混流输出码率，输出码率控制模式设置为 CBR恒定码率时有效 */
        int nOutputQuality;                         /**< 混流输出质量，输出码率控制模式设置为 CRF恒定质量时有效，有效范围 0-51，默认值是 23 */
        int nOutputAudioBitrate;                    /**< 混流输出音频码率 */
        
        int nOutputWidth;                           /**< 混流输出视频分辨率宽 */
        int nOutputHeight;                          /**< 混流输出视频分辨率高 */
        
        int nOutputAudioConfig;                     /**< 混流输出音频格式 */
        
        ZegoMixStreamInput* pInputStreamList;       /**< 混流输入流列表 */
        int nInputStreamCount;                      /**< 混流输入流列表个数 */
        
        ZegoMixStreamOutput* pOutputList;           /**< 混流输出列表 */
        int nOutputStreamCount;                     /**< 混流输出列表个数 */
        
        const unsigned char * pUserData;            /**< 用户自定义数据 */
        int nLenOfUserData;                         /**< 用户自定义数据的长度 */
        
        int nChannels;                              /**< 混流声道数，默认为单声道 */
        
        int nOutputBackgroundColor;                 /**< 混流背景颜色，前三个字节为 RGB 颜色值，即 0xRRGGBBxx */
        const char* pOutputBackgroundImage;         /**< 混流背景图，支持预设图片，如 (preset-id://xxx) */
        
        bool bWithSoundLevel;                       /**< 是否开启音浪。true：开启，false：关闭 */
        int nExtra;                                 /**< 扩展信息，备用 */
        
        ZegoMixStreamWatermark *pOutputWatermark;   /**< 混流水印 */
        
        ZegoMixStreamConfig ()
        : nOutputFps(0)
        , nOutputRateControlMode(0)
        , nOutputBitrate(0)
        , nOutputQuality(23)
        , nOutputAudioBitrate(0)
        , nOutputWidth(0)
        , nOutputHeight(0)
        , nOutputAudioConfig(0)
        , pInputStreamList(0)
        , nInputStreamCount(0)
        , pOutputList(0)
        , nOutputStreamCount(0)
        , pUserData(0)
        , nLenOfUserData(0)
        , nChannels(1)
        , nOutputBackgroundColor(0x00000000)
        , pOutputBackgroundImage(0)
        , bWithSoundLevel(false)
        , nExtra(0)
        , pOutputWatermark(0)
        {
            
        }
    };
    
}
}

#endif /* zego_api_mix_stream_defines_h */
