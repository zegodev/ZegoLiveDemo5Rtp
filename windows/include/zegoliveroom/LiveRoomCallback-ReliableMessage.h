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
             发送可靠业务消息的结果回调

             @param errorCode   错误码，0 表示无错误
             @param pszRoomID   房间 ID
             @param sendSeq     发送序号 seq
             @param pszMsgType  消息类型
             @param latestSeq   最新的消息 seq
             */
            virtual void OnSendReliableMessage(int errorCode, const char *pszRoomID, int sendSeq, const char *pszMsgType, unsigned int latestSeq) {}
            
            /**
             收到可靠业务消息
             
             @param pszRoomID       房间 ID
             @param message         可靠业务消息
             */
            virtual void OnRecvReliableMessage(const char *pszRoomID, const ROOM::ZegoReliableMessage& message) {}
            
            
            /**
             获取最新可靠业务消息的结果回调

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param sendSeq 发送序号 seq
             @param messageList 可靠业务消息列表
             @param messageCount 可靠业务消息个数
             */
            virtual void OnGetReliableMessage(int errorCode, const char *pszRoomID, int sendSeq, ROOM::ZegoReliableMessage *messageList, unsigned int messageCount) {}
            
            
            /**
             定时更新房间内可靠业务消息信息回调

             @param pszRoomID 房间 ID
             @param messageInfoList 可靠业务消息信息列表
             @param messageInfoCount 可靠业务消息信息个数
             */
            virtual void OnUpdateReliableMessageInfo(const char *pszRoomID, ROOM::ZegoReliableMessageInfo *messageInfoList, unsigned int messageInfoCount) {}
            
            
            virtual ~IReliableMessageCallback() {}
        };
    }
}
#endif /* LiveRoomCallback_ReliableMessage_h */
