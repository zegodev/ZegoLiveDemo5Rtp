#include "Dialog/ZegoMainDialog.h"
#include "ZegoSingleAnchorDialog.h"
#include "ZegoSingleAudienceDialog.h"
#include "ZegoMoreAnchorDialog.h"
#include "ZegoMoreAudienceDialog.h"
#include "ZegoMixStreamAnchorDialog.h"
#include "ZegoMixStreamAudienceDialog.h"
#include "ZegoPublish2StreamDialog.h"
#include "ZegoExternalAnchorDialog.h"
#include "Delegate/NoFocusFrameDelegate.h"
#include "ZegoProgressIndicator.h"
#include <QScrollBar>
#include <QStyledItemDelegate>

#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoViewZoom.h"
#endif

#define mConfig theApp.GetConfig()
#define mBase theApp.GetBase()

static QString rotation_list[] = {"camera_orientation_mode=0", "camera_orientation_mode=90", "camera_orientation_mode=180", "camera_orientation_mode=270"};

ZegoMainDialog::ZegoMainDialog(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	
	connect(ui.m_bMin, &QPushButton::clicked, this, &ZegoMainDialog::OnClickTitleButton);
	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoMainDialog::OnClickTitleButton);
	connect(ui.m_bJumpToNet, &QPushButton::clicked, this, &ZegoMainDialog::OnClickTitleButton);

	connect(ui.m_bResolutionDown, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);
	connect(ui.m_bResolutionUp, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);
	connect(ui.m_bBitrateDown, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);
	connect(ui.m_bBitrateUp, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);
	connect(ui.m_bFPSDown, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);
	connect(ui.m_bFPSUp, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonSliderValueChange);

	connect(ui.m_strEdUserId, &QLineEdit::editingFinished, this, &ZegoMainDialog::OnSaveUserIdChanged);
	connect(ui.m_strEdUserName, &QLineEdit::editingFinished, this, &ZegoMainDialog::OnSaveUserNameChanged);
	connect(ui.m_strEdAPPID, &QLineEdit::editingFinished, this, &ZegoMainDialog::OnSaveAppIdChanged);
	connect(ui.m_strEdAPPSign, &QLineEdit::editingFinished, this, &ZegoMainDialog::OnSaveAppSignChanged);

	//InitSDK成功回调
	connect(GetAVSignal(), &QZegoAVSignal::sigInitSDK, this, &ZegoMainDialog::OnInitSDK);
	//设备变更（增删）
	//connect(GetAVSignal(), &QZegoAVSignal::sigAudioDeviceChanged, this, &ZegoMainDialog::OnAudioDeviceChanged);
	//connect(GetAVSignal(), &QZegoAVSignal::sigVideoDeviceChanged, this, &ZegoMainDialog::OnVideoDeviceChanged);
	//设备变更（改变）
	//connect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	//connect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	//connect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));
	//app版本变更
	connect(ui.m_cbAppVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(OnComboBoxAppVersionChanged(int)));
	//摄像头旋转
	connect(ui.m_cbRotation, SIGNAL(currentIndexChanged(int)), this, SLOT(OnComboBoxCameraRotation(int)));
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);//去掉标题栏 
	
	m_pHelper = new FramelessHelper(this);
	m_pHelper->activateOn(this);
	m_pHelper->setTitleHeight(40);
	m_pHelper->setWidgetMovable(true); //无边框拖动

	m_device = new ZegoDeviceManager;
	connect(m_device, &ZegoDeviceManager::sigDeviceAdded, this, &ZegoMainDialog::OnDeviceAdded);
	connect(m_device, &ZegoDeviceManager::sigDeviceDeleted, this, &ZegoMainDialog::OnDeviceDeleted);

	ui.m_edRoomName->installEventFilter(this);
	ui.m_strEdUserId->installEventFilter(this);
	ui.m_strEdUserName->installEventFilter(this);
	ui.m_strEdAPPID->installEventFilter(this);
	ui.m_strEdAPPSign->installEventFilter(this);
	this->installEventFilter(this);
}

ZegoMainDialog::~ZegoMainDialog()
{
	//释放堆内存
	delete m_modeButtonGroup;
	delete m_qualityButtonGroup;
	delete m_cbMircoPhoneModel;
	delete m_cbCameraModel;
	delete m_roomListModel;
	delete m_cbMircoPhoneListView;
	delete m_cbCameraListView;

	delete m_pHelper;
	m_pHelper = nullptr;

	delete m_device;
	m_device = nullptr;

	m_roomList.clear();
	mBase.UninitAVSDK();
	
}

//part1:功能函数
void ZegoMainDialog::initDialog()
{
#if (defined Q_OS_MAC) || (!defined USE_SURFACE_MERGE) || (!defined Q_PROCESSOR_X86_32)
	ui.m_switchSurfaceMerge->setEnabled(false);
#endif

	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	//初始化房间列表
	m_roomListModel = new QStandardItemModel(this);
	m_roomListModel->setColumnCount(4);
	//表头内容
	m_roomListModel->setHeaderData(0, Qt::Horizontal, tr("房间名"));
	m_roomListModel->setHeaderData(1, Qt::Horizontal, tr("直播模式"));
	m_roomListModel->setHeaderData(2, Qt::Horizontal, tr("连麦人数"));
	m_roomListModel->setHeaderData(3, Qt::Horizontal, tr("进入"));
	ui.m_roomList->setModel(m_roomListModel);
	ui.m_roomList->initRoomList();

	//禁用某些高级功能的按钮
	banSwitch();

	initButtonIcon();
	//初始化ComboBox
	initComboBox();
	//将四个模式按钮加入组中
	addModeButtonGroup();
	//将六个视频质量按钮加入组中
	addQualityButtonGroup();

	//从用户配置文件中读取配置信息，若找不到则新建配置文件
	mConfig.LoadConfig();

	m_strEdUserId = mConfig.GetUserId();
	m_strEdUserName = mConfig.getUserName();

	ui.m_strEdUserId->setText(m_strEdUserId);
	ui.m_strEdUserName->setText(m_strEdUserName);

	//显示用户配置的视频质量
	QPushButton * pButton = (QPushButton *)m_qualityButtonGroup->button(mConfig.GetVideoQuality());
	pButton->setChecked(true);
	if (pButton == ui.m_bCustom)
		isVideoCustom = true;
	else
		isVideoCustom = false;

	if (mConfig.GetUseTestEnv())
	{
		ui.m_switchTestEnv->setChecked(true);
		mBase.setTestEnv(true);
	}

	//初始化app版本的ComboBox
	ui.m_cbAppVersion->blockSignals(true);
	ui.m_cbAppVersion->addItem(tr("国内版"));
	ui.m_cbAppVersion->addItem(tr("国际版"));
	//ui.m_cbAppVersion->addItem(tr("娃娃机"));
	ui.m_cbAppVersion->addItem(tr("自定义"));
	ui.m_cbAppVersion->blockSignals(false);

	//初始化摄像头旋转的ComboBox
	ui.m_cbRotation->blockSignals(true);
	ui.m_cbRotation->addItem(tr("0度"));
	ui.m_cbRotation->addItem(tr("90度"));
	ui.m_cbRotation->addItem(tr("180度"));
	ui.m_cbRotation->addItem(tr("270度"));
	ui.m_cbRotation->blockSignals(false);
	
	bool isVerticalCapture = mConfig.GetUseVerticalCapture();
	if (isVerticalCapture)
		ui.m_switchVerticalCapture->setChecked(true);

	m_versionMode = mConfig.GetAppVersion();
	//当Index = 0 时不会触发信号
	ui.m_cbAppVersion->setCurrentIndex(m_versionMode);
	if (m_versionMode == ZEGO_PROTOCOL_UDP)
	{
		ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppID()));
		ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
		ui.m_strEdAPPID->setEnabled(false);
		ui.m_strEdAPPSign->setEnabled(false);
	}

	mBase.setKey(m_versionMode);

	SettingsPtr pCurSettings = mConfig.GetVideoSettings();

	if (pCurSettings != nullptr)
	{
		setDefalutVideoQuality(pCurSettings);
		//EnumVideoAndAudioDevice(pCurSettings);
		GetDeviceList(pCurSettings);
		QString userID = mConfig.GetUserId();
		QString userName = mConfig.getUserName();
		mBase.InitAVSDK(userID, userName);

		//是否使用截屏推流,默认不使用
		pCurSettings->SetSurfaceMerge(m_isUseSurfaceMerge);

		mConfig.SetVideoSettings(pCurSettings);
	}
	//app版本
	ui.m_lbTitle->setText(tr("ZegoLiveDemo(%1)").arg(ui.m_cbAppVersion->currentText()));
	//sdk版本号
	ui.m_lbTitleVersion->setText(tr("版本: %1").arg(QString(QLatin1String(LIVEROOM::GetSDKVersion()))));
	//pull房间列表
	PullRoomList();

	m_initedDialog = true;
}

void ZegoMainDialog::GetDeviceList(SettingsPtr curSettings)
{
	//获取音频设备
	m_device->EnumAudioDeviceList();
	//获取视频设备
	m_device->EnumVideoDeviceList();

	m_vecAudioDevice = m_device->GetAudioDeviceList();
	m_vecVideoDevice = m_device->GetVideoDeviceList();

	for (int i = 0; i < m_vecAudioDevice.size(); i++)
	{
		insertStringListModelItem(m_cbMircoPhoneModel, m_vecAudioDevice.at(i).deviceName, m_cbMircoPhoneModel->rowCount());
	}

	for (int j = 0; j < m_vecVideoDevice.size(); j++)
	{
		insertStringListModelItem(m_cbCameraModel, m_vecVideoDevice.at(j).deviceName, m_cbCameraModel->rowCount());
	}

	int mic_index = m_device->GetAudioDeviceIndex();
	int camera_index = m_device->GetVideoDeviceIndex();
	int camera_2_index = m_device->GetVideoDevice2Index();

	if(mic_index >= 0)
	    ui.m_cbMircoPhone->setCurrentIndex(m_device->GetAudioDeviceIndex());
	if(camera_index >= 0)
	    ui.m_cbCamera->setCurrentIndex(m_device->GetVideoDeviceIndex());
	if (camera_2_index >= 0)
	{
		ui.m_cbCamera2->setCurrentIndex(m_device->GetVideoDevice2Index());
	}
	else
	{
		//先将第二个camera model用一个空的model绑定，此时就算推了第二路流也会没有图像
		ui.m_cbCamera2->setModel(new QStringListModel());
	}

	//设备变更（改变）
	connect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	connect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	connect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));

	curSettings->SetMicrophoneId(m_device->GetAudioDeviceId());
	curSettings->SetCameraId(m_device->GetVideoDeviceId());
	curSettings->SetCameraId2(m_device->GetVideoDeviceId2());

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
}

void ZegoMainDialog::setDefalutVideoQuality(SettingsPtr curSettings)
{
	
	Size defResolution = curSettings->GetResolution();

	for (int i = 0; i < sizeof(g_Resolution) / sizeof(g_Resolution[0]); ++i)
	{
		QString strResolution;
		strResolution = QString("%1×%2").arg(g_Resolution[i].cx).arg(g_Resolution[i].cy);
		m_vecResolution.push_back(strResolution);

		if (defResolution.cx == g_Resolution[i].cx && defResolution.cy == g_Resolution[i].cy)
		{
			//为了vec的索引值与slider的数组对应，采取反序
			ui.m_sliderResolution->setValue(g_Resolution_length - i);
			ui.m_lbValueResolution->setText(strResolution);
		}
	}

	connect(ui.m_sliderResolution, SIGNAL(valueChanged(int)), this, SLOT(OnSliderValueChange(int)));
	connect(ui.m_sliderResolution, &QSlider::sliderPressed, this, &ZegoMainDialog::OnCheckSliderPressed);
	connect(ui.m_sliderResolution, &QSlider::sliderReleased, this, &ZegoMainDialog::OnCheckSliderReleased);

	int defBitrate = curSettings->GetBitrate();

	for (int i = 0; i < sizeof(g_Bitrate) / sizeof(g_Bitrate[0]); ++i)
	{
		QString strBitrate;
		int m = g_Bitrate[i] / (1000 * 1000);
		strBitrate = QString("%1k").arg(g_Bitrate[i] / 1000);
		m_vecBitrate.push_back(strBitrate);

		if (defBitrate == g_Bitrate[i])
		{
			ui.m_sliderBitrate->setValue(g_Bitrate_length - i);
			ui.m_lbValueBitrate->setText(strBitrate);
		}
	}

	connect(ui.m_sliderBitrate, SIGNAL(valueChanged(int)), this, SLOT(OnSliderValueChange(int)));
	connect(ui.m_sliderBitrate, &QSlider::sliderPressed, this, &ZegoMainDialog::OnCheckSliderPressed);
	connect(ui.m_sliderBitrate, &QSlider::sliderReleased, this, &ZegoMainDialog::OnCheckSliderReleased);

	int defFPS = curSettings->GetFps();

	for (int i = 0; i < sizeof(g_Fps) / sizeof(g_Fps[0]); ++i)
	{
		QString strFPS;
		strFPS = QString("%1").arg(g_Fps[i]);
		m_vecFPS.push_back(strFPS);

		if (defFPS == g_Fps[i])
		{
			ui.m_sliderFPS->setValue(g_FPS_length - i);
			ui.m_lbValueFPS->setText(strFPS);
		}
	}

	connect(ui.m_sliderFPS, SIGNAL(valueChanged(int)), this, SLOT(OnSliderValueChange(int)));
	connect(ui.m_sliderFPS, &QSlider::sliderPressed, this, &ZegoMainDialog::OnCheckSliderPressed);
	connect(ui.m_sliderFPS, &QSlider::sliderReleased, this, &ZegoMainDialog::OnCheckSliderReleased);

}

void ZegoMainDialog::PullRoomList()
{
	//读取房间列表成功前转菊花
	ui.m_progIndicator->startAnimation();
	//先清空上次的房间列表
	m_roomListModel->removeRows(0, m_roomListModel->rowCount());
	//暂时禁用app版本的选择
	ui.m_cbAppVersion->setEnabled(false);
	//自定义APP版本的房间列表为空
	if (m_versionMode == Version::ZEGO_PROTOCOL_CUSTOM && ui.m_strEdAPPID->text().isEmpty())
	{
		ui.m_progIndicator->stopAnimation();
		//恢复app版本的选择
		ui.m_cbAppVersion->setEnabled(true);
		return;
	}
	unsigned long strAppID;
	if (m_versionMode == Version::ZEGO_PROTOCOL_CUSTOM)
	{
		strAppID = ui.m_strEdAPPID->text().toULong();
	}
	else
	{
		strAppID = mBase.GetAppID();
	}

	QString cstrBaseUrl;
	if (!m_isUseTestEnv) //非测试环境
	    cstrBaseUrl.sprintf(("https://liveroom%u-api.zego.im/demo/roomlist?appid=%u"), strAppID, strAppID);
	else                 //测试环境
		cstrBaseUrl.sprintf(("https://test2-liveroom-api.zego.im/demo/roomlist?appid=%u"), strAppID, strAppID);

	QUrl url(cstrBaseUrl);

	m_networkManager = new QNetworkAccessManager(this);
	QNetworkRequest *m_networkRequest = new QNetworkRequest;
	m_networkRequest->setUrl(url);

	//建立信号槽，当请求服务器完毕之后，保存房间列表的JSON数据
	connect(m_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(writeJsonData(QNetworkReply *)));
	m_networkManager->get(*m_networkRequest);
}

void ZegoMainDialog::writeJsonData(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError){
		json = reply->readAll();

		//qDebug() << "json = "<<json;
		//关闭请求
		reply->deleteLater();
	}
	else{
		ui.m_progIndicator->stopAnimation();
		ui.m_cbAppVersion->setEnabled(true);
		qDebug() << reply->errorString();
		qDebug() << reply->error();
		reply->deleteLater();
		qDebug() << "Network Reply Error.";
		return;
	}

	//解析房间列表
	ParseRoomList(json);
}

void ZegoMainDialog::ParseRoomList(QByteArray json)
{
	if (json.size() == 0){ return; }

	QVector<RoomPtr> vRoomList;

	QJsonParseError json_error;
	QJsonDocument doc = QJsonDocument::fromJson(json, &json_error);

	if (json_error.error != QJsonParseError::NoError){ return; }

	if (!doc.isObject()) { return; }

	QJsonObject obj = doc.object();

	if (!obj.contains("code")) { return; }

	QJsonValue code = obj.take("code");

	if (code.toInt() != 0)
	{
		QMessageBox::information(this, tr("提示"), tr("获取房间列表失败"));
		return; 
	}

	if (!obj.contains("data")) { return; }

	QJsonObject data = obj["data"].toObject();

	if (!data.contains("room_list")) { return; }

	QJsonArray valArray = data["room_list"].toArray();


	for (int i = 0; i < valArray.size(); i++)
	{
		QJsonObject room = valArray.at(i).toObject();
		QString strRoomID = room["room_id"].toString();
		QString strRoomName = room["room_name"].toString();
		QString strAnchorID = room["anchor_id_name"].toString();
		QString strAnchorName = room["anchor_nick_name"].toString();

		int nAnchorSize = 0;
		QJsonArray streamInfo = room["stream_info"].toArray();
		nAnchorSize = streamInfo.size();
		//僵尸房间不加载
		if (nAnchorSize != 0){
			RoomPtr pRoom(new QZegoRoomModel(strRoomID, strRoomName, strAnchorID, strAnchorName));
			pRoom->setLivesCount(nAnchorSize);

			vRoomList.push_back(pRoom);
		}
	}

	//在UI界面中显示房间列表
	RefreshRoomList(vRoomList);
}

void ZegoMainDialog::RefreshRoomList(QVector<RoomPtr> roomList)
{

	m_roomList.clear();
	m_roomList = roomList;

	for (size_t index = 0; index < m_roomList.size(); index++)
	{
		//第一列：房间名
		QString strRoomName;
		strRoomName = m_roomList[index]->getRoomName();
		if (strRoomName.size() == 0)
			strRoomName = m_roomList[index]->getRoomId();

		m_roomListModel->setItem(index, 0, new QStandardItem(strRoomName));

		//第二列：直播模式
		QString strLiveMode;
		strLiveMode = m_roomList[index]->getRoomId().mid(0, 3);
		if (strLiveMode == "#d-")
		    m_roomListModel->setItem(index, 1, new QStandardItem(tr("单主播模式")));
		else if (strLiveMode == "#m-")
			m_roomListModel->setItem(index, 1, new QStandardItem(tr("连麦模式")));
		else if (strLiveMode == "#s-")
			m_roomListModel->setItem(index, 1, new QStandardItem(tr("混流模式")));
		else if (strLiveMode == "#g-")
			m_roomListModel->setItem(index, 1, new QStandardItem(tr("游戏模式")));
		else if (strLiveMode == "#i-")
			m_roomListModel->setItem(index, 1, new QStandardItem(tr("狼人杀模式")));
		else
			m_roomListModel->setItem(index, 1, new QStandardItem(tr("-")));

		//第三列：连麦人数
		QString strDetail("-");
		unsigned int uLivesCount = m_roomList[index]->getLivesCount();

		if (uLivesCount != 0)
			strDetail = QString(tr("%1人正在连麦")).arg(m_roomList[index]->getLivesCount());

		m_roomListModel->setItem(index, 2, new QStandardItem(strDetail));

		//第四列：进入按钮
		ZegoEnterRoomButton *pBtn = new ZegoEnterRoomButton();
		pBtn->initButton();
		ui.m_roomList->resizeRowsToContents();
		connect(pBtn, &QPushButton::clicked, this, &ZegoMainDialog::OnButtonEnterRoom);
		QModelIndex indexTmp = m_roomListModel->index(index, 3, QModelIndex());
		ui.m_roomList->setIndexWidget(indexTmp, pBtn);
		
	}
	//停止转菊花
	ui.m_progIndicator->stopAnimation();
	//恢复app版本按钮
	ui.m_cbAppVersion->setEnabled(true);
}

void ZegoMainDialog::addModeButtonGroup()
{
	m_modeButtonGroup = new QButtonGroup(this);
	m_modeButtonGroup->addButton(ui.m_bSingleMode, 0);
	m_modeButtonGroup->addButton(ui.m_bMultiMode, 1);
	m_modeButtonGroup->addButton(ui.m_bMixMode, 2);
	m_modeButtonGroup->addButton(ui.m_bPublish2StreamMode, 3);
	//默认为连麦模式
	ui.m_bMultiMode->setChecked(true);
	//m_curMode = LIVEROOM::ZEGO_JOIN_PUBLISH;

	connect(m_modeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(OnButtonModeSheetChange(int)));
}

void ZegoMainDialog::addQualityButtonGroup()
{
	m_qualityButtonGroup = new QButtonGroup(this);
	m_qualityButtonGroup->addButton(ui.m_bSuperLow, 0);
	m_qualityButtonGroup->addButton(ui.m_bLow, 1);
	m_qualityButtonGroup->addButton(ui.m_bStandard, 2);
	m_qualityButtonGroup->addButton(ui.m_bHigh, 3);
	m_qualityButtonGroup->addButton(ui.m_bSuperHigh, 4);
	m_qualityButtonGroup->addButton(ui.m_bExtremelyHigh, 5);
	m_qualityButtonGroup->addButton(ui.m_bCustom, 6);

	connect(m_qualityButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(OnButtonQualityChange(int)));
}

void ZegoMainDialog::initComboBox()
{
	
	m_cbMircoPhoneModel = new QStringListModel(this);
	
	m_cbMircoPhoneModel->setStringList(m_MircoPhoneList);

	m_cbMircoPhoneListView = new QListView(this);
	ui.m_cbMircoPhone->setView(m_cbMircoPhoneListView);
	ui.m_cbMircoPhone->setModel(m_cbMircoPhoneModel);
	ui.m_cbMircoPhone->setItemDelegate(new NoFocusFrameDelegate(this));

	m_cbCameraModel = new QStringListModel(this);
	
	m_cbCameraModel->setStringList(m_CameraList);

	m_cbCameraListView = new QListView(this);
	ui.m_cbCamera->setView(m_cbCameraListView);
	ui.m_cbCamera->setModel(m_cbCameraModel);
	ui.m_cbCamera->setItemDelegate(new NoFocusFrameDelegate(this));

	m_cbCameraListView2 = new QListView(this);
	ui.m_cbCamera2->setView(m_cbCameraListView2);
	ui.m_cbCamera2->setModel(m_cbCameraModel);
	ui.m_cbCamera2->setItemDelegate(new NoFocusFrameDelegate(this));
}

void ZegoMainDialog::initButtonIcon()
{
	//ImageButton
	ui.m_bRefreshRoomList->setButtonIcon("refresh_default");
	ui.m_bMin->setButtonIcon("min");
	ui.m_bJumpToNet->setButtonIcon("official");
	ui.m_bClose->setButtonIcon("close");
	//SwitchButton
	ui.m_switchTestEnv->setButtonIcon("switch");
	ui.m_switchCapture->setButtonIcon("switch");
	ui.m_switchFilter->setButtonIcon("switch");
	ui.m_switchVerticalCapture->setButtonIcon("switch");
	ui.m_switchSurfaceMerge->setButtonIcon("switch");
	//ui.m_switchUnknown->setButtonIcon("switch");
	//ui.m_switchUnknown2->setButtonIcon("switch");
	ui.m_switchVirtualStereo->setButtonIcon("switch");
	ui.m_switchReverb->setButtonIcon("switch");
	ui.m_switchNational->setButtonIcon("switch");
	//StateButton
	ui.m_bResolutionDown->setButtonIcon("sub");
	ui.m_bBitrateDown->setButtonIcon("sub");
	ui.m_bFPSDown->setButtonIcon("sub");
	ui.m_bResolutionUp->setButtonIcon("add");
	ui.m_bBitrateUp->setButtonIcon("add");
	ui.m_bFPSUp->setButtonIcon("add");
}

void ZegoMainDialog::insertStringListModelItem(QStringListModel * model, QString name, int size)
{
	int row = size;
	model->insertRow(row);
	QModelIndex index = model->index(row);
	model->setData(index,name);
}

void ZegoMainDialog::removeStringListModelItem(QStringListModel * model, QString name)
{
	if (model->rowCount() > 0)
	{
		int curIndex = -1;
		QStringList list = model->stringList();
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == name)
				curIndex = i;
		}

		model->removeRows(curIndex, 1);
	}
}

void ZegoMainDialog::removeStringListModelItemByIndex(QStringListModel * model, int index)
{
	model->removeRow(index);
}

void ZegoMainDialog::banSwitch()
{
	//以后功能等demo实现了再取消禁用
	//ui.m_switchCapture->setEnabled(false);
	//ui.m_switchFilter->setEnabled(false);

	ui.m_lbAudioRight->setVisible(false);
	ui.m_lbNational->setVisible(false);
	ui.m_switchNational->setVisible(false);
}

QVector<QString> ZegoMainDialog::handleAppSign(QString appSign)
{
	QVector<QString> vecAppSign;
	appSign = appSign.simplified();
	appSign.remove(",");
	appSign.remove(" ");
	qDebug() << "appSign = "<<appSign;

	for (int i = 0; i < appSign.size(); i += 4)
	{
		//qDebug() << "curString = " << appSign.mid(i, 4);
		QString hexSign = appSign.mid(i, 4);
		hexSign.remove("0x");
		hexSign.toUpper();
		vecAppSign.append(hexSign);
	}
	qDebug() << vecAppSign;
	return vecAppSign;
}

int ZegoMainDialog::getCameraIndexFromID(const QString& cameraID)
{
	for (int i = 0; i < m_vecVideoDevice.size(); ++i)
	{
		if (m_vecVideoDevice.at(i).deviceId == cameraID)
			return i;
	}

	return -1;
}

//part2:SDK回调函数
void ZegoMainDialog::OnInitSDK(int nError)
{
	if (nError == 0)
	{
		qDebug() << "InitSDK Succeeded";
	}
	else
	{
		qDebug() << QString("InitSDK Error: %1").arg(nError);
	}
}

//part3:UI回调函数
void ZegoMainDialog::OnButtonModeSheetChange(int id)
{
	QPushButton *button = (QPushButton *)m_modeButtonGroup->button(id);

	if (id == MODE_PUBLISH_2_STREAM)
	{
		ui.m_vSpacerUpper->changeSize(17, 17, QSizePolicy::Expanding, QSizePolicy::Expanding);
		ui.m_lbCamera2->setVisible(true);
		ui.m_cbCamera2->setVisible(true);
	}
	else
	{
		ui.m_vSpacerUpper->changeSize(30, 30, QSizePolicy::Expanding, QSizePolicy::Expanding);
		ui.m_lbCamera2->setVisible(false);
		ui.m_cbCamera2->setVisible(false);
	}	
}

void ZegoMainDialog::OnButtonQualityChange(int id)
{
	QPushButton *button = (QPushButton *)m_qualityButtonGroup->button(id);
	
	if (button->isChecked() && (id == VQ_SelfDef))
	{
		//isVideoCustom = true;
		//changeSliderState(true);
	}
	else if (button->isChecked())
	{
		isVideoCustom = false;
		//changeSliderState(false);
		mConfig.SetVideoQuality((VideoQuality)id);

		SettingsPtr curSettings = mConfig.GetVideoSettings();
		IndexSet index = curSettings->getIndex();

		ui.m_lbValueResolution->setText(m_vecResolution[index.indexResolution]);
		ui.m_lbValueBitrate->setText(m_vecBitrate[index.indexBitrate]);
		ui.m_lbValueFPS->setText(m_vecFPS[index.indexFps]);

		ui.m_sliderResolution->setValue(g_Resolution_length - index.indexResolution);
		ui.m_sliderBitrate->setValue(g_Bitrate_length - index.indexBitrate);
		ui.m_sliderFPS->setValue(g_FPS_length - index.indexFps);

		mConfig.SaveConfig();

	}
	
}


void ZegoMainDialog::OnClickTitleButton()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());

	if (pButton == ui.m_bMin)
	{
		this->showMinimized();
	}
	else if (pButton == ui.m_bClose)
	{
		close();
	}
	else if (pButton == ui.m_bJumpToNet)
	{
		QDesktopServices::openUrl(QUrl(QLatin1String("https://www.zego.im")));
	}
}

void ZegoMainDialog::OnSliderValueChange(int value)
{
	//每次slider改变时将当前视频质量改为“自定义”，同时将每次改动写入ini文件中

	QSlider *slider = qobject_cast<QSlider *>(sender());

	if (!isVideoCustom && m_sliderPressed)
	{
		isVideoCustom = true;
		ui.m_bCustom->setChecked(true);
	}

	SettingsPtr curSettings = mConfig.GetVideoSettings();
	if (slider == ui.m_sliderResolution)
	{
		slider->setValue(value);
		ui.m_lbValueResolution->setText(m_vecResolution[g_Resolution_length - value]);
		curSettings->SetResolution(g_Resolution[g_Resolution_length - value]);
	}
	else if (slider == ui.m_sliderBitrate)
	{
		slider->setValue(value);
		ui.m_lbValueBitrate->setText(m_vecBitrate[g_Bitrate_length - value]);
		curSettings->SetBitrate(g_Bitrate[g_Bitrate_length - value]);
	}
	else if (slider == ui.m_sliderFPS)
	{
		slider->setValue(value);
		ui.m_lbValueFPS->setText(m_vecFPS[g_FPS_length - value]);
		curSettings->SetFps(g_Fps[g_FPS_length - value]);
	}

	mConfig.SetVideoSettings(curSettings);
	mConfig.SaveConfig();
}

void ZegoMainDialog::OnButtonSliderValueChange()
{
	//每次增减视频参数时将当前视频质量改为“自定义”，同时将每次改动写入ini文件中
	if (!isVideoCustom)
	{
		isVideoCustom = true;
		ui.m_bCustom->setChecked(true);
	}

	QPushButton *button = qobject_cast<QPushButton *>(sender());

	SettingsPtr curSettings = mConfig.GetVideoSettings();

	if (button == ui.m_bResolutionDown)
	{
		int curValue = ui.m_sliderResolution->value() - 1;
		if (curValue >= 0){
			ui.m_sliderResolution->setValue(curValue);
			ui.m_lbValueResolution->setText(m_vecResolution[g_Resolution_length - curValue]);
			curSettings->SetResolution(g_Resolution[g_Resolution_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}

	}
	else if (button == ui.m_bResolutionUp)
	{
		int curValue = ui.m_sliderResolution->value() + 1;
		if (curValue <= g_Resolution_length){
			ui.m_sliderResolution->setValue(curValue);
			ui.m_lbValueResolution->setText(m_vecResolution[g_Resolution_length - curValue]);
			curSettings->SetResolution(g_Resolution[g_Resolution_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}
	}
	else if (button == ui.m_bBitrateDown)
	{
		int curValue = ui.m_sliderBitrate->value() - 1;
		if (curValue >= 0){
			ui.m_sliderBitrate->setValue(curValue);
			ui.m_lbValueBitrate->setText(m_vecBitrate[g_Bitrate_length - curValue]);
			curSettings->SetBitrate(g_Bitrate[g_Bitrate_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}
	}
	else if (button == ui.m_bBitrateUp)
	{
		int curValue = ui.m_sliderBitrate->value() + 1;
		if (curValue <= g_Bitrate_length){
			ui.m_sliderBitrate->setValue(curValue);
			ui.m_lbValueBitrate->setText(m_vecBitrate[g_Bitrate_length - curValue]);
			curSettings->SetBitrate(g_Bitrate[g_Bitrate_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}
	}
	else if (button == ui.m_bFPSDown)
	{
		int curValue = ui.m_sliderFPS->value() - 1;
		if (curValue >= 0)
		{
			ui.m_sliderFPS->setValue(curValue);
			ui.m_lbValueFPS->setText(m_vecFPS[g_FPS_length - curValue]);
			curSettings->SetFps(g_Fps[g_FPS_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}
	}
	else if (button == ui.m_bFPSUp)
	{
		int curValue = ui.m_sliderFPS->value() + 1;
		if (curValue <= g_FPS_length)
		{
			ui.m_sliderFPS->setValue(curValue);
			ui.m_lbValueFPS->setText(m_vecFPS[g_FPS_length - curValue]);
			curSettings->SetFps(g_Fps[g_FPS_length - curValue]);

			mConfig.SetVideoSettings(curSettings);
			mConfig.SaveConfig();
		}
	}
}

void ZegoMainDialog::on_m_bRefreshRoomList_clicked()
{
	PullRoomList();
}

void ZegoMainDialog::on_m_bCreateRoom_clicked()
{
	if (m_strEdUserId.isEmpty() || m_strEdUserName.isEmpty())
	{
		QMessageBox::warning(NULL, tr("警告"), tr("UserID或UserName不能为空"));
		return;
	}

	if (ui.m_strEdAPPID->text() == "")
	{
		QMessageBox::information(NULL, tr("提示"), tr("AppID不能为空"));
		return;
	}

	if (ui.m_strEdAPPSign->text() == "")
	{
		QMessageBox::information(NULL, tr("提示"), tr("AppSign不能为空"));
		return;
	}

	disconnect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	disconnect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	disconnect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));

	mConfig.SetUserRole(true);
	mConfig.SetUserId(m_strEdUserId);
	mConfig.SetUserName(m_strEdUserName);

	QString strUserId = mConfig.GetUserId();
	QString strUserName = mConfig.getUserName();

	if (m_versionMode == Version::ZEGO_PROTOCOL_CUSTOM)
	{
		unsigned long appId = ui.m_strEdAPPID->text().toUInt();
		QString strAppSign = ui.m_strEdAPPSign->text();
		QVector<QString> vecAppSign = handleAppSign(strAppSign);
		if (vecAppSign.size() != 32)
		{
			QMessageBox::information(NULL, tr("提示"), tr("AppSign 必须为32位"));
			return;
		}

		unsigned char *appSign = new unsigned char[32];
		for (int i = 0; i < vecAppSign.size(); i++)
		{
			bool ok;
			appSign[i] = (unsigned char)vecAppSign[i].toInt(&ok, 16);
		}

		mBase.UninitAVSDK();
		if (!mBase.InitAVSDKwithCustomAppId(strUserId, strUserName, appId, appSign))
		{
			QMessageBox::information(NULL, tr("提示"), tr("初始化SDK失败"));
			return;
		}

	}

	//更新用户信息
	LIVEROOM::SetUser(strUserId.toStdString().c_str(), strUserName.toStdString().c_str());

	SettingsPtr pCurSettings = mConfig.GetVideoSettings();
	if (pCurSettings == nullptr)
	{
		return;
	}

	if (pCurSettings->GetCameraId().length() == 0)
		pCurSettings->InitDeviceId();

	int modeID = m_modeButtonGroup->checkedId();
	
	QString strMode;
	switch (modeID)
	{
	case MODE_SINGLE_ANCHOR:
		strMode = "#d";
		break;
	case MODE_JOIN_PUBLISH:
		strMode = "#m";
		break;
	case MODE_MIX_STREAM:
		strMode = "#s";
		break;
	case MODE_PUBLISH_2_STREAM:
		strMode = "WWJS";
	default:
		break;
	}

	QString strRoomID = QString(("%1-%2")).arg(strMode).arg(mConfig.GetUserId());

#ifdef Q_OS_WIN
	QString strRoomName = "windows-room-" + strUserId;
#else
	QString strRoomName = "mac-room-" + strUserId;
#endif

	QString inputRoomName = ui.m_edRoomName->text();
	if (!inputRoomName.isEmpty())
	{
		strRoomName = inputRoomName;
		ui.m_edRoomName->setText("");
	}

	RoomPtr pRoom(new QZegoRoomModel(strRoomID, strRoomName, strUserId, strUserName));

	if (mConfig.GetUseExternalCaptureAndRender())
	{
		ZegoExternalAnchorDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoExternalAnchorDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);

		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();

		return;
	}
	if (modeID == MODE_SINGLE_ANCHOR)
	{
		
		ZegoSingleAnchorDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoSingleAnchorDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
		
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}
	else if (modeID == MODE_JOIN_PUBLISH)
	{
		ZegoMoreAnchorDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoMoreAnchorDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
	
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}
	else if (modeID == MODE_MIX_STREAM)
	{
		ZegoMixStreamAnchorDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
        connect(&liveroom, &ZegoMixStreamAnchorDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
		             
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}
	else if (modeID = MODE_PUBLISH_2_STREAM)
	{
		ZegoPublish2StreamDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoPublish2StreamDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);

		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}

	connect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	connect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	connect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));
}

void ZegoMainDialog::OnButtonEnterRoom()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());

	int row;
	for (int i = 0; i < m_roomList.size(); i++){
		QModelIndex index = m_roomListModel->index(i, 3, QModelIndex());
		if ((QPushButton*)ui.m_roomList->indexWidget(index) == pButton)
			row = i;
	}

	qDebug() << "this is row " << row;
	int roomIndex = row;

	RoomPtr pRoom = m_roomList[roomIndex];

	if (m_strEdUserId.isEmpty() || m_strEdUserName.isEmpty())
	{
		QMessageBox::warning(NULL, tr("警告"), tr("UserID或UserName不能为空"));
		return;
	}
	if (ui.m_strEdAPPID->text() == "")
	{
		QMessageBox::information(NULL, tr("提示"), tr("AppID不能为空"));
		return;
	}

	if (ui.m_strEdAPPSign->text() == "")
	{
		QMessageBox::information(NULL, tr("提示"), tr("AppSign不能为空"));
		return;
	}

	disconnect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	disconnect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	disconnect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));
	//disconnect()
	int modeID;
	QString playLiveMode = pRoom->getRoomId().mid(0, 3);
	if (playLiveMode == "#d-")
		modeID = MODE_SINGLE_ANCHOR;
	else if (playLiveMode == "#m-")
		modeID = MODE_JOIN_PUBLISH;
	else if (playLiveMode == "#s-")
		modeID = MODE_MIX_STREAM;
	else
	{
		if (pRoom->getLivesCount() == 1)
			modeID = MODE_SINGLE_ANCHOR;
		else if (pRoom->getLivesCount() > 1)
			modeID = MODE_JOIN_PUBLISH;
	}
	
	mConfig.SetUserRole(false);
	mConfig.SetUserId(m_strEdUserId);
	mConfig.SetUserName(m_strEdUserName);
	

	QString strUserId = mConfig.GetUserId();
	QString strUserName = mConfig.getUserName();

	if (m_versionMode == Version::ZEGO_PROTOCOL_CUSTOM)
	{
		unsigned long appId = ui.m_strEdAPPID->text().toUInt();
		QString strAppSign = ui.m_strEdAPPSign->text();
		QVector<QString> vecAppSign = handleAppSign(strAppSign);
		unsigned char *appSign = new unsigned char[32];
		for (int i = 0; i < vecAppSign.size(); i++)
		{
			bool ok;
			appSign[i] = (unsigned char)vecAppSign[i].toInt(&ok, 16);
		}
		LIVEROOM::UnInitSDK();
		if (!LIVEROOM::InitSDK(appId, appSign, 32))
		{
			QMessageBox::information(NULL, tr("提示"), tr("初始化SDK失败"));
			return;
		}

	}

	//更新用户信息
	LIVEROOM::SetUser(strUserId.toStdString().c_str(), strUserName.toStdString().c_str());

	SettingsPtr pCurSettings = mConfig.GetVideoSettings();
	//限定观众模式都不能推第二路流
	pCurSettings->SetUsePublish2Stream(false);
	if (pCurSettings == nullptr)
	{
		return;
	}

	mConfig.SaveConfig();

	if (modeID == MODE_SINGLE_ANCHOR)
	{
		ZegoSingleAudienceDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoSingleAudienceDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
		
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}
	else if (modeID == MODE_JOIN_PUBLISH)
	{
		ZegoMoreAudienceDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoMoreAudienceDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
		
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}
	else if (modeID == MODE_MIX_STREAM)
	{
		ZegoMixStreamAudienceDialog liveroom(pRoom, m_device, m_cbMircoPhoneModel, m_cbCameraModel, this);
		liveroom.initDialog();
		connect(&liveroom, &ZegoMixStreamAudienceDialog::sigSaveVideoSettings, this, &ZegoMainDialog::OnSaveVideoSettings);
		
		//进入直播房间前先隐藏该界面
		this->hide();
		liveroom.exec();
	}

	connect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	connect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));
	connect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));
}

void ZegoMainDialog::on_m_switchTestEnv_clicked()
{
	if (ui.m_switchTestEnv->isChecked())
	{
		qDebug() << "TestEnv checked!";
		m_isUseTestEnv = true;
	
	}
	else
	{
		qDebug() << "TestEnv unChecked!";
		m_isUseTestEnv = false;
		
	}

	ui.m_switchTestEnv->setEnabled(false);
	mBase.setTestEnv(m_isUseTestEnv);
	mBase.UninitAVSDK();
	mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
	ui.m_switchTestEnv->setEnabled(true);

	//将修改写到用户配置中
	mConfig.SetUseTestEnv(m_isUseTestEnv);
	mConfig.SaveConfig();

	//当开启/关闭了测试环境时，其房间列表需要马上刷新一次，因为在两个环境下拉取房间列表不一样，避免出错
	PullRoomList();
}

void ZegoMainDialog::on_m_switchCapture_clicked()
{
	if (ui.m_switchCapture->isChecked())
	{
		qDebug() << "VideoCapture checked!";
		m_isUseVideoCapture = true;

	}
	else
	{
		qDebug() << "VideoCapture unChecked!";
		m_isUseVideoCapture = false;

	}

	if (m_isUseVideoCapture)
	{
		
		ui.m_bMixMode->setEnabled(false);
		ui.m_bPublish2StreamMode->setEnabled(false);
		ui.m_bMultiMode->setEnabled(false);

		int modeID = m_modeButtonGroup->checkedId();
		//只有单主播模式下可以开启外部采集
		if (modeID != MODE_SINGLE_ANCHOR)
		{
			ui.m_bSingleMode->setChecked(true);
		}
	}
	else
	{
		//恢复模式按钮
		ui.m_bMixMode->setEnabled(true);
		ui.m_bPublish2StreamMode->setEnabled(true);
		ui.m_bMultiMode->setEnabled(true);
	}

	ui.m_switchCapture->setEnabled(false);
	mBase.setUseVideoCapture(m_isUseVideoCapture);
	mBase.UninitAVSDK();

	//二选一，如果选择外部采集时已选择屏幕直播，则关闭屏幕直播
	if (ui.m_switchSurfaceMerge->isChecked())
	{
		ui.m_switchSurfaceMerge->setChecked(false);
		mBase.setUseSurfaceMerge(false);

		SettingsPtr curSettings = mConfig.GetVideoSettings();
		curSettings->SetSurfaceMerge(false);
		mConfig.SetVideoSettings(curSettings);
	}

	mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
	ui.m_switchCapture->setEnabled(true);
	mConfig.SetUseExternalCaptureAndRender(m_isUseVideoCapture);
}

void ZegoMainDialog::on_m_switchFilter_clicked()
{
	if (ui.m_switchFilter->isChecked())
	{
		qDebug() << "VideoFilter checked!";
		m_isUseVideoFilter = true;

	}
	else
	{
		qDebug() << "VideoFilter unChecked!";
		m_isUseVideoFilter = false;

	}

	ui.m_switchFilter->setEnabled(false);
	mBase.setUseVideoFilter(m_isUseVideoFilter);
	mBase.UninitAVSDK();
	mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
	ui.m_switchFilter->setEnabled(true);
}

void ZegoMainDialog::on_m_switchVerticalCapture_clicked()
{
	bool isUseVerticalCapture;

	if (ui.m_switchVerticalCapture->isChecked())
		isUseVerticalCapture = true;
	else
		isUseVerticalCapture = false;

	mConfig.SetUseVerticalCapture(isUseVerticalCapture);
	mConfig.SaveConfig();
}

void ZegoMainDialog::on_m_switchSurfaceMerge_clicked()
{
	if (ui.m_switchSurfaceMerge->isChecked())
	{
		qDebug() << "surface merge checked";
		m_isUseSurfaceMerge = true;
	}
	else
	{
		m_isUseSurfaceMerge = false;
	}

	if (m_isUseSurfaceMerge)
	{
		if (ui.m_switchCapture->isChecked())
		{
			ui.m_switchCapture->setChecked(false);
			mBase.setUseVideoCapture(false);
			mConfig.SetUseExternalCaptureAndRender(false);
		}

		ui.m_bMixMode->setEnabled(false);
		ui.m_bPublish2StreamMode->setEnabled(false);
		int modeID = m_modeButtonGroup->checkedId();
	    //只有单主播模式和连麦模式下可以开启屏幕推流
	    if (modeID == MODE_MIX_STREAM || modeID == MODE_PUBLISH_2_STREAM)
	    {
		    ui.m_bMultiMode->setChecked(true);
	    }
    }
    else
    {
	    //恢复模式按钮
	    ui.m_bMixMode->setEnabled(true);
		ui.m_bPublish2StreamMode->setEnabled(true);
     }

	ui.m_switchSurfaceMerge->setEnabled(false);
	mBase.UninitAVSDK();
	mBase.setUseSurfaceMerge(m_isUseSurfaceMerge);

	SettingsPtr curSettings = mConfig.GetVideoSettings();
	curSettings->SetSurfaceMerge(m_isUseSurfaceMerge);
	mConfig.SetVideoSettings(curSettings);

	mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
	ui.m_switchSurfaceMerge->setEnabled(true);
}

void ZegoMainDialog::on_m_switchReverb_clicked()
{
	/** 音频混响模式 */
	/*ZegoAVAPIAudioReverbMode
	{
		ZEGO_AUDIO_REVERB_MODE_SOFT_ROOM = 0,
		ZEGO_AUDIO_REVERB_MODE_WARM_CLUB = 1,
		ZEGO_AUDIO_REVERB_MODE_CONCERT_HALL = 2,
		ZEGO_AUDIO_REVERB_MODE_LARGE_AUDITORIUM = 3,
	};*/
	bool isUseReverb;
	if (ui.m_switchReverb->isChecked())
	{
		isUseReverb = true;
	}
	else
	{
		isUseReverb = false;
	}

	AUDIOPROCESSING::EnableReverb(isUseReverb, AUDIOPROCESSING::ZEGO_AUDIO_REVERB_MODE_LARGE_AUDITORIUM);
}

void ZegoMainDialog::on_m_switchVirtualStereo_clicked()
{
	bool isUseVirtualStereo;
	if (ui.m_switchVirtualStereo->isChecked())
	{
		isUseVirtualStereo = true;
	}
	else
	{
		isUseVirtualStereo = false;
	}

	//param angle 虚拟立体声中声源的角度，范围为0～180，90为正前方，0和180分别对应最左边和最右边
	AUDIOPROCESSING::EnableVirtualStereo(isUseVirtualStereo, 0);
}

void ZegoMainDialog::OnCheckSliderPressed()
{
	m_sliderPressed = true;
}

void ZegoMainDialog::OnCheckSliderReleased()
{
	m_sliderPressed = false;
}

void ZegoMainDialog::OnSaveUserIdChanged()
{
	if (ui.m_strEdUserId->hasFocus())
		return;

	m_strEdUserId = ui.m_strEdUserId->text();
	m_strEdUserId = m_strEdUserId.simplified();
	mConfig.SetUserId(m_strEdUserId);
	mConfig.SaveConfig();
}

void ZegoMainDialog::OnSaveUserNameChanged()
{
	if (ui.m_strEdUserName->hasFocus())
		return;

	m_strEdUserName = ui.m_strEdUserName->text();
	m_strEdUserName = m_strEdUserName.simplified();
	mConfig.SetUserName(m_strEdUserName);
	mConfig.SaveConfig();
}

void ZegoMainDialog::OnSaveAppIdChanged()
{
	if (ui.m_strEdAPPID->hasFocus())
		return;

	if (m_versionMode == ZEGO_PROTOCOL_CUSTOM)
	{
		mConfig.SetAppId(ui.m_strEdAPPID->text());
		mConfig.SaveConfig();
	}
}

void ZegoMainDialog::OnSaveAppSignChanged()
{
	if (ui.m_strEdAPPSign->hasFocus())
		return;

	if (m_versionMode == ZEGO_PROTOCOL_CUSTOM)
	{
		mConfig.SetAppSign(ui.m_strEdAPPSign->text());
		mConfig.SaveConfig();
	}
}

void ZegoMainDialog::OnSwitchAudioDevice(int id)
{
	if (this->isHidden() && m_initedDialog)
		return;

	if (id < 0)
		return;

	if (id < m_vecAudioDevice.size())
	{
		m_device->SetMicrophoneIdByIndex(id);
		QString audio_device_id = m_device->GetAudioDeviceId();

		SettingsPtr curSettings = mConfig.GetVideoSettings();
		curSettings->SetMicrophoneId(audio_device_id);
		mConfig.SetVideoSettings(curSettings);
		ui.m_cbMircoPhone->setCurrentIndexWithoutSignal(id);
		update();
	}

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
}

void ZegoMainDialog::OnSwitchVideoDevice(int id)
{
	if (this->isHidden() && m_initedDialog)
		return;

	if (id < 0)
		return;

	if (id < m_vecVideoDevice.size())
	{
		SettingsPtr curSettings = mConfig.GetVideoSettings();
		//若摄像头1需要选取的摄像头已被摄像头2选取，则交换摄像头
		/*if (id == ui.m_cbCamera2->currentIndex())
		{
			LIVEROOM::SetVideoDevice(curSettings->GetCameraId().toStdString().c_str(), ZEGO::AV::PUBLISH_CHN_AUX);
			curSettings->SetCameraId2(curSettings->GetCameraId());

			int curLastCameraIndex = getCameraIndexFromID(curSettings->GetCameraId());
			if (curLastCameraIndex < 0)
				return;

			ui.m_cbCamera2->setCurrentIndexWithoutSignal(curLastCameraIndex);
		}

		LIVEROOM::SetVideoDevice(m_vecVideoDeviceIDs[id].toStdString().c_str());
		curSettings->SetCameraId(m_vecVideoDeviceIDs[id]);
		*/
		QDeviceState state = m_device->SetCameraIdByIndex(id);
		//若摄像头1需要选取的摄像头已被摄像头2选取，则交换摄像头
		if (state == STATE_SWAP)
		{
			curSettings->SetCameraId2(m_device->GetVideoDeviceId2());
			ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());
		}

		curSettings->SetCameraId(m_device->GetVideoDeviceId());
		mConfig.SetVideoSettings(curSettings);

		ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
		update();

		qDebug() << "[MainDialog::VideoDevice_Changed_1]: current video device_main : " << curSettings->GetCameraId() << " video device_aux : " << curSettings->GetCameraId2();
	}

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
}

void ZegoMainDialog::OnSwitchVideoDevice2(int id)
{
	if (this->isHidden() && m_initedDialog)
		return;

	if (id < 0)
		return;

	if (id < m_vecVideoDevice.size())
	{
		SettingsPtr curSettings = mConfig.GetVideoSettings();
		//若摄像头1需要选取的摄像头已被摄像头2选取，则交换摄像头
		
		QDeviceState state = m_device->SetCameraId2ByIndex(id);
		if (state == STATE_SWAP)
		{
			curSettings->SetCameraId(m_device->GetVideoDeviceId());
			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
		}

		curSettings->SetCameraId2(m_device->GetVideoDeviceId2());
		mConfig.SetVideoSettings(curSettings);

		ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());
		update();

		qDebug() << "[MainDialog::VideoDevice_Changed_2]: current video device_main : " << curSettings->GetCameraId() << " video device_aux : " << curSettings->GetCameraId2();
	}

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
}

void ZegoMainDialog::OnDeviceAdded(int device_type, QString device_name)
{
	if (this->isHidden())
		return;

	SettingsPtr curSettings = mConfig.GetVideoSettings();

	if (device_type == TYPE_AUDIO)
	{
		ui.m_cbMircoPhone->blockSignals(true);
		insertStringListModelItem(m_cbMircoPhoneModel, device_name, m_cbMircoPhoneModel->rowCount());
		ui.m_cbMircoPhone->blockSignals(false);

		m_vecAudioDevice = m_device->GetAudioDeviceList();

		if (m_vecAudioDevice.size() == 1)
		{
			curSettings->SetMicrophoneId(m_device->GetAudioDeviceId());
			ui.m_cbMircoPhone->setCurrentIndexWithoutSignal(0);
		}

	}
	else if (device_type == TYPE_VIDEO)
	{
		ui.m_cbCamera->blockSignals(true);
		ui.m_cbCamera2->blockSignals(true);
		insertStringListModelItem(m_cbCameraModel, device_name, m_cbCameraModel->rowCount());
		ui.m_cbCamera->blockSignals(false);
		ui.m_cbCamera2->blockSignals(false);

		m_vecVideoDevice = m_device->GetVideoDeviceList();

		
		if (m_vecVideoDevice.size() == 1)
		{
			curSettings->SetCameraId(m_device->GetVideoDeviceId());
			ui.m_cbCamera->setCurrentIndexWithoutSignal(0);
			ui.m_cbCamera2->setModel(new QStringListModel(this));

		}
		else if (m_vecVideoDevice.size() == 2)
		{
			ui.m_cbCamera2->blockSignals(true);
			ui.m_cbCamera2->setModel(m_cbCameraModel);
			ui.m_cbCamera2->setCurrentIndex(1);
			ui.m_cbCamera2->blockSignals(false);

			ui.m_cbCamera->setCurrentIndexWithoutSignal(0);

			curSettings->SetCameraId(m_device->GetVideoDeviceId());
			curSettings->SetCameraId2(m_device->GetVideoDeviceId2());
		}
	}

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
	mConfig.SetVideoSettings(curSettings);
}

void ZegoMainDialog::OnDeviceDeleted(int device_type, int index)
{
	if (this->isHidden())
		return;

	SettingsPtr curSettings = mConfig.GetVideoSettings();

	if (device_type == TYPE_AUDIO)
	{
		ui.m_cbMircoPhone->blockSignals(true);
		removeStringListModelItemByIndex(m_cbMircoPhoneModel, index);
		ui.m_cbMircoPhone->blockSignals(false);
	   
		m_vecAudioDevice = m_device->GetAudioDeviceList();

		curSettings->SetMicrophoneId(m_device->GetAudioDeviceId());

		int curIndex = m_device->GetAudioDeviceIndex();
		if(curIndex >= 0)
		    ui.m_cbMircoPhone->setCurrentIndexWithoutSignal(curIndex);
	}
	else if (device_type == TYPE_VIDEO)
	{
		ui.m_cbCamera->blockSignals(true);
		ui.m_cbCamera2->blockSignals(true);
		removeStringListModelItemByIndex(m_cbCameraModel, index);
		ui.m_cbCamera->blockSignals(false);
		ui.m_cbCamera2->blockSignals(false);

		m_vecVideoDevice = m_device->GetVideoDeviceList();

		if (m_vecVideoDevice.size() == 1)
		{
			ui.m_cbCamera2->blockSignals(true);
			ui.m_cbCamera2->setModel(new QStringListModel(this));
			ui.m_cbCamera2->blockSignals(false);

			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
		}
		else
		{
			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
			ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());
		}

		curSettings->SetCameraId(m_device->GetVideoDeviceId());
		curSettings->SetCameraId2(m_device->GetVideoDeviceId2());
	}

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
	mConfig.SetVideoSettings(curSettings);
}

void ZegoMainDialog::OnSaveVideoSettings(SettingsPtr settings)
{

	mConfig.SetVideoSettings(settings);
	//是否更改了麦克风
	
	/*int index = 0;
	for (int i = 0; i < m_vecAudioDeviceIDs.size(); i++)
		if (m_vecAudioDeviceIDs[i] == settings->GetMircophoneId())
		{
			index = i;
		    break;
		}
		*/
	ui.m_cbMircoPhone->setCurrentIndexWithoutSignal(m_device->GetAudioDeviceIndex());
		
	//是否更改了摄像头1和2
	/*index = 0;
	for (int i = 0; i < m_vecVideoDeviceIDs.size(); i++)
	{
		if (m_vecVideoDeviceIDs[i] == settings->GetCameraId())
		{
			index = i;
			break;
		}
	}
	*/
	ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());

	/*index = 0;
	for (int i = 0; i < m_vecVideoDeviceIDs.size(); i++)
	{
		if (m_vecVideoDeviceIDs[i] == settings->GetCameraId2())
		{
			index = i;
			break;
		}
	}*/
	
	ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());
	
}

void ZegoMainDialog::OnComboBoxAppVersionChanged(int id)
{
	//ui.m_cbAppVersion->setCurrentIndex(id);

	m_versionMode = (Version)id;
	mConfig.SetAppVersion(id);

	if (id != ZEGO_PROTOCOL_CUSTOM){

		mBase.setKey(id);
		ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppID()));
		ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
		ui.m_strEdAPPID->setEnabled(false);
		ui.m_strEdAPPSign->setEnabled(false);

		mBase.UninitAVSDK();
		mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
	}
	else
	{
		if (!mConfig.GetAppConfig().m_customAppId.isEmpty())
			ui.m_strEdAPPID->setText(mConfig.GetAppConfig().m_customAppId);
		else
		    ui.m_strEdAPPID->setText("");

		if (!mConfig.GetAppConfig().m_customAppSign.isEmpty())
			ui.m_strEdAPPSign->setText(mConfig.GetAppConfig().m_customAppSign);
		else
		    ui.m_strEdAPPSign->setText("");

		ui.m_strEdAPPID->setEnabled(true);
		ui.m_strEdAPPSign->setEnabled(true);
		if(ui.m_strEdAPPID->text().isEmpty())
		    ui.m_strEdAPPID->setFocus();
	}
	mConfig.SaveConfig();
	
	//标题
	ui.m_lbTitle->setText(tr("ZegoLiveDemo(%1)").arg(ui.m_cbAppVersion->currentText()));
	//刷新房间列表
	PullRoomList();
}

void ZegoMainDialog::OnComboBoxCameraRotation(int id)
{
	qDebug() << "rotation index = " << id;

	mBase.UninitAVSDK();
	LIVEROOM::SetConfig(rotation_list[id].toStdString().c_str());
	mBase.InitAVSDK(m_strEdUserId, m_strEdUserName);
}

void ZegoMainDialog::on_m_bUploadLog_clicked()
{
	LIVEROOM::UploadLog();
	QMessageBox::information(NULL, tr("提示"), tr("日志上传成功"));
}

bool ZegoMainDialog::eventFilter(QObject *target, QEvent *event)
{
	if (target == ui.m_edRoomName) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) 
			{
				on_m_bCreateRoom_clicked();
				return true;
			}
		}
	}
	else if (target == ui.m_strEdUserId){
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				ui.m_strEdUserId->clearFocus();
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Tab)
			{
				ui.m_strEdUserId->clearFocus();
				ui.m_strEdUserName->setFocus();
				return true;
			}
		}
	}
	else if (target == ui.m_strEdUserName){
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Tab){
				ui.m_strEdUserName->clearFocus();
				return true;
			}
		}
	}
	else if (target == ui.m_strEdAPPID){
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				//appId为空的话，转回UDP
				if (ui.m_strEdAPPID->text().isEmpty())
				{
					QMessageBox::information(NULL, tr("提示"), tr("AppID不能为空"));
					mBase.setKey(Version::ZEGO_PROTOCOL_UDP);
					ui.m_cbAppVersion->setCurrentIndex(Version::ZEGO_PROTOCOL_UDP);
					ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppID()));
					ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
					ui.m_strEdAPPID->clearFocus();
					ui.m_strEdAPPID->setEnabled(false);
					ui.m_strEdAPPSign->setEnabled(false);
					
				}
				ui.m_strEdAPPID->clearFocus();
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Tab)
			{
				ui.m_strEdAPPID->clearFocus();
				ui.m_strEdAPPSign->setFocus();
				return true;
			}
		}
		
	}
	else if (target == ui.m_strEdAPPSign){
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Tab){
				if (ui.m_strEdAPPSign->text().isEmpty())
				{
					QMessageBox::information(NULL, tr("提示"), tr("AppSign不能为空"));
					mBase.setKey(Version::ZEGO_PROTOCOL_UDP);
					ui.m_cbAppVersion->setCurrentIndex(Version::ZEGO_PROTOCOL_UDP);
					ui.m_strEdAPPID->setText(QString("%1").arg(mBase.GetAppID()));
					ui.m_strEdAPPSign->setText(tr("AppSign 已设置"));
					ui.m_strEdAPPSign->clearFocus();
					ui.m_strEdAPPID->setEnabled(false);
					ui.m_strEdAPPSign->setEnabled(false);
				}
				ui.m_strEdAPPSign->clearFocus();
				return true;
			}
		}
	}
	else
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Escape)
				return true;
		}
	}
	return QDialog::eventFilter(target, event);
}

