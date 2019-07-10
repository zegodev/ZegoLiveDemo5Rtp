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
        发送可靠业务消息

         @param pszMsgType 业务类型，不能超过 128 字节, 不允许为空字符串, 一个房间内只允许不超过10个不同的消息类型
         @param pszMsgData 可靠业务消息内容，不能超过 2048 字节, 允许为空字符串
         @param latestMsgSeq 当前此业务类型的最新server seq
         @return 发送序号 seq
         */
        ZEGO_API int SendReliableMessage(const char *pszMsgType, const char *pszContent, unsigned int latestMsgSeq);
        
        
        /**
         获取当前最新的可靠业务消息

         @param messageInfoList 业务消息信息列表
         @param messageCount 业务消息信息个数
         @return 请求序号 seq
         */
        ZEGO_API int GetReliableMessage(const char **pszMsgTypeList, unsigned int msgTypeCount);
    }
}

#endif /* LiveRoom_ReliableMessage_h */
