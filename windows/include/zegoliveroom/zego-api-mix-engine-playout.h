//
//  zego-api-mix-engine-playout.h
//  zegoavkit
//
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef zego_api_mix_engine_playout_h
#define zego_api_mix_engine_playout_h

namespace ZEGO
{
namespace MIXENGINE
{
 
    /**
     把引擎播放的声音混到推流中

     @param bEnable 是否生效
     @return 0 成功
     */
    ZEGOAVKIT_API int MixEnginePlayout(bool bEnable);
    
    /**
     设置引擎播放的声音混到推流中的音量
     @param volume 音量，0-100
     */
    ZEGOAVKIT_API void SetMixEnginePlayoutVolume(int volume);

}
}

#endif /* zego_api_mix_engine_playout_h */
