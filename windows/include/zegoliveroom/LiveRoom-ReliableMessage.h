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

         @param pszMsgType 业务类型，不能超过 128 字节
         @param pszMsgData 业务内容，不能超过 10240 字节
         @return 发送序号 seq
         */
        ZEGO_API int SendReliableMessage(const char *pszMsgType, const char *pszMsgData);
        
        /**
         获取可靠业务广播
         
         @param pszMsgType 业务类型
         @param msgSeq 本地最新的业务序号
         @return 发送序号 seq
         */
        ZEGO_API int GetReliableMessage(const char *pszMsgType, const unsigned int msgSeq);
    }
}

#endif /* LiveRoom_ReliableMessage_h */
