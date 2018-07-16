//
//  zego-api-audio-aux.h
//

#ifndef zego_api_audio_aux_h
#define zego_api_audio_aux_h

namespace ZEGO
{
    namespace AUDIOAUX
    {
        class IZegoAuxCallback
        {
        public:
            /** 混音音频数据输入回调。
             当开启混音后，通过此回调获取混音音频数据。
             发送媒体次要信息前需要调用setMediaSideFlags设置媒体次要信息开关
             此接口带媒体次要信息时必须要带有混音音频数据才能发送媒体次要信息
             如果不带混音音频数据则会丢掉媒体次要信息
             <p><b>注意：</b>
             1. 每次必须返回 20ms 时长的音频数据；<br>
             2. 最大支持 48k 采样率、双声道、16位深的 PCM 音频数据；<br>
             3. 实际数据长度应根据当前音频数据的采样率及声道数决定；<br>
             4. 为确保混音效果，请不要在此 API 中执行耗时操作</p>
             @param pDataLen
             20ms音频数据长度计算如下：
             长度 = 采样率 * 20 / 1000 * 位深字节数 * 通道数 位深字节数固定为2
             例如: 44.1K采样率双声道20ms数据的长度*pDataLen为：
             *pDataLen = 44100 * 20 / 1000 * 2 * 2 = 3528
             @param pSampleRate 混音数据采样率，支持16k、32k、44.1k、48k
             @param pNumChannels 混音数据声道数，支持1、2
             @param pSideInfo 媒体次要信息数据缓冲区地址
             @param pSideInfoLength 媒体次要信息数据缓冲区长度
             @param bPacket  媒体次要信息数据是否外部已经打包好包头
             @attention 用户调用该 API 将混音数据传递给 SDK
             @note 混音数据 bit depth 必须为 16
             */
            virtual void OnAuxCallbackEx(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels,unsigned char *pSideInfo, int *pSideInfoLen, bool *bPacket) = 0;
            
            virtual ~IZegoAuxCallback() {}
        };
    
        /**
         混音开关

         @param bEnable bEnable true 启用混音输入；false 关闭混音输入
         @return true 成功，false 失败
         */
        ZEGOAVKIT_API bool EnableAux(bool bEnable);
        
        /**
         * 设置混音带有媒体次要信息回调
         * @param pCB 回调对象指针
         * @return true 成功，false 失败
         */
        ZEGOAVKIT_API bool SetAuxCallback(IZegoAuxCallback* pCB);
    }
}

#endif /* zego_api_audio_aux_h */
