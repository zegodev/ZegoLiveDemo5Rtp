//
//  zego-api-mediaplayer.h
//  ZegoLiveRoom
//
//  Created by kebo on 26/10/2017.
//

#ifndef zego_api_mediaplayer_h
#define zego_api_mediaplayer_h

#include "zego-api-defines.h"
#include "media_player.h"


namespace ZEGO
{
namespace MEDIAPLAYER
{
    
    /**
     获取播放器

     @param type 播放器类型（AVE::IMediaPlayer::PlayerType）
     @return 播放器指针（AVE::IMediaPlayer*）
     @note 不要删除返回的 AVE::IMediaPlayer 指针，由引擎控制其生命周期
     @note 播放器只有在引擎启动的情况下才有效，需要在 InitSDK 后再调用，且不能和 InitSDK 在同一个函数里调用。
     */
    ZEGOAVKIT_API AVE::IMediaPlayer* GetMediaPlayer(AVE::IMediaPlayer::PlayerType type);
    
}
}



#endif /* zego_api_mediaplayer_h */
