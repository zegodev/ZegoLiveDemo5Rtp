#pragma execution_character_set("utf-8")

#ifndef ZEGOPUBLISH2STREAMDIALOG_H
#define ZEGOPUBLISH2STREAMDIALOG_H

#include "Base/ZegoBaseDialog.h"

class ZegoPublish2StreamDialog : public ZegoBaseDialog
{
	Q_OBJECT

public:
	ZegoPublish2StreamDialog(QWidget *parent = 0);
	ZegoPublish2StreamDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent = 0);
	~ZegoPublish2StreamDialog();
	void initDialog();

protected slots:
	void OnLoginRoom(int errorCode, const QString& roomId, QVector<StreamPtr> vStreamList);
	void OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	void OnPlayStateUpdate(int stateCode, const QString& streamId);
	void OnJoinLiveRequest(int seq, const QString& fromUserId, const QString& fromUserName, const QString& roomId);


private slots:
    void OnButtonSwitchPublish();

private:
	void StartPublishStream();
	void StartPublishStream_Aux();
	void StopPublishStream(const QString& streamID, AV::PublishChannelIndex idx = ZEGO::AV::PUBLISH_CHN_MAIN);
	void StartPlayStream(StreamPtr stream);
	void StopPlayStream(const QString& streamID);
	bool praseJsonData(QJsonDocument doc);
	void GetOut();
	void initCameraListView2();   //继承父类接口
	void setWaterPrint(AV::PublishChannelIndex idx);

private:
	QString m_strPublishStreamID;
	QString m_strPublishStreamID_Aux;

	bool m_bIsPublishing = false;

	QListView *m_cbCameraListView2;
	StreamPtr m_anchorStreamInfo_Aux;
};

#endif
