#include "Model/ZegoRoomModel.h"

QZegoRoomModel::QZegoRoomModel(QString &roomId, QString &roomName, QString &anchorId, QString &anchorName)
	: m_strRoomId(roomId), m_strRoomName(roomName), m_strAnchorId(anchorId), m_strAnchorName(anchorName)
{

}

QZegoRoomModel::~QZegoRoomModel(void)
{
	m_vStreamList.clear();
}

void QZegoRoomModel::setRoomId(const QString &roomId)
{
	m_strRoomId = roomId;
}

QString QZegoRoomModel::getRoomId(void)
{
	return m_strRoomId;
}

void QZegoRoomModel::setRoomName(const QString &roomName)
{
	m_strRoomName = roomName;
}

QString QZegoRoomModel::getRoomName(void)
{
	return m_strRoomName;
}

void QZegoRoomModel::setAnchorId(const QString &anchorId)
{
	m_strAnchorId = anchorId;
}

QString QZegoRoomModel::getAnchorId(void)
{
	return m_strAnchorId;
}

void QZegoRoomModel::setAnchorName(const QString &anchorName)
{
	m_strAnchorName = anchorName;
}

QString QZegoRoomModel::getAnchorName(void)
{
	return m_strAnchorName;
}

void QZegoRoomModel::setCreatedTime(unsigned int time)
{
	m_uCreatedTime = time;
}

unsigned int QZegoRoomModel::getCreatedTime(void)
{
	return m_uCreatedTime;
}

void QZegoRoomModel::setLivesCount(unsigned int count)
{
	m_uLivesCount = count;
}

unsigned int QZegoRoomModel::getLivesCount(void)
{
	return m_uLivesCount;
}

void QZegoRoomModel::addStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	QString strStreamID = stream->getStreamId();

	for (auto iter : m_vStreamList)
	{
		if (iter->getStreamId() == strStreamID)
			return;
	}

	m_vStreamList.push_back(stream);
}

StreamPtr QZegoRoomModel::removeStream(const QString& streamId)
{
	StreamPtr pStream(nullptr);

	for (int i = 0; i < m_vStreamList.size(); ++i)
	{
		if (m_vStreamList.at(i)->getStreamId() == streamId)
		{
			pStream = m_vStreamList.takeAt(i);
			break;
		}

	}

	return pStream;
}

QVector<StreamPtr> QZegoRoomModel::getStreamList()
{
	return m_vStreamList;
}

int QZegoRoomModel::getStreamCount(void)
{
	return m_vStreamList.size();
}

StreamPtr QZegoRoomModel::getStreamById(const QString &streamId)
{
	
	for (int i = 0; i < m_vStreamList.size(); ++i)
	{
		
		if (m_vStreamList[i]->getStreamId() == streamId)
		{
			return m_vStreamList[i];
		}

	}

	return StreamPtr();

}
