//
//  LiveRoomCallback-Player.h
//  zegoliveroom
//
//  Created by Randy Qiu on 2017/1/23.
//
//

#ifndef LiveRoomCallback_Player_h
#define LiveRoomCallback_Player_h

#include "./LiveRoomDefines.h"
#include "video_capture.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class ILivePlayerCallback
        {
        public:
            /**
             播放状态更新

             @param stateCode 状态码
             @param pszStreamID 流 ID
             */
            virtual void OnPlayStateUpdate(int stateCode, const char* pszStreamID) = 0;

            /**
             观看质量更新

             @param pszStreamID 观看流 ID
             @param quality 0~3 分别对应优、良、中、差
             @param videoFPS 帧率
             @param videoKBS 码率
             */
            virtual void OnPlayQualityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS) {};
            
            /**
             观看质量更新

             @param pszStreamID 观看流 ID
             @param playQuality ZegoPlayQuality 对象，内部包含了各项质量数据
             */
            virtual void OnPlayQualityUpdate(const char* pszStreamID, ZegoPlayQuality playQuality) {};
            
            /**
             收到请求连麦响应结果

             @param result 结果
             @param pszFromUserId 来源用户 Id
             @param pszFromUserName 来源用户名
             @param seq 请求 seq
             */
            virtual void OnJoinLiveResponse(int result, const char* pszFromUserId, const char* pszFromUserName, int seq) {};
            
            /**
             收到结束连麦指令

             @param pszFromUserId 来源用户 Id
             @param pszFromUserName 来源用户名
             @param pszRoomID 房间 ID
             */
            virtual void OnRecvEndJoinLiveCommand(const char *pszFromUserId, const char* pszFromUserName, const char* pszRoomID) {};

            /**
             收到连麦邀请

             @param seq 请求 seq
             @param pszFromUserId 来源用户 Id
             @param pszFromUserName 来源用户名
             @param pszRoomID 房间 ID
             */
            virtual void OnInviteJoinLiveRequest(int seq, const char* pszFromUserId, const char* pszFromUserName, const char* pszRoomID) {};
            
            /**
             视频尺寸变更通知

             @param pStreamID 流 ID
             @param nWidth 视频宽度
             @param nHeight 视频高度
             */
            virtual void OnVideoSizeChanged(const char* pStreamID, int nWidth, int nHeight) {};
            
            /**
             截屏结果

             @param pImage 截屏图片
             @param pszStreamID 流 ID
             */
            virtual void OnSnapshot(void *pImage, const char* pszStreamID) {};
            
            virtual ~ILivePlayerCallback() {}
        };
        
        class IZegoVideoRenderCallback
        {
        public:
            /**
             视频帧数据回调

             @param pData 视频数据起始地址，windows 平台上回调数据格式为 RGBA32
             @param dataLen 视频数据长度
             @param pszStreamID 流 ID。当外部渲染拉流数据，pszStreamID 为拉流流名；当外部渲染推流数据，pszStreamID 为常量 kZegoVideoDataMainPublishingStream 时表示第一路推流数据；pszStreamID 为常量 kZegoVideoDataAuxPublishingStream 时表示第二路推流数据
             @param width 视频宽度
             @param height 视频高度
             @param strides 每个平面一行字节数（RGBA 只需考虑 strides[0]）
             */
            virtual void OnVideoDataCallback(const unsigned char *pData, int dataLen, const char* pszStreamID, int width, int height, int strides[4]) {};
            
            /**
             视频帧数据回调2
             
             @param pData 视频数据起始地址
             @param dataLen 视频数据长度
             @param pszStreamID 流 ID
             @param width 视频宽度
             @param height 视频高度
             @param strides 每个平面一行字节数（RGBA 只需考虑 strides[0]）
             @param pixel_format 视频帧数据格式
             */
            virtual void OnVideoDataCallback2(const unsigned char **pData, int* dataLen, const char* pszStreamID, int width, int height, int strides[4], AVE::VideoPixelFormat pixel_format) {}

        };
    }
}


#endif /* LiveRoomCallback_Player_h */
