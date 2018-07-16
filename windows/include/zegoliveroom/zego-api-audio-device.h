#ifndef zego_api_audio_device_h
#define zego_api_audio_device_h

namespace ZEGO
{
    namespace AUDIODEVICE
    {
#ifdef WIN32
        /**
         设置双声道采集

         @param captureType default is 0. 0:capture mono any time; 1: capture stereo any time;2: capture mono when voice chat(publish and play at the same time), capture stereo when only publish.PS: Do not do inner processing when capture stereo.
         @return true 成功，false 失败
         @discussion  必须在初始化 SDK 之后，启用音视频功能前调用（如预览画面StartPreview、推流StartPublishing之前调用）。
         */
        ZEGOAVKIT_API bool EnableCaptureStereo(int captureType);
    }
#endif
}

#endif /* zego_api_audio_device_h */
