//
//  ChatRoomCallback.h
//  zegoliveroom
//
//  Created by Strong on 2017/2/21.
//
//

#ifndef ChatRoomCallback_h
#define ChatRoomCallback_h

#include "./LiveRoomDefines.h"
#include "./LiveRoomDefines-IM.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        class IChatRoomCallback
        {
        public:
            /**
             登录聊天室成功回调

             @param errorCode 错误码，0 表示无错误
             */
            virtual void OnLoginChatRoom(int errorCode) = 0;

            /**
             退出聊天室

             @param errorCode 错误码
             */
            virtual void OnLogoutChatRoom(int errorCode) {}
            
            /**
             因为使用同一个 UserId 登录，用户被挤出聊天室

             @param reason 被踢出原因
             */
            virtual void OnKickOutChatRoom(int reason) = 0;
            
            /**
             当前网络连接状态

             @param state 当前网络连接状态
             @param errorCode 错误码
             */
            virtual void OnConnectState(int state, int errorCode) = 0;
            
            /**
             发送广播消息结果

             @param errorCode 错误码
             @param sendSeq 发送 seq
             @param messageId server 返回的消息 id
             */
            virtual void OnBroadMessageResult(int errorCode, int sendSeq, unsigned long long messageId) = 0;
            
            /**
             收到广播消息

             @param pMessage 收到的消息指针
             @param messageCount 消息条数
             */
            virtual void OnRecvBroadMessage(ROOM::ZegoRoomMessage *pMessage, unsigned int messageCount) = 0;
            
            /**
             创建讨论组结果

             @param errorCode 错误码
             @param sendSeq 发送 seq
             @param pszGroupId 讨论组 Id
             */
            virtual void OnCreateGroupChat(int errorCode, int sendSeq, const char *pszGroupId) = 0;

            /**
             获取讨论组信息

             @param errorCode 错误码
             @param pszGroupId 讨论组 Id
             @param pGroupInfo 讨论组信息（名称，创建时间，创建人等)
             @param pMemberList 讨论组成员列表
             @param memberCount 讨论组成员个数
             */
            virtual void OnGetGropuChatInfo(int errorCode, const char *pszGroupId, ROOM::ZegoConverInfo *pGroupInfo, ROOM::ZegoUser *pMemberList, unsigned int memberCount) = 0;
            
            /**
             讨论组消息发送结果

             @param errorCode 错误码
             @param pszGroupId 讨论组 Id
             @param sendSeq 发送 seq
             @param messageId 消息 Id
             */
            virtual void OnGroupMessageResult(int errorCode, const char *pszGroupId, int sendSeq, unsigned long long messageId) = 0;
            
            /**
             收到讨论组消息

             @param pMessage 讨论组消息信息
             @param pszGroupId 讨论组 Id
             */
            virtual void OnRecvGroupMessage(ROOM::ZegoConversationMessage *pMessage, const char *pszGroupId) = 0;
            
            /**
             发送 RequestVideoTalk 结果

             @param errorCode 错误码
             @param requestSeq 请求 seq
             */
            virtual void OnRequestVideoTalkResult(int errorCode, int requestSeq) = 0;
            
            /**
             收到 RequestVideoTalk 消息

             @param respondSeq 消息回应 seq
             @param pszUserId 发送者 UserId
             @param pszUserName 发送者 UserName
             @param pszContent 收到的附加消息内容
             */
            virtual void OnRecvRequestVideoTalk(int respondSeq, const char *pszUserId, const char *pszUserName, const char *pszContent) = 0;

            /**
             发送 CancelVideoTalk 结果

             @param errorCode 错误码
             @param requestSeq 请求 seq
             */
            virtual void OnCancelVideoTalkResult(int errorCode, int requestSeq) = 0;
            
            /**
             收到 CancelVideoTalk 消息

             @param respondSeq 消息回应 seq
             @param pszUserId 发送者 UserId
             @param pszUserName 发送者 UserName
             */
            virtual void OnRecvCancelVideoTalk(int respondSeq, const char *pszUserId, const char *pszUserName) = 0;
            
            /**
             发送 RespondVideoTalk 结果

             @param errorCode 错误码
             @param requestSeq 请求 seq
             */
            virtual void OnRespondVideoTalkResult(int errorCode, int requestSeq) = 0;
            
            /**
             收到 RespondVideoTalk 消息

             @param respondSeq 消息回应 seq
             @param pszUserId 发送者 UserId
             @param pszUserName 发送者 UserName
             @param result 是否同意
             */
            virtual void OnRecvRespondVideoTalk(int respondSeq, const char *pszUserId, const char *pszUserName, bool result) = 0;
            
            /**
             当前在线用户变化消息

             @param pUserInfo 用户信息
             @param userCount 用户个数
             @param type 更新类型
             */
            virtual void OnChatRoomUserUpdate(const ZegoUserInfo *pUserInfo, unsigned int userCount, ZegoUserUpdateType type) = 0;
        };
    }
}

#endif /* ChatRoomCallback_h */
