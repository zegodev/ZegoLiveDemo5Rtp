#ifndef zego_api_sound_level_h
#define zego_api_sound_level_h

#include <zego-api-defines.h>

namespace ZEGO
{
    namespace SOUNDLEVEL
    {
    
        struct ZegoSoundLevelInfo
        {
            ZegoSoundLevelInfo()
            {
                szStreamID[0] = '\0';
                soundLevel = 0.0f;
            }
            
            char szStreamID[ZEGO_MAX_COMMON_LEN];
            float soundLevel;
        };
        
        class IZegoSoundLevelCallback
        {
        public:
            /**
             获取 soundLevel 更新的回调

             @param vecSoundLevels 房间内所有流（非自己推的流）的 soundLevel 值
             */
            virtual void OnSoundLevelUpdate(ZegoSoundLevelInfo *pSoundLevelList, unsigned int soundLevelCount) = 0;
            
            /**
             获取 captureSoundLevel 更新的回调
             
             @param pCaptureSoundLevel 房间内采集 soundLevel 值（自己推的流）
             */
            virtual void OnCaptureSoundLevelUpdate(ZegoSoundLevelInfo *pCaptureSoundLevel) = 0;
            
            virtual ~ IZegoSoundLevelCallback() {}
        };

        /**
         设置获取 soundLevel 的回调对象
         
         @param pCB 实现 IZegoSoundLevelCallback 协议的对象
         @return true 成功；false 失败
         */
        ZEGOAVKIT_API bool SetSoundLevelCallback(IZegoSoundLevelCallback* pCB);
        
        /**
         设置 soundLevel 的监控周期
         
         @param timeInMS 时间周期，单位为毫秒，取值范围 [100, 3000]。默认 200 ms。
         @return true 成功；false 失败
         */
        ZEGOAVKIT_API bool SetSoundLevelMonitorCycle(unsigned int timeInMS);
        
        /**
         启动 soundLevel 监听
         
         @return true 成功，等待回调；false 失败
         @discussion StartSoundLevelMonitor 后一定要 StopSoundLevelMonitor
         */
        ZEGOAVKIT_API bool StartSoundLevelMonitor();
        
        /**
         停止 soundLevel 监听
         
         @return true 成功；false 失败
         */
        ZEGOAVKIT_API bool StopSoundLevelMonitor();
        
    }
}

#endif /* zego_api_sound_level_h */
