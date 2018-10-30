//
//  LiveRoomCallback-ReliableMessage.h
//  zegoliveroom
//
//  Copyright © 2018年 Zego. All rights reserved.
//
//

#ifndef LiveRoomCallback_ReliableMessage_h
#define LiveRoomCallback_ReliableMessage_h

#include "./LiveRoomDefines.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class IReliableMessageCallback
        {
        public:
            
            /**
             发送可靠业务广播的回调

             @param errorCode   错误码，0 表示无错误
             @param pszRoomID   房间 ID
             @param sendSeq     发送序号 seq
             @param pszMsgType  业务类型
             @param msgSeq      业务服务端最新序号
             */
            virtual void OnSendReliableMessage(int errorCode, const char *pszRoomID, int sendSeq, const char *pszMsgType, const unsigned int msgSeq) {}
            
            /**
             收到业务广播的推送
             
             @param pszRoomID       房间 ID
             @param pszMsgType      业务类型
             @param pszMsgData      业务数据
             @param msgSeq          业务服务端序号
             @param pszUserId       广播者ID
             @param pszUsername     广播者名字
             @param sendTime        广播发送时间戳
             */
            virtual void OnRecvReliableMessage(const char *pszRoomID, const char *pszMsgType, const char *pszMsgData, unsigned int msgSeq, const char *pszUserId, const char *pszUsername, unsigned long long sendTime) {}
            
            virtual ~IReliableMessageCallback() {}
        };
    }
}
#endif /* LiveRoomCallback_ReliableMessage_h */
