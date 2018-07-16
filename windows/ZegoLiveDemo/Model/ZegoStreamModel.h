#pragma once

#include <QObject>
#include <QVector>

class QZegoStreamModel
{
public :
	QZegoStreamModel(const QString &streamId, const QString &userId, const QString &userName, const QString &extraInfo, bool isCurUser = false, bool isCurUserAux = false);
	QZegoStreamModel(const QZegoStreamModel &otherStream);

public : 
	//获取相关信息
	QString getStreamId(void);
	QString getUserId(void);
	QString getUserName(void);
	QString getExtraInfo(void);
	void setPlayView(int viewId);
	int getPlayView(void);
	bool isPlaying(void);

	bool isCurUserCreated(void);
	bool isCurUserCreated_Aux(void);

	QVector<QString> m_vecRtmpUrls;
	QVector<QString> m_vecFlvUrls;
	QVector<QString> m_vecHlsUrls;

	void setStreamID(const QString &streamID);
private :
	QString m_strStreamId;
	QString m_strUserId;
	QString m_strUserName;
	QString m_strExtraInfo;

	int m_nPlayViewId;
	bool m_bCurUserCreated;
	bool m_bCurUserCreated_Aux;
	bool m_bPrimary;
};

using StreamPtr = QSharedPointer < QZegoStreamModel > ;