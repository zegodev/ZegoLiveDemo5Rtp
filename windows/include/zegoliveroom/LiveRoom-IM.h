//
//  LiveRoom-IM.h
//  zegoliveroom
//
//  Copyright © 2017年 Zego. All rights reserved.
//
//

#ifndef LiveRoom_IM_h
#define LiveRoom_IM_h

#include "./LiveRoomDefines-IM.h"
#include "./LiveRoomCallback-IM.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         设置 IM 信息通知的回调对象

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetIMCallback(IIMCallback* pCB);
    
        /**
         发送聊天室消息

         @param type 消息类型
         @param category 消息分类
         @param priority 消息优先级
         @param messageContent 消息内容, 不超过 512 字节
         @return 消息 seq
         @note Deprecated. 请使用 SendRoomMessageEx(ROOM::ZegoMessageType, ROOM::ZegoMessageCategory, const char *)
         */
        ZEGO_API int SendRoomMessage(ROOM::ZegoMessageType type, ROOM::ZegoMessageCategory category, ROOM::ZegoMessagePriority priority, const char *messageContent);
        
        /**
         发送聊天室消息
         
         @param type 消息类型
         @param category 消息分类
         @param messageContent 消息内容, 不超过 512 字节
         @return 消息 seq
         */
        ZEGO_API int SendRoomMessageEx(ROOM::ZegoMessageType type, ROOM::ZegoMessageCategory category, const char *messageContent);
        
        /**
         获取聊天室历史消息

         @param priority 消息优先级
         @param ascendOrder 历史消息新旧顺序
         @param messageId 消息ID
         @param messageCount 历史消息条数
         @return 操作是否成功
         */
        ZEGO_API bool GetRoomMessage(ROOM::ZegoMessagePriority priority, bool ascendOrder, unsigned long long messageId, int messageCount);
        
        /**
         在房间中创建一个会话

         @param conversationName 会话名称
         @param memberList 会话成员列表
         @param memberCount 会话成员数量
         @return 消息 seq
         */
        ZEGO_API int CreateConversation(const char *conversationName, ROOM::ZegoUser *memberList, unsigned int memberCount);
        
        /**
         获取会话相关信息

         @param conversationId 会话 Id
         @return true 成功，false 失败
         */
        ZEGO_API bool GetConversationInfo(const char *conversationId);
        
        /**
         在会话中发送一条消息

         @param conversationId 会话 Id
         @param type 会话类型
         @param messageContent 消息内容
         @return 消息 seq
         */
        ZEGO_API int SendConversationMessage(const char *conversationId, ROOM::ZegoMessageType type, const char *messageContent);
        
        /**
         发送不可靠信道消息，主要用于大并发的场景，发送一些非必须到达的消息
         
         @param type 消息类型
         @param category 消息分类
         @param messageContent 消息内容, 不超过 512 字节
         @return 消息 seq
         */
        ZEGO_API int SendBigRoomMessage(ROOM::ZegoMessageType type, ROOM::ZegoMessageCategory category, const char *messageContent);
    }
}

#endif /* LiveRoom_IM_h */
