//
//  LiveRoomCallback-Publisher.h
//  zegoliveroom
//
//  Created by Randy Qiu on 2017/1/23.
//
//

#ifndef LiveRoomCallback_Publisher_h
#define LiveRoomCallback_Publisher_h

#include "./LiveRoomDefines-Publisher.h"
#include "./LiveRoomDefines.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class ILivePublisherCallback
        {
        public:
            /**
             推流状态更新

             @param stateCode 状态码
             @param pszStreamID 流 ID
             @param oStreamInfo 推流信息
             */
            virtual void OnPublishStateUpdate(int stateCode, const char* pszStreamID, const ZegoPublishingStreamInfo& oStreamInfo) = 0;
            
            /**
             收到连麦请求

             @param seq 请求 seq
             @param pszFromUserId 来源用户 Id
             @param pszFromUserName 来源用户名
             @param pszRoomID 房间 ID
             */
            virtual void OnJoinLiveRequest(int seq, const char *pszFromUserId, const char *pszFromUserName, const char *pszRoomID) {}
            
            /**
             收到邀请连麦响应结果

             @param result 结果
             @param pszFromUserId 来源用户 Id
             @param pszFromUserName 来源用户名
             @param seq 请求 seq
             */
            virtual void OnInviteJoinLiveResponse(int result, const char *pszFromUserId, const char *pszFromUserName, int seq) {}
            
            /**
             结束连麦结果

             @param result 结果
             @param seq 请求 seq
             @param pszRoomID 房间 ID
             */
            virtual void OnEndJoinLive(int result, int seq, const char *pszRoomID) {}
            
            /**
             推流质量更新

             @param pszStreamID 流 ID
             @param quality 发布质量，0~3 分别对应优、良、中、差
             @param videoFPS 帧率
             @param videoKBS 码率
             */
            virtual void OnPublishQulityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS) {}
            
            /**
             推流质量更新

             @param pszStreamID 流 ID
             @param publishQuality ZegoPublishQuality 对象，内含各项推流质量数据
             */
            virtual void OnPublishQualityUpdate(const char* pszStreamID, ZegoPublishQuality publishQuality) {}
            
            /**
             采集视频的宽度和高度变化通知

             @param nWidth 视频宽度
             @param nHeight 视频高度
             @attention 发布直播成功后，当视频尺寸变化时，发布者会收到此通知
             */
            virtual void OnCaptureVideoSizeChanged(int nWidth, int nHeight) {}
            
            virtual void OnCaptureVideoSizeChanged(AV::PublishChannelIndex index, int nWidth, int nHegith) {}
            
            /**
             预览截图

             @param pImage 截图结果
             */
            virtual void OnPreviewSnapshot(void *pImage) {}
            
            virtual void OnPreviewSnapshot(AV::PublishChannelIndex index, void *pImage) {}
            
            /**
             混音数据输入回调

             @param pData 混音数据
             <p><b>注意：</b>
             1. 最大支持 48k 采样率、双声道、16位深的 PCM 音频数据；<br>
             2. 实际数据长度应根据当前音频数据的采样率及声道数决定；<br>
             3. 为确保混音效果，请不要在此 API 中执行耗时操作</p>
             @param pDataLen pDataLen既是输入参数也是输出参数；
                             作为输入参数，SDK会提供好长度值，用户按照这个长度写入数据即可，数据充足的情况下，无需更改*pDataLen的值
                             作为输出参数，如果填写的数据不足SDK提供的长度值，则*pDataLen = 0,
                             或者最后的尾音不足 SDK提供的长度值，可以用静音数据补齐。
             @param pSampleRate 混音数据采样率，支持16k、32k、44.1k、48k
             @param pNumChannels 混音数据声道数，支持1、2
             @attention 用户调用该 API 将混音数据传递给 SDK
             @note 混音数据 bit depth 必须为 16
             @warning Deprecated 请使用 zego-api-audio-aux.h 中的 IZegoAudioAuxCallbackEx
             */
            virtual void OnAuxCallback(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels) {}
            
            /**
             混流请求结果回调

             @param result 结果
             @param pszMixStreamID 混流 ID
             @param seq 请求 seq
             */
            virtual void OnMixStream(const AV::ZegoMixStreamResult& result, const char* pszMixStreamID, int seq) {}
            
            /**
             转推CDN状态通知

             @param streamID 流ID
             @param statesInfo 转推CDN状态信息列表
             @param statesInfoCount 状态信息列表个数
             */
            virtual void OnRelayCDNStateUpdate(const char *streamID, AV::ZegoStreamRelayCDNInfo* statesInfo, unsigned int statesInfoCount) {}
            
            /**
             添加/删除转推地址状态回调
             
             @param pszStreamID 流 ID
             @param strTarget 转推地址（支持rtmp/avertp）
             @param errorCode 错误码
             */
            virtual void OnUpdatePublishTargetState(int errorCode, const char *streamID, int seq) {}
            
            /**
             采集视频的首帧通知
             */
            virtual void OnCaptureVideoFirstFrame() {}
            
            virtual void OnCaptureVideoFirstFrame(AV::PublishChannelIndex idx) {}
            
            /**
             采集音频的首帧通知
             */
            virtual void OnCaptureAudioFirstFrame() {}
            
            virtual ~ILivePublisherCallback() {}
            
            /**
             更新混流配置回调
 
             @note 不建议使用，请用 OnMixStream
             */
            virtual void OnUpdateMixStreamConfig(unsigned int uiErrorCode, const char* pszMixStreamID, const ZegoPublishingStreamInfo& oStreamInfo) {}
        };
    }
}
#endif /* LiveRoomCallback_Publisher_h */
