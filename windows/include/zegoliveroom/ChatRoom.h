//
//  ChatRoom.h
//  zegoliveroom
//
//  Created by Strong on 2017/2/21.
//
//

#ifndef ChatRoom_h
#define ChatRoom_h

#include "./ChatRoomCallback.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         设置聊天室回调对象

         @param pCB 回调对象指针
         @return true 成功，false 失败
         @note 未设置回调对象，或对象设置错误，可能导致无法正常收到相关回调
         */
        ZEGO_API bool SetChatRoomCallback(IChatRoomCallback *pCB);

        /**
         登录聊天室

         @return true 成功，false 失败
         @attention 登录成功后，等待 IChatRoomCallback::OnLoginChatRoom 回调
         @note 使用聊天室功能前，必须确保登录成功
         */
        ZEGO_API bool LoginChatRoom();
        
        /**
         退出聊天室

         @return true 成功，false 失败
         @attention 退出成功后，等待 IChatRoomCallback::OnLogoutRoom 回调
         */
        ZEGO_API bool LogoutChatRoom();
        
        /**
         聊天室发送广播消息

         @param type 消息类型
         @param category 消息分类
         @param priority 消息优先级, deprecated, 由 SDK 内部确定优先级
         @param messageContent 消息内容
         @return 消息发送 seq
         */
        ZEGO_API int SendBroadMessage(ROOM::ZegoMessageType type, ROOM::ZegoMessageCategory category, ROOM::ZegoMessagePriority priority, const char *messageContent);
        
        /**
         创建讨论组

         @param groupName 讨论组名称
         @param memberList 讨论组用户
         @param memberCount 讨论组成员数量
         @return 消息发送 seq
         */
        ZEGO_API int CreateGroupChat(const char *groupName, ROOM::ZegoUser *memberList, unsigned int memberCount);
        
        /**
         获取讨论组信息

         @param pszGroupId 讨论组 Id
         @return true 成功，false 失败
         @attention 成功后，在 IChatRoomCallback::OnGetGropuChatInfo 回调中获取信息
         */
        ZEGO_API bool GetGroupChatInfo(const char *pszGroupId);
        
        /**
         发送讨论组消息

         @param pszGroupId 讨论组 Id
         @param type 消息类型
         @param messageContent 消息内容
         @return 消息发送 seq
         */
        ZEGO_API int SendGroupChatMessage(const char *pszGroupId, ROOM::ZegoMessageType type, const char *messageContent);
        
        /**
         邀请视频通话

         @param memberList 请求视频通话成员，用户必须在线
         @param memberCount 视频通话成员个数
         @param pszVideoRoomId 视频通话房间 Id
         @return 消息发送 seq
         */
        ZEGO_API int RequestVideoTalk(ROOM::ZegoUser *memberList, unsigned int memberCount, const char *pszVideoRoomId);

        /**
         取消视频通话

         @param requestSeq 请求视频通话的 seq
         @return true 取消成功，false 取消失败
         */
        ZEGO_API bool CancelVideoTalk(int requestSeq);
        
        /**
         回应视频通话

         @param respondSeq 收到视频通话请求的 seq
         @param respondResult 同意/拒绝视频通话
         @return true 成功，false 失败
         */
        ZEGO_API bool RespondVideoTalk(int respondSeq, bool respondResult);
    }
}
#endif /* ChatRoom_h */
