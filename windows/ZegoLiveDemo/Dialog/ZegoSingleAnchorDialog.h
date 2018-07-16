#pragma execution_character_set("utf-8")

#ifndef ZEGOSINGLEANCHORDIALOG_H
#define ZEGOSINGLEANCHORDIALOG_H

#include "Base/ZegoBaseDialog.h"

class ZegoSingleAnchorDialog : public ZegoBaseDialog
{
	Q_OBJECT

public:
	ZegoSingleAnchorDialog(QWidget *parent = 0);
	ZegoSingleAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent = 0);
	~ZegoSingleAnchorDialog();
	void initDialog();

protected slots:
	void OnLoginRoom(int errorCode, const QString& roomId, QVector<StreamPtr> vStreamList);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	
private slots:
	//对于主播来说，没有请求连麦按钮，换成开始/停止直播按钮
	void OnButtonSwitchPublish();

private:
	void StartPublishStream();
	void StopPublishStream(const QString& streamID);
	void GetOut();
	
private:
	bool m_bIsPublishing = false;
	QString m_strPublishStreamID;
	QString m_strPublishStreamID_Aux;
};

#endif
