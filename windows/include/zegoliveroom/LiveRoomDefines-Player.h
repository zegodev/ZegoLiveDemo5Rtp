//
//  LiveRoomDefines-Player.h
//  ZegoLiveRoom
//

#ifndef LiveRoomDefines_Player_h
#define LiveRoomDefines_Player_h

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         流媒体次要信息回调
         
         @param pszStreamID 流ID，标记当前回调的信息属于哪条流
         @param buf，数据缓冲区，存储流媒体次要信息
         @param dataLen, 缓冲区长度
         */
        typedef void (OnMediaSideCallback)(const char * pszStreamID, const unsigned char *buf, int dataLen);
    }
}
#endif /* LiveRoomDefines_Player_h */
