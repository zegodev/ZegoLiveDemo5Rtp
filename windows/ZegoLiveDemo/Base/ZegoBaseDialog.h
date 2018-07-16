#pragma execution_character_set("utf-8")

#ifndef ZEGOBASEDIALOG_H
#define ZEGOBASEDIALOG_H

#include <QtWidgets/QDialog>
#include <QStack>
#include <QVector>
#include <QLayout>
#include <QStringListModel>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QJsonDocument>
#include <QVariantMap>
#include <QJsonObject>
#include <QFileDialog>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#ifdef Q_OS_WIN
Q_GUI_EXPORT QPixmap qt_pixmapFromWinHBITMAP(HBITMAP bitmap, int hbitmapFormat);
#endif
#include "ui_ZegoLiveRoomDialog.h"
#include "ZegoLiveDemo.h"
#include "ZegoAVView.h"
#include "ZegoRoomMessageLabel.h"

#include "Settings/ZegoSettingsModel.h"
#include "Model/ZegoRoomModel.h"
#include "Model/ZegoRoomMsgModel.h"
#include "Delegate/NoFocusFrameDelegate.h"
#include "Dialog/ZegoShareDialog.h"
#include "Dialog/ZegoImageShowDialog.h"
#include "Device/ZegoDeviceManager.h"
#include "Base/IncludeZegoLiveRoomApi.h"
#include "Base/ZegoLiveDemoDefines.h"
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32)
#include "ZegoMusicHookDialog.h"
#include "ZegoAudioHook.h"
#endif
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
#include "Module/ZegoSurfaceMergeApi.h"
#endif

class ZegoBaseDialog : public QDialog
{
	Q_OBJECT

public:
	ZegoBaseDialog(QWidget *parent = 0);
	ZegoBaseDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, bool isPublish2Stream, bool isPublisher, QDialog *parent = 0);
	~ZegoBaseDialog();
	void initDialog();

protected slots:
	void OnUserUpdate(QVector<QString> userIDs, QVector<QString> userNames, QVector<int> userFlags, QVector<int> userRoles, unsigned int userCount, LIVEROOM::ZegoUserUpdateType type);
	void OnDisconnect(int errorCode, const QString& roomId);
	void OnKickOut(int reason, const QString& roomId);
	void OnPlayQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS);
	void OnPublishQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS);
	void OnAVAuxInput(unsigned char *pData, int* pDataLen, int pDataLenValue, int *pSampleRate, int *pNumChannels);
	void OnSendRoomMessage(int errorCode, const QString& roomID, int sendSeq, unsigned long long messageId);
	void OnRecvRoomMessage(const QString& roomId, QVector<RoomMsgPtr> vRoomMsgList);
	
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
	void OnSurfaceMergeResult(unsigned char *surfaceMergeData, int datalength);
#endif
	void OnPreviewSnapshot(void *pImage);
	void OnSnapshot(void *pImage, const QString &streamID);

protected:
	virtual void mousePressEvent(QMouseEvent *event);  
	virtual void mouseMoveEvent(QMouseEvent *event);  
	virtual void mouseReleaseEvent(QMouseEvent *event);  
	virtual void mouseDoubleClickEvent(QMouseEvent *event);  
	virtual void showEvent(QShowEvent *event);
	virtual void closeEvent(QCloseEvent *e);  
	virtual bool eventFilter(QObject *target, QEvent *event);  

signals:
	//当直播窗口关闭时，将更改的视频设置传回给MainDialog（如，更换了摄像头、麦克风）
	void sigSaveVideoSettings(SettingsPtr settings);
	void sigShowSnapShotImage(QImage *imageData);

public slots:
	void OnClickTitleButton();  
	void OnClose();  
	void OnButtonSendMessage();  
	void OnButtonSoundCapture();  
	void OnButtonMircoPhone(); 
	void OnButtonSound();  
	void OnButtonCamera();
	void OnProgChange();  
	void OnShareLink();  
	void OnButtonAux();  
	void OnSnapshotPreview();
	void OnSnapshotWithStreamID(const QString &streamID);
	//混音app地址回调
	void OnUseDefaultAux(bool state);
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32)
	void OnGetMusicAppPath(QString exePath);
#endif
	//切换音视频设备
	void OnSwitchAudioDevice(int id);  
	void OnSwitchVideoDevice(int id);  
	void OnSwitchVideoDevice2(int id); 
	//全屏显示
	void OnButtonShowFullScreen();  

	void OnShowSnapShotImage(QImage *imageData);

public slots:
	void OnDeviceAdded(int device_type, QString device_name);
	void OnDeviceDeleted(int device_type, int index);

protected:
	void insertStringListModelItem(QStringListModel * model, QString name, int size); 
	void removeStringListModelItem(QStringListModel * model, QString name);
	void removeStringListModelItemByIndex(QStringListModel * model, int index);
	//void EnumVideoAndAudioDevice();  
	void GetDeviceList();
	void initComboBox(); 
	void initButtonIcon();
	virtual void initCameraListView2(){}
	void FreeAVView(StreamPtr stream);  
	virtual void GetOut();  
	void BeginAux();  
	void EndAux();  
	QString encodeStringAddingEscape(QString str);  
	void SetOperation(bool state);  
	//成员列表增删函数
	void roomMemberAdd(QString userName);  
	void roomMemberDelete(QString userName);  
	//view布局函数
	int takeLeastAvaliableViewIndex();  
	void initAVView(QZegoAVView *view);  
	void addAVView(int addViewIndex, ZegoDialogType dialogType);
	void removeAVView(int removeViewIndex);  
	void updateViewLayout(int viewCount);
	void setWaterPrint();  
	int getCameraIndexFromID(const QString& cameraID);  

protected:
	Ui::ZegoLiveRoomDialog ui;
	
	QString m_strCurUserID;
	QString m_strCurUserName;
	QVector<unsigned int> m_avaliableView;
	bool m_bCKEnableMic;
	bool m_bCKEnableSpeaker;
	SettingsPtr m_pAVSettings;
	RoomPtr m_pChatRoom;
	//混音参数
	unsigned char* m_pAuxData;
	int m_nAuxDataLen;
	int m_nAuxDataPos;

	bool m_bSystemCapture = false;
	bool isMax = false;
	bool isUseDefaultAux = false;
	bool m_isLiveFullScreen = false;
	bool m_takeSnapShot = false;
	bool m_isPublish2StreamMode = false;
	bool m_isPublisher;
	bool m_isUseVerticalCapture;

	QVector<QDeviceInfo> m_vecAudioDevice;
	QVector<QDeviceInfo> m_vecVideoDevice;

	QVector<QZegoAVView *> AVViews;

	QString m_strLastSendMsg;

	//List
	QStringList m_MircoPhoneList;
	QStringList m_CameraList;

	//自定义的ComboBox下拉式页面
	QListView *m_cbMircoPhoneListView;
	QListView *m_cbCameraListView;

	//Model
	QStringListModel *m_cbMircoPhoneModel;
	QStringListModel *m_cbCameraModel;
	QStandardItemModel *m_chatModel;
	QStringListModel *m_memberModel;

	//实现自定义标题栏的拖动
	bool isMousePressed;
	QPoint mousePosition;

	//实时监控麦克风音量大小
	QTimer *timer;

	//保存上一个界面的指针，用于退出该页面时显示它
	QDialog *m_lastDialog;

	//分享链接
	QString sharedHlsUrl;
	QString sharedRtmpUrl;

	//保留当前第一主播的流信息
	StreamPtr m_anchorStreamInfo;
	StreamPtr m_anchorStreamInfo_Aux;
	//view的网格动态布局
	QGridLayout *gridLayout;

	//设备管理
	ZegoDeviceManager *m_device = nullptr;
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32)
	ZegoMusicHookDialog hookDialog;
#endif

	//保存截图数据
	unsigned char* m_image = nullptr;

	QMutex m_mutex;
	
};

#endif
