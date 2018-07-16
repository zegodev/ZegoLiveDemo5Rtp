#pragma execution_character_set("utf-8")

#ifndef ZEGOMIXSTREAMAUDIENCEDIALOG_H
#define ZEGOMIXSTREAMAUDIENCEDIALOG_H

#include "Base/ZegoBaseDialog.h"

#define m_MixStreamID "mixStreamID"


class ZegoMixStreamAudienceDialog : public ZegoBaseDialog
{
	Q_OBJECT

public:
	ZegoMixStreamAudienceDialog(QWidget *parent = 0);
	ZegoMixStreamAudienceDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent = 0);
	~ZegoMixStreamAudienceDialog();
	void initDialog();

protected slots:
	void OnLoginRoom(int errorCode, const QString& roomId, QVector<StreamPtr> vStreamList);
	void OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	void OnPlayStateUpdate(int stateCode, const QString& streamId);
	void OnJoinLiveResponse(int result, const QString& fromUserId, const QString& fromUserName, int seq);
	void OnMixStream(unsigned int errorCode, const QString& hlsUrl, const QString& rtmpUrl, const QString& mixStreamID, int seq);
	void OnRecvEndJoinLiveCommand(const QString& userId, const QString& userName, const QString& roomId);
	void OnStreamExtraInfoUpdated(const QString& roomId, QVector<StreamPtr> vStreamList);

private slots:
	void OnButtonJoinLive();

private:
	void StartPublishStream();
	void StopPublishStream(const QString& streamID);
	void StartPlayStream(StreamPtr stream);
	void StopPlayStream(const QString& streamID);
	void GetOut();
	//混流需要调用的函数
	void StartMixStream();
	void MixStreamAdd(QVector<StreamPtr> vStreamList, const QString& roomId);
	void MixStreamDelete(QVector<StreamPtr> vStreamList, const QString& roomId);
	bool praseMixJsonData(QJsonDocument doc);
	void StartPlayMixStream(StreamPtr streamInfo);
	void StopPlayMixStream(QVector<StreamPtr> vStreamList);
	bool isStreamExisted(QString streamID);
	void StartPlaySingleStream(QVector<StreamPtr> streamList);
	void StopPlaySingleStream();

private:
	bool m_bIsJoinLive = false;
	int m_iRequestJoinLiveSeq = -1;
	QString m_strPublishStreamID;

	//保存混流画布信息的数组
	QVector<ZEGO::AV::ZegoMixStreamConfig *> m_mixStreamInfos;

	//混流模式下用于保存流StreamPtr的数组
	QVector<StreamPtr> m_mixStreamList;

	//混流回调序号
	int m_mixStreamRequestSeq;

	//推流时的混流ID
	QString m_myMixStreamID;
	//拉流时第一主播的混流ID
	QString m_anchorMixStreamID;

	//保存拉混流的ExtraInfo信息
	//QString sharedHlsUrl;
	//QString sharedRtmpUrl;

};

#endif
