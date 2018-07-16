#pragma once

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include "ZegoUserModel.h"
#include "ZegoStreamModel.h"

class QZegoRoomModel
{
public :
	QZegoRoomModel() { m_strRoomId = nullptr; m_strRoomName = nullptr; }
	QZegoRoomModel(QString &roomId, QString &roomName, QString &anchorId, QString &anchorName);
	~QZegoRoomModel();

public :
	void setRoomId(const QString &roomId);
	QString getRoomId(void);

	void setRoomName(const QString &roomName);
	QString getRoomName(void);

	void setAnchorId(const QString &anchorId);
	QString getAnchorId(void);

	void setAnchorName(const QString &anchoName);
	QString getAnchorName(void);

	void setCreatedTime(unsigned int time);
	unsigned int getCreatedTime(void);

	void setLivesCount(unsigned int count);
	unsigned int getLivesCount(void);

	void addStream(StreamPtr stream);
	StreamPtr removeStream(const QString &streamId);
	int getStreamCount(void);
	StreamPtr getStreamById(const QString &streamId);
	QVector<StreamPtr> getStreamList(void);

private :
	QString m_strRoomId;
	QString m_strRoomName;
	QString m_strAnchorId;
	QString m_strAnchorName;

	QVector<StreamPtr> m_vStreamList;

	unsigned int m_uCreatedTime;
	unsigned int m_uLivesCount;
};

using RoomPtr = QSharedPointer < QZegoRoomModel > ;