//
//  zego-api-media-side-info.hpp
//  ZegoLiveRoom
//
//  Created by MarkWu on 2018/1/12.
//

#ifndef zego_api_media_side_info_h
#define zego_api_media_side_info_h
#include "zego-api-defines.h"

namespace ZEGO
{
    namespace MEDIASIDEINFO
    {
        /**
         流媒体次要信息回调
         
         @param pszStreamID 流ID，标记当前回调的信息属于哪条流
         @param pBuf，数据缓冲区，存储流媒体次要信息
         @param dataLen, 缓冲区长度
         */
		class IZegoMediaSideCallback
        {
        public:
            virtual void onRecvMediaSideInfo(const char * pszStreamID, const unsigned char *pBuf, int dataLen) = 0;
			virtual ~IZegoMediaSideCallback() {}
        };
        
        /**
         发送媒体次要信息开关
         
         @param bStart true 开启, false 关闭
         @param bOnlyAudioPublish true 纯音频直播，不传输视频数据, false 音视频直播，传输视频数据
         @param idx 推流 channel Index. 默认为主Channel
         @attention onlyAudioPublish 开关在 start 开关开启时才生效
         @attention 必须在InistSDK之后、推流前，设置
         */
        ZEGOAVKIT_API void SetMediaSideFlags(bool bStart, bool bOnlyAudioPublish, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         发送媒体次要信息
         
         @param inData 媒体次要信息数据
         @param dataLen 数据长度
         @param bPacket 是否外部已经打包好包头，true 已打包, false 未打包
         @param idx 推流 channel Index. 默认为主Channel
         @attention 必须在推流成功后调用
         */
        ZEGOAVKIT_API void SendMediaSideInfo(const unsigned char *inData, int dataLen, bool bPacket, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        
        /**
         设置回调, 接收媒体次要信息
         
         @param pCB 回调函数指针
         @attention InitSDK之后、开始拉流前，设置。当不需要接收数据时，必须将 callback 置空，避免内存泄漏
         */
        ZEGOAVKIT_API void SetMediaSideCallback(IZegoMediaSideCallback* pCB);
    }
}



#endif /* zego_api_media_side_info_hpp */
