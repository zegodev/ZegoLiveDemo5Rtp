//
//  LiveRoom-Relay.h
//  zegoliveroom
//
//  Copyright © 2018年 Zego. All rights reserved.
//
//

#ifndef LiveRoom_Relay_h
#define LiveRoom_Relay_h

#include "./LiveRoomDefines.h"
#include "./LiveRoomCallback-Relay.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         设置 Relay 通知的回调对象

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetRelayCallback(IRelayCallback* pCB);
    
        /**
         转发接口

         @param relayType 转发类型
         @param pszRelayData 转发内容
         @return 发送序号 seq
         */
        ZEGO_API int Relay(ROOM::ZegoRelayType relayType, const char *pszRelayData);
    }
}

#endif /* LiveRoom_Relay_h */
