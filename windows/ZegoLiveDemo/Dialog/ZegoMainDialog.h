#pragma execution_character_set("utf-8")

#ifndef ZEGOMAINDIALOG_H
#define ZEGOMAINDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_ZegoMainDialog.h"
#include "Model/ZegoRoomModel.h"
#include "Config/ZegoUserConfig.h"
#include "ZegoLiveDemo.h"
#include "Base/ZegoBase.h"
#include "Base/ZegoLiveDemoDefines.h"
#include "ZegoEnterRoomButton.h"
#include "Device/ZegoDeviceManager.h"
#include "FramelessHelper.h"
#include <QtNetwork/qnetworkaccessmanager.h> 
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>
#include <QFile>
#include <QUrl>
#include <QJsonParseError>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>
#include <QDesktopServices>
#include <QListWidget>
#include <QStringListModel>
#include <QStandardItemModel>
//虚拟立体声和混响接口
#include "zego-api-audio-processing.h"

typedef enum _LiveMode
{
	MODE_SINGLE_ANCHOR = 0,
	MODE_JOIN_PUBLISH,
	MODE_MIX_STREAM,
	MODE_PUBLISH_2_STREAM
}LiveMode;

class ZegoMainDialog : public QDialog
{
	Q_OBJECT

public:
	ZegoMainDialog(QWidget *parent = 0);
	~ZegoMainDialog();
	void initDialog();

protected slots:
    void OnInitSDK(int nError);

private slots:
	void OnButtonModeSheetChange(int id);
	void OnButtonQualityChange(int id);
	void OnSliderValueChange(int value);
	void OnButtonSliderValueChange();
	void OnButtonEnterRoom();
	void OnClickTitleButton();
	void OnSaveUserIdChanged();
	void OnSaveUserNameChanged();
	void OnSaveAppIdChanged();
	void OnSaveAppSignChanged();
	void OnCheckSliderPressed();
	void OnCheckSliderReleased();

	void writeJsonData(QNetworkReply *reply);
	//切换音视频设备
	void OnSwitchAudioDevice(int id);
	void OnSwitchVideoDevice(int id);
	void OnSwitchVideoDevice2(int id);
	void OnSaveVideoSettings(SettingsPtr settings);
	void OnDeviceAdded(int device_type, QString device_name);
	void OnDeviceDeleted(int device_type, int index);

	void OnComboBoxAppVersionChanged(int id);
	void OnComboBoxCameraRotation(int id);


private slots:
	void on_m_bCreateRoom_clicked();
	void on_m_bRefreshRoomList_clicked();
	void on_m_switchTestEnv_clicked();
	void on_m_switchCapture_clicked();
	void on_m_switchFilter_clicked();
	void on_m_switchSurfaceMerge_clicked();
	void on_m_switchReverb_clicked();
	void on_m_switchVirtualStereo_clicked();
	void on_m_switchVerticalCapture_clicked();
	void on_m_bUploadLog_clicked();

protected:
	virtual bool eventFilter(QObject *target, QEvent *event);

private:
	void GetDeviceList(SettingsPtr curSettings);
	void setDefalutVideoQuality(SettingsPtr curSettings);
	void PullRoomList();
	void ParseRoomList(QByteArray json);
	void RefreshRoomList(QVector<RoomPtr> roomList);
	void addModeButtonGroup();
	void addQualityButtonGroup();
	void initComboBox();
	void initButtonIcon();
	void insertStringListModelItem(QStringListModel * model, QString name, int size);
	void removeStringListModelItem(QStringListModel * model, QString name);
	void removeStringListModelItemByIndex(QStringListModel * model, int index);
	void banSwitch();    //禁用未实现功能的按钮
	QVector<QString> handleAppSign(QString appSign);
	int getCameraIndexFromID(const QString& cameraID);

private:
	Ui::ZegoMainDialog ui;
	QVector<RoomPtr> m_roomList;

	//用于接收服务器房间数据的网络请求
	QNetworkAccessManager *m_networkManager;
	QByteArray json;

	//直播属性为UDP,RTMP,国际版或自定义（0,1,2,3）
	int m_versionMode;

	//User
	QString m_strEdUserId;
	QString m_strEdUserName;

	//ButtonGroup
	QButtonGroup *m_modeButtonGroup;
	QButtonGroup *m_qualityButtonGroup;

	//VideoQuality
	QVector<QString> m_vecResolution;
	QVector<QString> m_vecBitrate;
	QVector<QString> m_vecFPS;

	//Devices
	QVector<QDeviceInfo> m_vecAudioDevice;
	QVector<QDeviceInfo> m_vecVideoDevice;
	ZegoDeviceManager *m_device;

	//Model
	QStringListModel *m_cbMircoPhoneModel;
	QStringListModel *m_cbCameraModel;
	QStandardItemModel *m_roomListModel;

	//List
	QStringList m_MircoPhoneList;
	QStringList m_CameraList;

	//自定义的ComboBox下拉式页面
	QListView *m_cbMircoPhoneListView;
	QListView *m_cbCameraListView;
	QListView *m_cbCameraListView2;
	//实现自定义标题栏的拖动
	FramelessHelper *m_pHelper = nullptr;

	//当前视频质量是否自定义
	bool isVideoCustom;
	//检查当前slider是否pressed
	bool m_sliderPressed = false;
	//是否使用测试环境，默认不使用
	bool m_isUseTestEnv = false;
	//是否使用外部采集，默认不使用
	bool m_isUseVideoCapture = false;
	//是否使用外部滤镜，默认不使用
	bool m_isUseVideoFilter = false;
	//是否使用截屏推流，默认不使用
	bool m_isUseSurfaceMerge = false;
	//是否使用推两路流，默认不使用
	bool m_isUsePublish2Stream = false;
	//判断是否已经初始化dialog
	bool m_initedDialog = false;
};

#endif // ZEGOMAINDIALOG_H
