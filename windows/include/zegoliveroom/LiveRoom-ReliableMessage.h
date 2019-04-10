//
//  LiveRoom-ReliableMessage.h
//  zegoliveroom
//
//  Copyright © 2018年 Zego. All rights reserved.
//
//

#ifndef LiveRoom_ReliableMessage_h
#define LiveRoom_ReliableMessage_h

#include "./LiveRoomDefines.h"
#include "./LiveRoomCallback-ReliableMessage.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         设置 ReliableMessage 通知的回调

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetReliableMessageCallback(IReliableMessageCallback* pCB);
    
        /**
         可靠业务广播通道

         @param pszMsgType 业务类型，不能超过 128 字节, 不允许为空字符串
         @param pszMsgData 业务内容，不能超过 2048 字节, 允许为空字符串
         @return 发送序号 seq
         */
        ZEGO_API int SendReliableMessage(const char *pszMsgType, const char *pszMsgData);
        
    }
}

#endif /* LiveRoom_ReliableMessage_h */
