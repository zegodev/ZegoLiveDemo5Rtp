#pragma execution_character_set("utf-8")

#ifndef ZEGOMIXSTREAMANCHORDIALOG_H
#define ZEGOMIXSTREAMANCHORDIALOG_H

#include "Base/ZegoBaseDialog.h"
#define m_MixStreamID "mixStreamID"

class ZegoMixStreamAnchorDialog : public ZegoBaseDialog
{
	Q_OBJECT

public:
	ZegoMixStreamAnchorDialog(QWidget *parent = 0);
	ZegoMixStreamAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent = 0);
	~ZegoMixStreamAnchorDialog();
	void initDialog();

protected slots:
	void OnLoginRoom(int errorCode, const QString& roomId, QVector<StreamPtr> vStreamList);
	void OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	void OnPlayStateUpdate(int stateCode, const QString& streamId);
	void OnJoinLiveRequest(int seq, const QString& fromUserId, const QString& fromUserName, const QString& roomId);
	void OnMixStream(unsigned int errorCode, const QString& hlsUrl, const QString& rtmpUrl, const QString& mixStreamID, int seq);
	void OnKickOut(int reason, const QString& roomId);
private slots:
	void OnButtonSwitchPublish();

private:
	void StartPublishStream();
	void StopPublishStream(const QString& streamID);
	void StartPlayStream(StreamPtr stream);
	void StopPlayStream(const QString& streamID);
	void GetOut();

	//混流需要调用的函数
	void StartMixStream();
	void StopMixStream();
	void MixStreamAdd(QVector<StreamPtr> vStreamList, const QString& roomId);
	void MixStreamDelete(QVector<StreamPtr> vStreamList, const QString& roomId);
	bool isStreamExisted(QString streamID);
	
private:
	
	bool m_bIsPublishing = false;
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
