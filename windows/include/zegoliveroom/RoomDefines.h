//
//  RoomDefines.h
//  zegoliveroom
//
//  Created by Strong on 2017/7/20.
//

#ifndef RoomDefines_h
#define RoomDefines_h

#include "./AVDefines.h"

#ifndef ZEGO_API
    #ifdef WIN32
        #ifdef ZEGO_EXPORTS
            #define ZEGO_API __declspec(dllexport)
        #else
            #define ZEGO_API __declspec(dllimport)
        #endif
    #else
        #define ZEGO_API __attribute__((visibility("default")))
    #endif
#endif

namespace ZEGO
{
    namespace COMMON
    {
        /** 网络类型 */
        enum ZEGONetType
        {
            ZEGO_NT_NONE = 0,       /**< 无网络 */
            ZEGO_NT_LINE = 1,       /**< 有线网络 */
            ZEGO_NT_WIFI = 2,       /**< 无线网络 */
            ZEGO_NT_2G = 3,         /**< 2G网络 */
            ZEGO_NT_3G = 4,         /**< 3G网络 */
            ZEGO_NT_4G = 5,         /**< 4G网络 */
            ZEGO_NT_UNKNOWN = 32    /**< 未知网络 */
        };
        
        struct ZegoStreamInfo
        {
            ZegoStreamInfo()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
                szStreamId[0] = '\0';
                szExtraInfo[0] = '\0';
            }
            
            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
            char szStreamId[ZEGO_MAX_COMMON_LEN];
            char szExtraInfo[ZEGO_MAX_EXTRA_INFO_LEN];
        };
        
        /** 流更新类型 */
        enum ZegoStreamUpdateType
        {
            StreamAdded     = 2001,     /**< 新增流 */
            StreamDeleted   = 2002,     /**< 删除流 */
        };

        /** 发布直播的模式 */
        enum ZegoPublishFlag
        {
            ZEGO_JOIN_PUBLISH = 0,        /**< 连麦模式 */
            ZEGO_MIX_STREAM = 1 << 1,   /**< 混流模式 */
            ZEGO_SINGLE_ANCHOR = 1 << 2,   /**< 单主播模式 */
        };
        
        struct ZegoPublishingStreamInfo
        {
            ZegoPublishingStreamInfo()
            {
                uiRtmpURLCount = 0;
                uiHlsURLCount = 0;
                uiFlvURLCount = 0;
            }
            const char* arrRtmpURLs[ZEGO_MAX_URL_COUNT];   /**< RTMP 播放 URL 列表 */
            unsigned int uiRtmpURLCount;                   /**< RTMP URL 个数 */
            
            const char* arrFlvURLs[ZEGO_MAX_URL_COUNT];
            unsigned int uiFlvURLCount;
            
            const char* arrHlsURLs[ZEGO_MAX_URL_COUNT];
            unsigned int uiHlsURLCount;
        };

        /** 成员角色 */
        enum ZegoRoomRole
        {
            UnknownRole = 0,/**< 未知角色 */
            Anchor = 1,     /**< 主播 */
            Audience = 2,   /**< 观众 */
            Assistant = 32, /**< 助教 */
        };

        /** 用户更新类型 */
        enum ZegoUserUpdateType
        {
            UPDATE_TOTAL = 1,   /**< 全量更新 */
            UPDATE_INCREASE,    /**< 增量更新 */
        };

        /** 用户更新属性 */
        enum ZegoUserUpdateFlag
        {
            USER_ADDED = 1,     /**< 新增 */
            USER_DELETED,       /**< 删除 */
        };

        struct ZegoUserInfo
        {
            ZegoUserInfo()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
            }

            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
            ZegoUserUpdateFlag udapteFlag;
            ZegoRoomRole role;
        };
    }
}

#ifndef ZegoRoomDefines_h

namespace ZEGO
{
    namespace ROOM
    {
        struct ZegoUser
        {
            ZegoUser()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
            }

            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
        };

        /** 消息类型 */
        enum ZegoMessageType
        {
            Text = 1,           /**< 文字 */
            Picture,            /**< 图片 */
            File,               /**< 文件 */
            OtherType = 100,    /**< 其他 */
        };

        /** 消息优先级 */
        enum ZegoMessagePriority
        {
            Default = 2,        /**< 默认优先级 */
            High = 3,           /**< 高优先级 */
        };

        /** 消息类别 */
        enum ZegoMessageCategory
        {
            Chat = 1,           /**< 聊天 */
            System,             /**< 系统 */
            Like,               /**< 点赞 */
            Gift,               /**< 送礼物 */
            OtherCategory = 100,/**< 其他 */
        };
        
        /** Relay类别 */
        enum ZegoRelayType
        {
            RelayTypeNone = 1,
            RelayTypeDati = 2,
        };

        struct ZegoRoomMessage
        {
            ZegoRoomMessage()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
                szContent[0] = '\0';
                role = COMMON::Audience;
                type = Text;
                priority = Default;
                category = Chat;
                sendTime = 0;
            }

            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
            COMMON::ZegoRoomRole role;
            char szContent[ZEGO_MAX_COMMON_LEN];
            unsigned long long messageId;
            ZegoMessageType type;
            ZegoMessagePriority priority;
            ZegoMessageCategory category;
            unsigned long long sendTime;
        };

        struct ZegoConversationMessage
        {
            ZegoConversationMessage()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
                szContent[0] = '\0';
                type = Text;
                sendTime = 0;
            }

            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
            char szContent[ZEGO_MAX_COMMON_LEN];
            unsigned long long messageId;
            ZegoMessageType type;
            unsigned long long sendTime;
        };

        struct ZegoConverInfo
        {
            char szConverName[ZEGO_MAX_COMMON_LEN];
            char szCreatorId[ZEGO_MAX_USERID_LEN];
            int createTime;
        };
        
        struct ZegoBigRoomMessage
        {
            ZegoBigRoomMessage()
            {
                szUserId[0] = '\0';
                szUserName[0] = '\0';
                szContent[0] = '\0';
                szMessageId[0] = '\0';
                role = COMMON::Audience;
                type = Text;
                category = Chat;
                sendTime = 0;
            }
            
            char szUserId[ZEGO_MAX_USERID_LEN];
            char szUserName[ZEGO_MAX_USERNAME_LEN];
            COMMON::ZegoRoomRole role;
            char szContent[ZEGO_MAX_COMMON_LEN];
            char szMessageId[ZEGO_MAX_IDENTITY_LEN];
            ZegoMessageType type;
            ZegoMessageCategory category;
            unsigned long long sendTime;
        };
        
        struct ZegoReliableMessage
        {
            /** 消息类型 */
            const char *type;
            /** 当前最新消息Seq */
            unsigned int latestSeq;
            /** 消息内容 */
            const char *content;
            /** 消息发送UserID */
            const char *userID;
            /** 消息发送UserName */
            const char *userName;
            /** 发送时间 */
            unsigned long long sendTime;
        };
        
        struct ZegoReliableMessageInfo
        {
            /** 消息类型 */
            const char *type;
            /** 当前最新消息Seq */
            unsigned int latestSeq;
        };
    }
}

#endif  /* ZegoRoomDefines_h */
#endif /* RoomDefines_h */


