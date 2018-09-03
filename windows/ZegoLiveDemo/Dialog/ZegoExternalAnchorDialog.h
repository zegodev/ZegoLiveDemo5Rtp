#pragma execution_character_set("utf-8")

#ifndef ZegoExternalAnchorDialog_H
#define ZegoExternalAnchorDialog_H

#include "Base/ZegoBaseDialog.h"
#include "External_Input/ZegoInputManager.h"
class ZegoExternalAnchorDialog : public ZegoBaseDialog
{
	Q_OBJECT

public:
	ZegoExternalAnchorDialog(QWidget *parent = 0);
	ZegoExternalAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent = 0);
	~ZegoExternalAnchorDialog();
	void initDialog();

protected slots:
	void OnLoginRoom(int errorCode, const QString& roomId, QVector<StreamPtr> vStreamList);
	void OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo);
	void OnPublishQualityUpdate(const QString& streamId, int quality, double capFPS, double videoFPS, double videoKBS, double audioKBS, int rtt, int pktLostRate);

protected slots:
	void OnDeviceAdded(int device_type, QString device_name);
	void OnDeviceDeleted(int device_type, int index);

private slots:
    void OnButtonSwitchPublish();
	void OnTimerRefreshView();
	//切换音视频设备
	void OnSwitchAudioDevice_External(int id);
	void OnSwitchVideoDevice_External(int id);

private:
	void StartPublishStream();
	void StopPublishStream(const QString& streamID);

	bool praseJsonData(QJsonDocument doc);
	void GetOut();

	void addAVView(int addViewIndex, ZegoDialogType dialogType);
	void removeAVView(int removeViewIndex);
private:
	
	QString m_strPublishStreamID;
	bool m_bIsPublishing = false;

	//外部渲染定时器
	QTimer *m_render_timer = nullptr;
	//外部采集控制器
	ZegoInputManager *m_input = nullptr;
};

#endif
