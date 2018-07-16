#ifndef zego_api_audio_encrypt_decrypt_h
#define zego_api_audio_encrypt_decrypt_h
#include "zego-api-defines.h"

namespace ZEGO
{
    namespace AUDIO_ENCRYPT_DECRYPT
    {
        class IZegoAudioEncryptDecryptCallback
        {
        public:
            /**
             音频加密、解密回调
             
             @param pszStreamID 标识当前回调的音频数据属于哪条流
             @param pInData  SDK回调给用户的音频数据, 推流时用于加密，拉流时用于解密
             @param inDataLen SDK回调给用户的音频数据的长度（单位：btye）
             @param pOutData 用户将加密（推流）或者解密（拉流）后的音频数据回传给SDK
             @param pOutDataLen 用户实际回传给SDK的数据大小（单位：btye)
             @param maxOutBufLen 用户回传数据的缓冲区的最大长度（单位：btye）
             **/
            virtual void OnAudioEncryptDecryptCallback(const char* pszStreamID, const unsigned char *pInData, int inDataLen, unsigned char *pOutData, int* pOutDataLen, int maxOutBufLen) = 0;
            virtual ~IZegoAudioEncryptDecryptCallback(){};
        };
        
        /**
         音频加密、解密开关
         
         @param enable：开启，false 关闭
         @discussion 必须在init sdk之前调用
         */
        ZEGOAVKIT_API void EnableAudioEncryptDecrypt(bool enable);
        
        /**
         设置回调，接收音频数据进行加密或者解密后，再回传给sdk
         
         @param 音频加密、解密回调
         @param discussion 成功推流、拉流后才会有回调
         **/
        ZEGOAVKIT_API void SetAudioEncryptDecryptCallback(IZegoAudioEncryptDecryptCallback* pCB);
    }
}
#endif
