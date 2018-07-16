#pragma once

#include <QObject>
#include <QVector>
#include "LiveRoomDefines-IM.h"

using namespace ZEGO;

class QZegoRoomMsgModel
{
public :
	QZegoRoomMsgModel(const QString &userId, const QString &userName, const QString &content, unsigned long long msgId, ROOM::ZegoMessageType msgType, ROOM::ZegoMessagePriority msgPriority, ROOM::ZegoMessageCategory msgCategory);
	QZegoRoomMsgModel(const QZegoRoomMsgModel &otherRoom);
	~QZegoRoomMsgModel();
	                                                                                                                                                                                                                  
public :
	QString getUserId(void);
	QString getUserName(void);
	QString getContent(void);
	unsigned long long getMsgId(void);
	ROOM::ZegoMessageType getMsgType(void);
	ROOM::ZegoMessagePriority getMsgPriority(void);
	ROOM::ZegoMessageCategory getMsgCategory(void);

private :
	QString m_strUserId;
	QString m_strUserName;
	QString m_strContent;
	unsigned long long m_ullMsgId;
	ROOM::ZegoMessageType m_nMsgType;
	ROOM::ZegoMessagePriority m_nMsgPriority;
	ROOM::ZegoMessageCategory m_nMsgCategory;
};

using RoomMsgPtr = QSharedPointer < QZegoRoomMsgModel > ;
