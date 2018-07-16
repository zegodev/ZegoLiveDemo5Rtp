//
//  LiveRoomCallback-IM.h
//  zegoliveroom
//
//  Copyright © 2017年 Zego. All rights reserved.
//
//

#ifndef LiveRoomCallback_IM_h
#define LiveRoomCallback_IM_h

#include "./LiveRoomDefines-IM.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class IIMCallback
        {
        public:
            /**
             用户状态更新

             @param pUserInfo 用户信息
             @param userCount 用户数
             @param type 更新类型
             */
            virtual void OnUserUpdate(const ZegoUserInfo *pUserInfo, unsigned int userCount, ZegoUserUpdateType type) = 0;
            
            /**
             在线人数更新
             
             @param onlineCount 在线人数
             @param pszRoomID 房间 ID
             */
            virtual void OnUpdateOnlineCount(int onlineCount, const char *pszRoomID) {};
            
            /**
             发送房间消息结果

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param sendSeq 发送消息 seq
             @param messageId 消息 Id
             */
            virtual void OnSendRoomMessage(int errorCode, const char *pszRoomID, int sendSeq, unsigned long long messageId) {}
            
            /**
             创建会话消息结果

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param sendSeq 消息 seq
             @param pszConversationID 会话 ID
             */
            virtual void OnCreateConversation(int errorCode, const char *pszRoomID, int sendSeq, const char *pszConversationID) {}
            
            /**
             获取会话信息结果

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param pszConverID 会话 ID
             @param pConverInfo 会话信息
             @param pMemberList 会话成员列表
             @param memberCount 会话成员数量
             */
            virtual void OnGetConversationInfo(int errorCode, const char *pszRoomID, const char *pszConverID, ROOM::ZegoConverInfo *pConverInfo, ROOM::ZegoUser *pMemberList, unsigned int memberCount) {}
           
            /**
             发送会话消息

             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param pszConverID 会话 ID
             @param sendSeq 消息 seq
             @param messageId 消息 Id
             */
            virtual void OnSendConversationMessage(int errorCode, const char *pszRoomID, const char *pszConverID, int sendSeq, unsigned long long messageId) {}
            
            /**
             收到房间消息回调

             @param pMessageInfo 消息信息
             @param messageCount 消息个数
             @param pszRoomID 房间 ID
             */
            virtual void OnRecvRoomMessage(ROOM::ZegoRoomMessage *pMessageInfo, unsigned int messageCount, const char *pszRoomID) {}
            
            
            /**
             主动拉取房间历史消息回调

             @param pMessageInfo 消息信息
             @param messageCount 消息个数
             @param pszRoomID 房间ID
             @param haveMore 是否还有更多消息
             */
            virtual void OnGetRoomMessage(int erroCode, ROOM::ZegoRoomMessage *pMessageInfo, unsigned int messageCount, const char *pszRoomID, bool haveMore) {}
            
            /**
             收到会话消息

             @param pMessageInfo 消息信息
             @param pszConversationID 会话 ID
             @param pszRoomID 房间 ID
             */
            virtual void OnRecvConversationMessage(ROOM::ZegoConversationMessage *pMessageInfo, const char *pszConversationID, const char *pszRoomID) {}
            
            /**
             发送不可靠消息结果，这个接口用于大并发情景
             
             @param errorCode 错误码，0 表示无错误
             @param pszRoomID 房间 ID
             @param sendSeq 发送消息 seq
             @param pszmessageID 消息 Id
             */
            virtual void OnSendBigRoomMessage(int errorCode, const char *pszRoomID, int sendSeq, const char *pszmessageID) {}
            
            /**
             收到不可靠消息回调
             
             @param pMessageInfo 消息信息
             @param messageCount 消息个数
             @param pszRoomID 房间 ID
             */
            virtual void OnRecvBigRoomMessage(ROOM::ZegoBigRoomMessage *pMessageInfo, unsigned int messageCount, const char *pszRoomID) {}
            
            virtual ~IIMCallback() {}
        };
    }
}
#endif /* LiveRoomCallback_IM_h */
