//
//  zego-api-mediaplayer-defines.h
//  ZegoLiveRoom
//
//  Copyright © 2018年 Zego. All rights reserved.
//

#ifndef zego_api_mediaplayer_defines_h
#define zego_api_mediaplayer_defines_h

namespace ZEGO
{
namespace MEDIAPLAYER
{
        
    enum ZegoMediaPlayerType
    {
        ZegoMediaPlayerTypePlayer   = 0,
        ZegoMediaPlayerTypeAux      = 1
    };
    
    enum ZegoMediaPlayerVideoPixelFormat
    {
        ZegoMediaPlayerVideoPixelFormatUnknown  = 0,
        ZegoMediaPlayerVideoPixelFormatBGRA32   = 4,
        ZegoMediaPlayerVideoPixelFormatRGBA32   = 5,
        ZegoMediaPlayerVideoPixelFormatARGB32   = 6,
        ZegoMediaPlayerVideoPixelFormatABGR32   = 7,
    };
    
    struct ZegoMediaPlayerVideoDataFormat
    {
        int width;
        int height;
        int strides[4];
        int rotation;
        ZegoMediaPlayerVideoPixelFormat pixelFormat;
        
        ZegoMediaPlayerVideoDataFormat()
        {
            width = 0;
            height = 0;
            strides[0] = strides[1] = strides[2] = strides[3] = 0;
            rotation = 0;
            pixelFormat = ZegoMediaPlayerVideoPixelFormatUnknown;
        }
        
        ZegoMediaPlayerVideoDataFormat(int width, int height, ZegoMediaPlayerVideoPixelFormat pixelFormat)
        {
            this->width = width;
            this->height = height;
            this->pixelFormat = pixelFormat;
            this->strides[0] = this->strides[1] = this->strides[2] = this->strides[3] = 0;
            this->rotation = 0;
        }
    };
    
    class IZegoMediaPlayerEventCallback
    {
    public:
        /**
         开始播放
         */
        virtual void OnPlayStart() = 0;
        /**
         播放出错
         
         PLAY_ERROR_NOERROR = 0,
         PLAY_ERROR_FILE =  -1，文件格式不支持,
         PLAY_ERROR_PATH =  -2，路径不存在,
         PLAY_ERROR_CODEC = -3, 文件无法解码
         PLAY_ERROR_NO_SUPPORT_STREAM = -4,文件中没有可播放的音视频流
         PLAY_ERROR_DEMUX = -5, 文件解析过程中出现错误
         */
        virtual void OnPlayError(const int errCode) = 0;
        /**
         视频开始播放
         */
        virtual void OnVideoBegin() {}
        /**
         音频开始播放
         */
        virtual void OnAudioBegin() {}
        /**
         播放结束
         */
        virtual void OnPlayEnd() = 0;
        /**
         快进到指定时刻
         
         @param state >=0 成功，其它表示失败
         @param duration 实际快进的进度，单位毫秒
         */
        virtual void OnSeekComplete(const int state, const long duration) {}
        /**
         暂停播放
         */
        virtual void OnPlayPause() {}
        /**
         恢复播放
         */
        virtual void OnPlayResume() {}
        /**
         主动停止播放
         */
        virtual void OnPlayStop() {}
        /**
         开始缓冲
         */
        virtual void OnBufferBegin() {}
        /**
         结束缓冲
         */
        virtual void OnBufferEnd() {}
    };
    
    class IZegoMediaPlayerVideoDataCallback
    {
    public:
        /**
         视频帧数据回调，同步回调，不要在回调中处理数据或进行耗时操作
         
         @param data 视频帧数据
         @param len 视频帧数据长度
         @param format 视频帧格式信息
         */
        virtual void OnPlayVideoData(const char* data, int len, ZegoMediaPlayerVideoDataFormat& format) = 0;
    };
    
}   // MEDIAPLAYER
}   // ZEGO


#endif /* zego_api_mediaplayer_defines_h */
