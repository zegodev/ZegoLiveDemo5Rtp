#include "ZegoRoomMsgModel.h"


QZegoRoomMsgModel::QZegoRoomMsgModel(const QString &userId, const QString &userName, const QString &content, unsigned long long msgId, ROOM::ZegoMessageType type, ROOM::ZegoMessagePriority priority, ROOM::ZegoMessageCategory category)
{
	m_strUserId = userId;
	m_strUserName = userName;
	m_strContent = content;
	m_ullMsgId = msgId;
	m_nMsgType = type;
	m_nMsgPriority = priority;
	m_nMsgCategory = category;
}

QZegoRoomMsgModel::QZegoRoomMsgModel(const QZegoRoomMsgModel& otherRoom)
{
	m_strUserId = otherRoom.m_strUserId;
	m_strUserName = otherRoom.m_strUserName;
	m_strContent = otherRoom.m_strContent;
	m_ullMsgId = otherRoom.m_ullMsgId;
	m_nMsgType = otherRoom.m_nMsgType;
	m_nMsgPriority = otherRoom.m_nMsgPriority;
	m_nMsgCategory = otherRoom.m_nMsgCategory;
}

QZegoRoomMsgModel::~QZegoRoomMsgModel()
{
}

QString QZegoRoomMsgModel::getUserId(void)
{
	return m_strUserId;
}

QString QZegoRoomMsgModel::getUserName(void)
{
	return m_strUserName;
}

QString QZegoRoomMsgModel::getContent(void)
{
	return m_strContent;
}

unsigned long long QZegoRoomMsgModel::getMsgId(void)
{
	return m_ullMsgId;
}

ROOM::ZegoMessageType QZegoRoomMsgModel::getMsgType(void)
{
	return m_nMsgType;
}

ROOM::ZegoMessagePriority QZegoRoomMsgModel::getMsgPriority(void)
{
	return m_nMsgPriority;
}

ROOM::ZegoMessageCategory QZegoRoomMsgModel::getMsgCategory(void)
{
	return m_nMsgCategory;
}

