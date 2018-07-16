//
//  LiveRoomCallback-Relay.h
//  zegoliveroom
//
//  Copyright © 2018年 Zego. All rights reserved.
//
//

#ifndef LiveRoomCallback_Relay_h
#define LiveRoomCallback_Relay_h

#include "./LiveRoomDefines.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class IRelayCallback
        {
        public:
            
            /**
             发送转发结果

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param sendSeq 发送序号 seq
             @param type    转发的类型
             @param pszRelayResult 转发的结果
             */
            virtual void OnRelay(int errorCode, const char *pszRoomID, int sendSeq, ZEGO::ROOM::ZegoRelayType type, const char *pszRelayResult) {}
            
            virtual ~IRelayCallback() {}
        };
    }
}
#endif /* LiveRoomCallback_Relay_h */
