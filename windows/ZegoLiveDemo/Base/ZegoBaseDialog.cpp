#include "ZegoBaseDialog.h"
#include "ZegoLiveDemoDefines.h"
#include "Signal/ZegoSDKSignal.h"
#include "Base/IncludeZegoLiveRoomApi.h"

#include <QSysInfo>

#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoBaseDialog::ZegoBaseDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//UI的信号槽
	connect(ui.m_bMin, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);
	connect(ui.m_bMax, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);
	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);
}

ZegoBaseDialog::ZegoBaseDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, bool isPublish2Stream, bool isPublisher, QDialog *parent)
	:
	m_pChatRoom(room),
	m_device(device),
	//m_cbMircoPhoneModel(micModel),
	//m_cbCameraModel(cameraModel),
	m_bCKEnableMic(true),
	m_bCKEnableSpeaker(true),
	m_isPublish2StreamMode(isPublish2Stream),
	m_isPublisher(isPublisher),
	m_lastDialog(lastDialog)
{
	ui.setupUi(this);

	m_pAVSettings = mConfig.GetVideoSettings();
	m_strCurUserID = mConfig.GetUserId();
	m_strCurUserName = mConfig.getUserName();
	m_isUseVerticalCapture = mConfig.GetUseVerticalCapture();

	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigDisconnect, this, &ZegoBaseDialog::OnDisconnect);
	connect(GetAVSignal(), &QZegoAVSignal::sigKickOut, this, &ZegoBaseDialog::OnKickOut);
	
	connect(GetAVSignal(), &QZegoAVSignal::sigSendRoomMessage, this, &ZegoBaseDialog::OnSendRoomMessage);
	connect(GetAVSignal(), &QZegoAVSignal::sigRecvRoomMessage, this, &ZegoBaseDialog::OnRecvRoomMessage);
	connect(GetAVSignal(), &QZegoAVSignal::sigUserUpdate, this, &ZegoBaseDialog::OnUserUpdate);
	connect(m_device, &ZegoDeviceManager::sigDeviceAdded, this, &ZegoBaseDialog::OnDeviceAdded);
	connect(m_device, &ZegoDeviceManager::sigDeviceDeleted, this, &ZegoBaseDialog::OnDeviceDeleted);
	//信号与槽同步执行
	connect(GetAVSignal(), &QZegoAVSignal::sigAuxInput, this, &ZegoBaseDialog::OnAVAuxInput, Qt::DirectConnection);
#ifdef USE_EXTERNAL_SDK
	connect(GetAVSignal(), &QZegoAVSignal::sigSurfaceMergeResult, this, &ZegoBaseDialog::OnSurfaceMergeResult, Qt::DirectConnection);
#endif
	connect(GetAVSignal(), &QZegoAVSignal::sigPreviewSnapshot, this, &ZegoBaseDialog::OnPreviewSnapshot, Qt::DirectConnection);
	connect(GetAVSignal(), &QZegoAVSignal::sigSnapshot, this, &ZegoBaseDialog::OnSnapshot, Qt::DirectConnection);

	//UI的信号槽
	connect(ui.m_bMin, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);
	connect(ui.m_bMax, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);
	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoBaseDialog::OnClickTitleButton);

	connect(ui.m_bSendMessage, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonSendMessage);
	connect(ui.m_bCapture, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonSoundCapture);
	connect(ui.m_bProgMircoPhone, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonMircoPhone);
	connect(ui.m_bSound, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonSound);
	connect(ui.m_bCamera, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonCamera);
	connect(ui.m_bShare, &QPushButton::clicked, this, &ZegoBaseDialog::OnShareLink);
	connect(ui.m_bAux, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonAux);
	connect(ui.m_bFullScreen, &QPushButton::clicked, this, &ZegoBaseDialog::OnButtonShowFullScreen);

#ifdef USE_EXTERNAL_SDK
	connect(&hookDialog, &ZegoMusicHookDialog::sigUseDefaultAux, this, &ZegoBaseDialog::OnUseDefaultAux);
	connect(&hookDialog, &ZegoMusicHookDialog::sigSendMusicAppPath, this, &ZegoBaseDialog::OnGetMusicAppPath);
#endif
	connect(this, &ZegoBaseDialog::sigShowSnapShotImage, this, &ZegoBaseDialog::OnShowSnapShotImage);

	connect(m_device, &ZegoDeviceManager::sigMicCaptureSoundLevelUpdate, this, &ZegoBaseDialog::OnProgChange);

	m_cbMircoPhoneModel = micModel;
	m_cbCameraModel = cameraModel;

	//混音数据参数
	m_pAuxData = NULL;
	m_nAuxDataLen = 0;
	m_nAuxDataPos = 0;

	//去掉标题栏，并且点击任务栏Icon可进行最小化以及恢复
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

	ui.m_edInput->installEventFilter(this);
	ui.m_zoneLiveView_Inner->installEventFilter(this);
	this->installEventFilter(this);

	//初始化网格布局
	gridLayout = new QGridLayout();

	m_pHelper = new FramelessHelper;
	m_pHelper->activateOn(this);
	m_pHelper->setTitleHeight(40);
	m_pHelper->setTitleDoubleClick(this, true);
	m_pHelper->setWidgetMovable(true);
}

ZegoBaseDialog::~ZegoBaseDialog()
{
	m_device->StopMicCaptureMonitor();
	disconnect(m_device, &ZegoDeviceManager::sigMicCaptureSoundLevelUpdate, this, &ZegoBaseDialog::OnProgChange);

	delete m_pHelper;
	m_pHelper = nullptr;
}

//功能函数
void ZegoBaseDialog::initDialog()
{
	if (QSysInfo::windowsVersion() == QSysInfo::WV_XP)
		ui.m_bCapture->setVisible(false);

	initButtonIcon();
	initComboBox();

	//对话框模型初始化
	m_chatModel = new QStandardItemModel(this);
	ui.m_listChat->setModel(m_chatModel);
	ui.m_listChat->horizontalHeader()->setVisible(false);
	ui.m_listChat->verticalHeader()->setVisible(false);
	ui.m_listChat->verticalHeader()->setDefaultSectionSize(26);
	ui.m_listChat->setItemDelegate(new NoFocusFrameDelegate(this));
	ui.m_listChat->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_listChat->setColumnWidth(0, 300);


	//成员列表初始化
	m_memberModel = new QStringListModel(this);
	ui.m_listMember->setModel(m_memberModel); 
	ui.m_listMember->setItemDelegate(new NoFocusFrameDelegate(this));
	ui.m_listMember->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//剩余能用的AVView
	for (int i = MAX_VIEW_COUNT; i >= 0; i--)
		m_avaliableView.push_front(i);
	
	//推流成功前不能开混音、声音采集、分享、停止直播
	SetOperation(false);

	GetDeviceList();

	m_device->StartMicCaptureMonitor();

	int role;
	if (m_isPublisher)
		role = LIVEROOM::ZegoRoomRole::Anchor;
	else
		role = LIVEROOM::ZegoRoomRole::Audience;

	if (!LIVEROOM::LoginRoom(m_pChatRoom->getRoomId().toStdString().c_str(), role, m_pChatRoom->getRoomName().toStdString().c_str()))
	{
		QMessageBox::information(NULL, tr("提示"), tr("进入房间失败"));
	}

}

void ZegoBaseDialog::initButtonIcon()
{
	//imageButton
	ui.m_bMin->setButtonIcon("min");
	ui.m_bMax->setButtonIcon("max");
	ui.m_bClose->setButtonIcon("close");

	//switchButton
	ui.m_bSound->setButtonIcon("sound");
	ui.m_bCamera->setButtonIcon("camera");
}

void ZegoBaseDialog::initComboBox()
{

	m_cbMircoPhoneModel->setStringList(m_MircoPhoneList);

	m_cbMircoPhoneListView = new QListView(this);
	ui.m_cbMircoPhone->setView(m_cbMircoPhoneListView);
	ui.m_cbMircoPhone->setModel(m_cbMircoPhoneModel);
	ui.m_cbMircoPhone->update();
	ui.m_cbMircoPhone->setItemDelegate(new NoFocusFrameDelegate(this));

	m_cbCameraModel->setStringList(m_CameraList);

	m_cbCameraListView = new QListView(this);
	ui.m_cbCamera->setView(m_cbCameraListView);
	ui.m_cbCamera->setModel(m_cbCameraModel);
	ui.m_cbCamera->update();
	ui.m_cbCamera->setItemDelegate(new NoFocusFrameDelegate(this));

	initCameraListView2();

}

void ZegoBaseDialog::GetDeviceList()
{
	m_vecAudioDevice = m_device->GetAudioDeviceList();
	m_vecVideoDevice = m_device->GetVideoDeviceList();

	for (int i = 0; i < m_vecAudioDevice.size(); i++)
	{
		qDebug() << m_vecAudioDevice.at(i).deviceName;
		insertStringListModelItem(m_cbMircoPhoneModel, m_vecAudioDevice.at(i).deviceName, m_cbMircoPhoneModel->rowCount());
	}

	for (int j = 0; j < m_vecVideoDevice.size(); j++)
	{
		qDebug() << m_vecVideoDevice.at(j).deviceName;
		insertStringListModelItem(m_cbCameraModel, m_vecVideoDevice.at(j).deviceName, m_cbCameraModel->rowCount());
	}

	int mic_index = m_device->GetAudioDeviceIndex();
	int camera_index = m_device->GetVideoDeviceIndex();
	int camera_2_index = m_device->GetVideoDevice2Index();

	if (mic_index >= 0)
		ui.m_cbMircoPhone->setCurrentIndex(mic_index);
	if (camera_index >= 0)
		ui.m_cbCamera->setCurrentIndex(camera_index);
	if (camera_2_index >= 0)
	{
		ui.m_cbCamera2->setCurrentIndex(camera_2_index);
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

	QString microphoneId = m_device->GetAudioDeviceId();
	QString cameraId = m_device->GetVideoDeviceId();
	QString cameraId_aux = m_device->GetVideoDeviceId2();

	LIVEROOM::SetAudioDevice(AV::AudioDeviceType::AudioDevice_Input, qtoc(microphoneId));
	LIVEROOM::SetVideoDevice(qtoc(cameraId));
	LIVEROOM::SetVideoDevice(qtoc(cameraId_aux), AV::PUBLISH_CHN_AUX);

	ui.m_bProgMircoPhone->setMyEnabled(m_device->GetMicEnabled());
	ui.m_bProgMircoPhone->setChecked(m_device->GetMicEnabled());
	ui.m_bSound->setChecked(m_device->GetSpeakerEnabled());
	ui.m_bCamera->setChecked(m_device->GetCameraEnabled());
}

void ZegoBaseDialog::insertStringListModelItem(QStringListModel * model, QString name, int size)
{
	if (model == nullptr)
		return;

	int row = size;
	model->insertRows(row, 1);
	QModelIndex index = model->index(row);
	model->setData(index, name);

}

void ZegoBaseDialog::removeStringListModelItem(QStringListModel * model, QString name)
{
	if (model == nullptr)
		return;

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

void ZegoBaseDialog::removeStringListModelItemByIndex(QStringListModel * model, int index)
{
	if (model == nullptr)
		return;

	if (model->rowCount() <= 0)
		return;

	model->removeRow(index);
}

void ZegoBaseDialog::SetOperation(bool state)
{
	//ui.m_cbMircoPhone->setEnabled(state);
	//ui.m_cbCamera->setEnabled(state);
	//ui.m_lbMircoPhone->setEnabled(state);
	//ui.m_lbCamera->setEnabled(state);

	//ui.m_bAux->setEnabled(state);
	//ui.m_bCapture->setEnabled(state);
	ui.m_bShare->setEnabled(state);

}

int ZegoBaseDialog::takeLeastAvaliableViewIndex()
{
	int min = m_avaliableView[0];
	int minIndex = 0;
	for (int i = 1; i < m_avaliableView.size(); i++)
	{
		if (m_avaliableView[i] < min)
		{
			min = m_avaliableView[i];
			minIndex = i;
		}
	}

	m_avaliableView.takeAt(minIndex);
	return min;
}

void ZegoBaseDialog::initAVView(QZegoAVView *view)
{
	view->setMinimumSize(QSize(240, 0));
	view->setStyleSheet(QLatin1String("border: none;\n"
		"background-color: #383838;"));
}

void ZegoBaseDialog::addAVView(int addViewIndex, ZegoDialogType dialogType)
{
	QZegoAVView *newAVView = new QZegoAVView(dialogType);

	initAVView(newAVView);
	newAVView->setViewIndex(addViewIndex);
	AVViews.push_back(newAVView);

	updateViewLayout(AVViews.size());
}

void ZegoBaseDialog::removeAVView(int removeViewIndex)
{
	int viewIndex = -1;
	for (int i = 0; i < AVViews.size(); i++)
	{
		if (AVViews[i]->getViewIndex() == removeViewIndex)
		{
			viewIndex = i;
			break;
		}
	}

	QZegoAVView *popView = AVViews.takeAt(viewIndex);
	popView->deleteLater();

	updateViewLayout(AVViews.size());
}

void ZegoBaseDialog::updateViewLayout(int viewCount)
{
	
	for (int i = 0; i < viewCount; i++)
		gridLayout->removeWidget(AVViews[i]);

	gridLayout->deleteLater();

	gridLayout = new QGridLayout();
	gridLayout->setSpacing(0);
	gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	ui.zoneLiveViewHorizontalLayout->addLayout(gridLayout);

	for (int i = 0; i < viewCount; i++)
	{
		int row, col;
		if (viewCount >= 1 && viewCount <= 4)
		{
			row = i / 2;
			col = i % 2;
		}
		else if (viewCount >= 5 && viewCount <= 9)
		{
			row = i / 3;
			col = i % 3;
		}
		else if (viewCount >= 10 && viewCount <= 12)
		{
			row = i / 4;
			col = i % 4;
		}
		qDebug() << "current row = " << row << " col = " << col;
		gridLayout->addWidget(AVViews[i], row, col, 1, 1);
	    gridLayout->setRowStretch(row, 1);
		gridLayout->setColumnStretch(col, 1);
	}
	
}

void ZegoBaseDialog::FreeAVView(StreamPtr stream)
{
	if (stream == nullptr)
	{
		return;
	}

	int nIndex = stream->getPlayView();

	m_avaliableView.push_front(nIndex);

	//刷新可用的view页面
	update();
}

QString ZegoBaseDialog::encodeStringAddingEscape(QString str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str.at(i) == '!'){
			str.replace(i, 1, "%21");
			i += 2;
		}
		else if (str.at(i) == '*'){
			str.replace(i, 1, "%2A");
			i += 2;
		}
		else if (str.at(i) == '\''){
			str.replace(i, 1, "%27");
			i += 2;
		}
		else if (str.at(i) == '('){
			str.replace(i, 1, "%28");
			i += 2;
		}
		else if (str.at(i) == ')'){
			str.replace(i, 1, "%29");
			i += 2;
		}
		else if (str.at(i) == ';'){
			str.replace(i, 1, "%3B");
			i += 2;
		}
		else if (str.at(i) == ':'){
			str.replace(i, 1, "%3A");
			i += 2;
		}
		else if (str.at(i) == '@'){
			str.replace(i, 1, "%40");
			i += 2;
		}
		else if (str.at(i) == '&'){
			str.replace(i, 1, "%26");
			i += 2;
		}
		else if (str.at(i) == '='){
			str.replace(i, 1, "%3D");
			i += 2;
		}
		else if (str.at(i) == '+'){
			str.replace(i, 1, "%2B");
			i += 2;
		}
		else if (str.at(i) == '$'){
			str.replace(i, 1, "%24");
			i += 2;
		}
		else if (str.at(i) == ','){
			str.replace(i, 1, "%2C");
			i += 2;
		}
		else if (str.at(i) == '/'){
			str.replace(i, 1, "%2F");
			i += 2;
		}
		else if (str.at(i) == '?'){
			str.replace(i, 1, "%2A");
			i += 2;
		}
		else if (str.at(i) == '%'){
			str.replace(i, 1, "%25");
			i += 2;
		}
		else if (str.at(i) == '#'){
			str.replace(i, 1, "%23");
			i += 2;
		}
		else if (str.at(i) == '['){
			str.replace(i, 1, "%5B");
			i += 2;
		}
		else if (str.at(i) == ']'){
			str.replace(i, 1, "%5D");
			i += 2;
		}
	}
	return str;
}

void ZegoBaseDialog::roomMemberAdd(QString userName)
{
	if (m_memberModel == nullptr)
		return;

	insertStringListModelItem(m_memberModel, userName, m_memberModel->rowCount());
	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
}

void ZegoBaseDialog::roomMemberDelete(QString userName)
{
	if (m_memberModel == nullptr)
		return;

	removeStringListModelItem(m_memberModel, userName);
	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
}

void ZegoBaseDialog::BeginAux()
{
	QString filePath = QFileDialog::getOpenFileName(this,
		tr(QString("请选择一个混音文件").toStdString().c_str()),
		"./Resources",
		tr(QString("pcm文件(*.pcm)").toStdString().c_str()));


	if (!filePath.isEmpty())
	{
		FILE* fAux;
		fAux = fopen(filePath.toStdString().c_str(), "rb");

		if (fAux == NULL)
		{
			QMessageBox::warning(this, tr("警告"), tr("文件内容错误: %1").arg(filePath));
			return;
		}

		fseek(fAux, 0, SEEK_END);
		m_nAuxDataLen = ftell(fAux);

		if (m_nAuxDataLen > 0)
		{
			m_pAuxData = new unsigned char[m_nAuxDataLen];
			memset(m_pAuxData, 0, m_nAuxDataLen);
		}
		rewind(fAux);

		int nReadDataLen = fread(m_pAuxData, sizeof(unsigned char), m_nAuxDataLen, fAux);

		fseek(fAux, 0, 0);
		fclose(fAux);

		LIVEROOM::EnableAux(true);
	}
}

void ZegoBaseDialog::EndAux()
{
	LIVEROOM::EnableAux(false);

	ui.m_bAux->setText(tr("开启混音"));
	if (m_pAuxData)
	{
		delete[] m_pAuxData;
		m_pAuxData = NULL;
	}
	m_nAuxDataLen = 0;
	m_nAuxDataPos = 0;
}

void ZegoBaseDialog::setWaterPrint()
{
	QString waterPrintPath = QDir::currentPath();
#ifdef Q_OS_WIN
	waterPrintPath += "/Resources/waterprint/";
	if (this->devicePixelRatio() < 2.0)
	{
		waterPrintPath += "waterprint.png";
	}
	else
	{
		waterPrintPath += "waterprint@2x.png";
	}
#else
	waterPrintPath += "/ZegoLiveDemo.app/Contents/Resources/";
	if (this->devicePixelRatio() < 2.0)
	{
		waterPrintPath += "waterprint.png";
	}
	else
	{
		waterPrintPath += "waterprint@2x.png";
	}
    waterPrintPath = "file:" + waterPrintPath;
#endif
	QImage waterPrint(waterPrintPath);
	qDebug() << "water print path = " << waterPrintPath;

	//标准640 * 360，根据标准对当前分辨率的水印进行等比缩放
	int cx = m_pAVSettings->GetResolution().cx;
	int cy = m_pAVSettings->GetResolution().cy;
	float scaleX = cx * 1.0 / 640;
	float scaleY = cy * 1.0 / 360;

	LIVEROOM::SetPublishWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY));
	LIVEROOM::SetPreviewWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY));
	LIVEROOM::SetWaterMarkImagePath(waterPrintPath.toStdString().c_str());
}

int ZegoBaseDialog::getCameraIndexFromID(const QString& cameraID)
{
	for (int i = 0; i < m_vecVideoDevice.size(); ++i)
	{
		if (m_vecVideoDevice[i].deviceId == cameraID)
			return i;
	}

	return -1;
}

void ZegoBaseDialog::GetOut()
{
	//离开房间时先把混音功能和声卡采集关闭
#ifdef USE_EXTERNAL_SDK
	if (isUseDefaultAux)
		EndAux();
	else
	{
		AUDIOHOOK::StopAudioRecord();
		LIVEROOM::EnableAux(false);
		AUDIOHOOK::UnInitAudioHook();

	}
#else
	EndAux();
#endif

	if (ui.m_bCapture->text() == tr("停止采集"))
		LIVEROOM::EnableMixSystemPlayout(false);

	roomMemberDelete(m_strCurUserName);
	LIVEROOM::LogoutRoom();

	//释放堆内存
	delete m_cbMircoPhoneListView;
	delete m_cbCameraListView;
	delete m_memberModel;
	delete m_chatModel;
	delete gridLayout;
	//指针置为空
	m_cbMircoPhoneListView = nullptr;
	m_cbCameraListView = nullptr;
	m_memberModel = nullptr;
	m_chatModel = nullptr;
	gridLayout = nullptr;
	
}

//SDK回调
void ZegoBaseDialog::OnUserUpdate(QVector<QString> userIDs, QVector<QString> userNames, QVector<int> userFlags, QVector<int> userRoles, unsigned int userCount, LIVEROOM::ZegoUserUpdateType type)
{
	qDebug() << "onUserUpdate!";

	//全量更新
	if (type == LIVEROOM::ZegoUserUpdateType::UPDATE_TOTAL){
		//removeAll
		m_memberModel->removeRows(0, m_memberModel->rowCount());

		insertStringListModelItem(m_memberModel, m_strCurUserName, 0);
		for (int i = 0; i < userCount; i++)
		{
			insertStringListModelItem(m_memberModel, userNames[i], m_memberModel->rowCount());
		}
	}
	//增量更新
	else
	{

		for (int i = 0; i < userCount; i++)
		{

			if (userFlags[i] == LIVEROOM::USER_ADDED)
				insertStringListModelItem(m_memberModel, userNames[i], m_memberModel->rowCount());
			else
				removeStringListModelItem(m_memberModel, userNames[i]);
		}
	}

	ui.m_tabCommonAndUserList->setTabText(1, QString(tr("成员(%1)").arg(m_memberModel->rowCount())));
	ui.m_listMember->update();
}

void ZegoBaseDialog::OnDisconnect(int errorCode, const QString& roomId)
{
	if (m_pChatRoom->getRoomId() == roomId)
	{
		QMessageBox::information(NULL, tr("提示"), tr("您已掉线"));
		OnClose();
	}
}

void ZegoBaseDialog::OnKickOut(int reason, const QString& roomId)
{
	if (m_pChatRoom->getRoomId() == roomId)
	{
		QMessageBox::information(NULL, tr("提示"), tr("您已被踢出房间"));
		OnClose();
	}
}

/*void ZegoBaseDialog::OnPlayQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	AVViews[nIndex]->setCurrentQuality(quality);

}

void ZegoBaseDialog::OnPublishQualityUpdate(const QString& streamId, int quality, double capFPS, double videoFPS, double videoKBS, double audioKBS, int rtt, int pktLostRate)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	AVViews[nIndex]->setCurrentQuality(quality);
}*/

void ZegoBaseDialog::OnAVAuxInput(unsigned char *pData, int *pDataLen, int pDataLenValue, int *pSampleRate, int *pNumChannels)
{
#ifdef USE_EXTERNAL_SDK
	if (isUseDefaultAux)
	{
		if (m_pAuxData != nullptr && (*pDataLen < m_nAuxDataLen))
		{
			*pSampleRate = 44100;
			*pNumChannels = 2;
            
			if (m_nAuxDataPos + *pDataLen > m_nAuxDataLen)
			{
				m_nAuxDataPos = 0;
			}
			//按照SDK指定的帧长度进行拷贝
            int nCopyLen = *pDataLen;
			memcpy(pData, m_pAuxData + m_nAuxDataPos, nCopyLen);

			m_nAuxDataPos += *pDataLen;


		}
		else
		{
			*pDataLen = 0;
		}
	}
	else
	{
		AUDIOHOOK::GetAUXData(pData, pDataLen, pSampleRate, pNumChannels);
	}
#else
	if (m_pAuxData != nullptr && (*pDataLen < m_nAuxDataLen))
	{
		*pSampleRate = 44100;
		*pNumChannels = 2;

		if (m_nAuxDataPos + *pDataLen > m_nAuxDataLen)
		{
			m_nAuxDataPos = 0;
		}
		//按照SDK指定的帧长度进行拷贝
		int nCopyLen = *pDataLen;
		memcpy(pData, m_pAuxData + m_nAuxDataPos, nCopyLen);

		m_nAuxDataPos += *pDataLen;


	}
	else
	{
		*pDataLen = 0;
	}
#endif
}

void ZegoBaseDialog::OnSendRoomMessage(int errorCode, const QString& roomID, int sendSeq, unsigned long long messageId)
{
	if (errorCode != 0)
	{
		QMessageBox::warning(NULL, tr("警告"), tr("消息发送失败，错误码: %1").arg(errorCode));
		return;
	}

	qDebug() << "message send success";
}

void ZegoBaseDialog::OnRecvRoomMessage(const QString& roomId, QVector<RoomMsgPtr> vRoomMsgList)
{
	for (auto& roomMsg : vRoomMsgList)
	{
		QString strTmpContent;
		strTmpContent = QString("%1").arg(roomMsg->getContent());
		
		QStandardItem *item = new QStandardItem;
		m_chatModel->appendRow(item);
		QModelIndex index = m_chatModel->indexFromItem(item);

		ZegoRoomMessageLabel *chatContent = new ZegoRoomMessageLabel;
		chatContent->setTextContent(roomMsg->getUserName(), strTmpContent);

		ui.m_listChat->setIndexWidget(index, chatContent);
		if (chatContent->getHeightNum() > 1)
			ui.m_listChat->resizeRowToContents(m_chatModel->rowCount() - 1);

		//每次接受消息均显示最后一条
		ui.m_listChat->scrollToBottom();

	}
}

void ZegoBaseDialog::OnDeviceAdded(int device_type, QString device_name)
{
	if (device_type == TYPE_AUDIO)
	{
		ui.m_cbMircoPhone->blockSignals(true);
		insertStringListModelItem(m_cbMircoPhoneModel, device_name, m_cbMircoPhoneModel->rowCount());
		ui.m_cbMircoPhone->blockSignals(false);

		m_vecAudioDevice = m_device->GetAudioDeviceList();

		if (m_vecAudioDevice.size() == 1)
		{
			LIVEROOM::SetAudioDevice(AV::AudioDeviceType::AudioDevice_Input, qtoc(m_device->GetAudioDeviceId()));
			m_pAVSettings->SetMicrophoneId(m_device->GetAudioDeviceId());
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
			QString cameraId = m_device->GetVideoDeviceId();

			m_pAVSettings->SetCameraId(cameraId);
			ui.m_cbCamera->setCurrentIndexWithoutSignal(0);
			ui.m_cbCamera2->setModel(new QStringListModel(this));

			
			//if (m_isExternalCapture)
				//m_input->SetCameraDeviceID(cameraId.toStdString());
			//else
			//{
			LIVEROOM::SetVideoDevice(qtoc(cameraId));
			LIVEROOM::StartPreview();
			//}

		}
		else if (m_vecVideoDevice.size() == 2 && m_isPublish2StreamMode)
		{
			QString cameraId = m_device->GetVideoDeviceId();
			QString camera2Id = m_device->GetVideoDeviceId2();

			LIVEROOM::SetVideoDevice(qtoc(camera2Id), ZEGO::AV::PUBLISH_CHN_AUX);

			m_pAVSettings->SetCameraId2(camera2Id);

			ui.m_cbCamera2->blockSignals(true);
			ui.m_cbCamera2->setModel(m_cbCameraModel);
			ui.m_cbCamera2->setCurrentIndex(1);
			ui.m_cbCamera2->blockSignals(false);

			ui.m_cbCamera->setCurrentIndexWithoutSignal(0);
			m_pAVSettings->SetCameraId(cameraId);

			LIVEROOM::EnableCamera(true, ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::StartPreview(ZEGO::AV::PUBLISH_CHN_AUX);


		}
	}

	update();

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";
}

void ZegoBaseDialog::OnDeviceDeleted(int device_type, int index)
{
	if (device_type == TYPE_AUDIO)
	{
		ui.m_cbMircoPhone->blockSignals(true);
		removeStringListModelItemByIndex(m_cbMircoPhoneModel, index);
		ui.m_cbMircoPhone->blockSignals(false);

		m_vecAudioDevice = m_device->GetAudioDeviceList();

		QString microphoneId = m_device->GetAudioDeviceId();
		m_pAVSettings->SetMicrophoneId(microphoneId);
		if (microphoneId.isEmpty())
			LIVEROOM::SetAudioDevice(AV::AudioDeviceType::AudioDevice_Input, nullptr);
		else
			LIVEROOM::SetAudioDevice(AV::AudioDeviceType::AudioDevice_Input, qtoc(microphoneId));

		int curIndex = m_device->GetAudioDeviceIndex();
		if (curIndex >= 0)
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

		QString cameraId = m_device->GetVideoDeviceId();
		QString cameraId2 = m_device->GetVideoDeviceId2();

		if (m_vecVideoDevice.size() == 0)
		{
			LIVEROOM::StopPreview();
			LIVEROOM::SetVideoDevice(nullptr);
		}
		else if (m_vecVideoDevice.size() == 1)
		{
			ui.m_cbCamera2->blockSignals(true);
			ui.m_cbCamera2->setModel(new QStringListModel(this));
			ui.m_cbCamera2->blockSignals(false);

			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());

			//剩一个设备的时候，摄像头2必定不存在
			LIVEROOM::EnableCamera(false, ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::StopPreview(ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::SetVideoDevice(nullptr, ZEGO::AV::PUBLISH_CHN_AUX);
			//此时是摄像头2设置到摄像头1的位置上的情况
			if (cameraId != m_pAVSettings->GetCameraId())
			{
				//if (m_isExternalCapture)
					//m_input->SetCameraDeviceID(cameraId.toStdString());
				//else
				LIVEROOM::SetVideoDevice(qtoc(cameraId));
			}
		
		}
		else
		{
			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
			ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());

			if (cameraId != m_pAVSettings->GetCameraId())
			{
				//if (m_isExternalCapture)
					//m_input->SetCameraDeviceID(cameraId.toStdString());
				//else
				LIVEROOM::SetVideoDevice(qtoc(cameraId));
			}

			if (cameraId2 != m_pAVSettings->GetCameraId2() && m_isPublish2StreamMode)
			{
				LIVEROOM::SetVideoDevice(qtoc(cameraId2), ZEGO::AV::PUBLISH_CHN_AUX);
			}
		}

		m_pAVSettings->SetCameraId(m_device->GetVideoDeviceId());
		m_pAVSettings->SetCameraId2(m_device->GetVideoDeviceId2());
	}

	update();

	qDebug() << "------------------------------------------------------";
	qDebug() << "current mic id: " << m_device->GetAudioDeviceId();
	qDebug() << "current mic index:" << m_device->GetAudioDeviceIndex();
	qDebug() << "current camera id: " << m_device->GetVideoDeviceIndex();
	qDebug() << "current camera index: " << m_device->GetVideoDeviceId();
	qDebug() << "current camera2 id: " << m_device->GetVideoDeviceId2();
	qDebug() << "current camera2 index: " << m_device->GetVideoDevice2Index();
	qDebug() << "------------------------------------------------------";

}

#ifdef USE_EXTERNAL_SDK
void ZegoBaseDialog::OnSurfaceMergeResult(unsigned char *surfaceMergeData, int datalength)
{
	if (m_takeSnapShot)
	{
		//同一时刻只允许一个线程进入该代码段
		m_takeSnapShot = false;
		m_mutex.lock();
		m_image = new unsigned char[datalength];
		memcpy(m_image, surfaceMergeData, datalength);
		QImage *image = new QImage(m_image, m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy, QImage::Format_RGB32);
		emit sigShowSnapShotImage(image);
		m_mutex.unlock();
	}
}
#endif

void ZegoBaseDialog::OnPreviewSnapshot(void *pImage)
{
	QImage *image;

#ifdef Q_OS_WIN
	image = new QImage;
	QPixmap pixmap = qt_pixmapFromWinHBITMAP((HBITMAP)pImage, 0);
	*image = pixmap.toImage();
#else
	image = CGImageToQImage(pImage);
#endif
	//发送信号切线程，不能阻塞当前线程
	emit sigShowSnapShotImage(image);
}

void ZegoBaseDialog::OnSnapshot(void *pImage, const QString &streamID)
{
	QImage *image;

#ifdef Q_OS_WIN
	image = new QImage;
	QPixmap pixmap = qt_pixmapFromWinHBITMAP((HBITMAP)pImage, 0);
	*image = pixmap.toImage();
#else
	image = CGImageToQImage(pImage);
#endif

	//发送信号切线程，不能阻塞当前线程
	emit sigShowSnapShotImage(image);
}
//UI回调
void ZegoBaseDialog::OnClickTitleButton()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());

	if (pButton == ui.m_bMin)
	{
		this->showMinimized();
	}
	else if (pButton == ui.m_bClose)
	{
		this->close();
	}
	else if (pButton == ui.m_bMax)
	{
		if (isMax)
		{
			this->showNormal();
			isMax = false;
			ui.m_bMax->setButtonIcon("max");
		}
		else
		{
			this->showMaximized();
			isMax = true;
			ui.m_bMax->setButtonIcon("max_re");
		}
	}
}

void ZegoBaseDialog::OnClose()
{
	this->close();
}

void ZegoBaseDialog::OnButtonSendMessage()
{
	QString strChat;
	strChat = ui.m_edInput->toPlainText();

	m_strLastSendMsg = strChat;
	m_strLastSendMsg = m_strLastSendMsg.trimmed();

	if (!m_strLastSendMsg.isEmpty())
		LIVEROOM::SendRoomMessage(ROOM::ZegoMessageType::Text, ROOM::ZegoMessageCategory::Chat, ROOM::ZegoMessagePriority::Default, m_strLastSendMsg.toStdString().c_str());

	ui.m_edInput->setText("");

	QString strTmpContent;
	strTmpContent = QString("%1").arg(m_strLastSendMsg);

	QStandardItem *item = new QStandardItem;
	m_chatModel->appendRow(item);
	QModelIndex index = m_chatModel->indexFromItem(item);

	ZegoRoomMessageLabel *chatContent = new ZegoRoomMessageLabel;
	chatContent->setTextContent("我", strTmpContent);

	ui.m_listChat->setIndexWidget(index, chatContent);
	if (chatContent->getHeightNum() > 1)
		ui.m_listChat->resizeRowToContents(m_chatModel->rowCount() - 1);

	//每次发送消息均显示最后一条
	ui.m_listChat->scrollToBottom();
	m_strLastSendMsg.clear();

}

void ZegoBaseDialog::OnButtonSoundCapture()
{
	if (ui.m_bCapture->text() == tr("声卡采集"))
	{
#ifdef Q_OS_WIN
		LIVEROOM::EnableMixSystemPlayout(true);
#endif
		ui.m_bCapture->setText(tr("停止采集"));
	}
	else
	{
#ifdef Q_OS_WIN
		LIVEROOM::EnableMixSystemPlayout(false);
#endif
		ui.m_bCapture->setText(tr("声卡采集"));
	}
}

void ZegoBaseDialog::OnButtonMircoPhone()
{


	if (ui.m_bProgMircoPhone->isChecked())
	{
		m_bCKEnableMic = true;
		ui.m_bProgMircoPhone->setMyEnabled(true);
		
	}
	else
	{
		m_bCKEnableMic = false;
		
		ui.m_bProgMircoPhone->setMyEnabled(false);
		ui.m_bProgMircoPhone->update();
	}

	//使用麦克风
	m_device->SetMicEnabled(m_bCKEnableMic);
}

void ZegoBaseDialog::OnButtonSound()
{


	if (ui.m_bSound->isChecked())
	{

		m_bCKEnableSpeaker = true;
	}
	else
	{

		m_bCKEnableSpeaker = false;
	}

	//使用扬声器
	m_device->SetSpeakerEnabled(m_bCKEnableSpeaker);

}

void ZegoBaseDialog::OnButtonCamera()
{
	/*if (ui.m_bCamera->isChecked())
	{
		LIVEROOM::EnableCamera(true);
		LIVEROOM::StartPreview();
		if (m_isPublish2StreamMode)
		{
			LIVEROOM::EnableCamera(true, AV::PUBLISH_CHN_AUX);
			LIVEROOM::StartPreview(AV::PUBLISH_CHN_AUX);
		}
	}
	else
	{
		LIVEROOM::StopPreview();
		LIVEROOM::EnableCamera(false);
		if (m_isPublish2StreamMode)
		{
			LIVEROOM::StopPreview(AV::PUBLISH_CHN_AUX);
			LIVEROOM::EnableCamera(false, AV::PUBLISH_CHN_AUX);
		}
		update();
	}*/
	bool isUseCameras;
	if (ui.m_bCamera->isChecked())
	{
		isUseCameras = true;
	}
	else
	{
		isUseCameras = false;
	}

	m_device->SetCameraEnabled(isUseCameras);
}

void ZegoBaseDialog::OnProgChange(float soundlevel)
{
	ui.m_bProgMircoPhone->setProgValue(soundlevel);
	ui.m_bProgMircoPhone->update();
}

void ZegoBaseDialog::OnShareLink()
{

	QString encodeHls = encodeStringAddingEscape(sharedHlsUrl);
	QString encodeRtmp = encodeStringAddingEscape(sharedRtmpUrl);
	QString encodeID = encodeStringAddingEscape(m_pChatRoom->getRoomId());
	QString encodeStreamID = encodeStringAddingEscape(m_anchorStreamInfo->getStreamId());

	QString link("http://www.zego.im/share/index2?video=" + encodeHls + "&rtmp=" + encodeRtmp + "&id=" + encodeID + "&stream=" + encodeStreamID);
	ZegoShareDialog share(link);
	share.exec();

}

void ZegoBaseDialog::OnButtonShowFullScreen()
{
	//直播窗口总在最顶层
	ui.m_zoneLiveView_Inner->setWindowFlags(Qt::Dialog);
	ui.m_zoneLiveView_Inner->showFullScreen();
	m_isLiveFullScreen = true;
}

void ZegoBaseDialog::OnSnapshotPreview()
{
	if (m_pAVSettings->GetSurfaceMerge())
	{
		m_takeSnapShot = true;
	}
	else
	{
		LIVEROOM::TakeSnapshotPreview();
	}
}

void ZegoBaseDialog::OnSnapshotWithStreamID(const QString &streamID)
{
	LIVEROOM::TakeSnapshot(streamID.toStdString().c_str());
}

void ZegoBaseDialog::OnShowSnapShotImage(QImage *imageData)
{
	ZegoImageShowDialog imageShowDialog(imageData, imageData->width(), imageData->height(), m_pAVSettings);
	imageShowDialog.initDialog();
	imageShowDialog.exec();

	if (m_image)
	{
		delete[] m_image;
		m_image = nullptr;
	}

}

void ZegoBaseDialog::OnUseDefaultAux(bool state)
{
	BeginAux();
	isUseDefaultAux = state;
	ui.m_bAux->setEnabled(true);
	ui.m_bAux->setText(tr("关闭混音"));
}

#ifdef USE_EXTERNAL_SDK
void ZegoBaseDialog::OnGetMusicAppPath(QString exePath)
{

	QString dllPath = QDir::currentPath() + "/MusicHook/ZegoMusicAudio.dll";

	const char*  exepath;
	QByteArray exeBA = exePath.toLocal8Bit();
	exepath = exeBA.data();

	const char*  dllpath;
	QByteArray dllBA = dllPath.toLocal8Bit();
	dllpath = dllBA.data();

	AUDIOHOOK::InitAuidoHook();
	if (!AUDIOHOOK::StartAudioHook(exepath, dllpath))
	{
		QMessageBox::warning(NULL, tr("警告"), tr("路径格式错误"));
		ui.m_bAux->setEnabled(true);
		ui.m_bAux->setText(tr("开启混音"));
		return;
	}

	AUDIOHOOK::StartAudioRecord();
	LIVEROOM::EnableAux(true);

	ui.m_bAux->setEnabled(true);
	ui.m_bAux->setText(tr("关闭混音"));
}
#endif

void ZegoBaseDialog::OnButtonAux()
{
	if (ui.m_bAux->text() == tr("开启混音"))
	{

		ui.m_bAux->setText(tr("开启中..."));
		ui.m_bAux->setEnabled(false);

#ifdef Q_OS_WIN
	#ifdef USE_EXTERNAL_SDK

		hookDialog.searchMusicAppFromReg();
		if (hookDialog.exec() == QDialog::Rejected)
		{
			ui.m_bAux->setEnabled(true);
			ui.m_bAux->setText(tr("开启混音"));
		}
	#else
		BeginAux();
		isUseDefaultAux = true;
		ui.m_bAux->setEnabled(true);
		ui.m_bAux->setText(tr("关闭混音"));
	#endif //USE_EXTERNAL_SDK

#elif Q_OS_MAC

		BeginAux();
		ui.m_bAux->setEnabled(true);
		ui.m_bAux->setText(tr("关闭混音"));
#endif
	}
	else
	{
		ui.m_bAux->setText(tr("关闭中..."));
		ui.m_bAux->setEnabled(false);

#ifdef USE_EXTERNAL_SDK
		if (isUseDefaultAux)
		{
			EndAux();

		}
		else
		{
			AUDIOHOOK::StopAudioRecord();
			LIVEROOM::EnableAux(false);
			AUDIOHOOK::UnInitAudioHook();

		}
#else
		EndAux();
#endif
		ui.m_bAux->setEnabled(true);
		ui.m_bAux->setText(tr("开启混音"));
	}
}

void ZegoBaseDialog::OnSwitchAudioDevice(int id)
{
	if (id < 0)
		return;

	if (id < m_vecAudioDevice.size())
	{
		m_device->SetMicrophoneIdByIndex(id);
		QString microphoneId = m_device->GetAudioDeviceId();

		LIVEROOM::SetAudioDevice(AV::AudioDevice_Input, qtoc(microphoneId));
		m_pAVSettings->SetMicrophoneId(microphoneId);
		ui.m_cbMircoPhone->setCurrentIndexWithoutSignal(id);

		//切换设备之后，如果当前设备被关闭，则开启
		if (!ui.m_bProgMircoPhone->isChecked())
			ui.m_bProgMircoPhone->setChecked(true);

		update();
	}
}

void ZegoBaseDialog::OnSwitchVideoDevice(int id)
{
	if (id < 0)
		return;

	if (id < m_vecVideoDevice.size())
	{
		int og_camera_index = m_device->GetVideoDeviceIndex();
		QDeviceState state = m_device->SetCameraIdByIndex(id);
		//若摄像头1需要选取的摄像头已被摄像头2选取，则交换摄像头
		if (state == STATE_SWAP)
		{
			//先关闭所有正在使用的摄像头，避免交换时先后次序不同导致的抢占问题
			LIVEROOM::StopPreview();
			LIVEROOM::StopPreview(ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::EnableCamera(false);
			LIVEROOM::EnableCamera(false, ZEGO::AV::PUBLISH_CHN_AUX);

			m_pAVSettings->SetCameraId2(m_device->GetVideoDeviceId2());

			if (og_camera_index < 0)
				return;

			ui.m_cbCamera2->setCurrentIndexWithoutSignal(og_camera_index);

			LIVEROOM::SetVideoDevice(qtoc(m_device->GetVideoDeviceId2()), ZEGO::AV::PUBLISH_CHN_AUX);
		}

	    LIVEROOM::SetVideoDevice(qtoc(m_device->GetVideoDeviceId()));
		m_pAVSettings->SetCameraId(qtoc(m_device->GetVideoDeviceId()));

#ifdef USE_EXTERNAL_SDK
		if (mBase.GetUseSurfaceMerge())
		{
			SurfaceMergeController::getInstance().setSurfaceCameraId(m_device->GetVideoDeviceId());
			SurfaceMergeController::getInstance().startSurfaceMerge();
		}
#endif
		update();

		LIVEROOM::EnableCamera(true);
		if (m_isPublish2StreamMode)
			LIVEROOM::EnableCamera(true, ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::StartPreview();
		if (m_isPublish2StreamMode)
			LIVEROOM::StartPreview(ZEGO::AV::PUBLISH_CHN_AUX);

		//切换设备之后，如果当前设备被关闭，则开启
		if (!ui.m_bCamera->isChecked())
			ui.m_bCamera->setChecked(true);
		qDebug() << "[MoreAnchorDialog::VideoDevice_Changed_1]: current video device_main : " << m_pAVSettings->GetCameraId() << " video device_aux : " << m_pAVSettings->GetCameraId2();
	}
}

void ZegoBaseDialog::OnSwitchVideoDevice2(int id)
{
	if (id < 0)
		return;

	if (id < m_vecVideoDevice.size())
	{
		int og_camera_2_index = m_device->GetVideoDevice2Index();
		QDeviceState state = m_device->SetCameraId2ByIndex(id);
		//若摄像头1需要选取的摄像头已被摄像头2选取，则交换摄像头
		if (state == STATE_SWAP)
		{
			//先关闭所有正在使用的摄像头，避免交换时先后次序不同导致的抢占问题
			LIVEROOM::StopPreview();
			LIVEROOM::StopPreview(ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::EnableCamera(false);
			LIVEROOM::EnableCamera(false, ZEGO::AV::PUBLISH_CHN_AUX);

			m_pAVSettings->SetCameraId(m_device->GetVideoDeviceId());

			//将摄像头1设置为原来摄像头2的位置去
			ui.m_cbCamera->setCurrentIndexWithoutSignal(og_camera_2_index);

			LIVEROOM::SetVideoDevice(qtoc(m_device->GetVideoDeviceId()));
		}

		LIVEROOM::SetVideoDevice(qtoc(m_device->GetVideoDeviceId2()), ZEGO::AV::PUBLISH_CHN_AUX);
		m_pAVSettings->SetCameraId2(qtoc(m_device->GetVideoDeviceId2()));

		update();

		LIVEROOM::EnableCamera(true);
		LIVEROOM::EnableCamera(true, ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::StartPreview();
		LIVEROOM::StartPreview(ZEGO::AV::PUBLISH_CHN_AUX);

		//切换设备之后，如果当前设备被关闭，则开启
		if (!ui.m_bCamera->isChecked())
			ui.m_bCamera->setChecked(true);
		qDebug() << "[MoreAnchorDialog::VideoDevice_Changed_2]: current video device_main : " << m_pAVSettings->GetCameraId() << " video device_aux : " << m_pAVSettings->GetCameraId2();
	}
}

void ZegoBaseDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (isMax)
	{
		isMax = false;
		ui.m_bMax->setButtonIcon("max");
	}
	else
	{
		isMax = true;
		ui.m_bMax->setButtonIcon("max_re");
	}

}

void ZegoBaseDialog::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);
	this->setAttribute(Qt::WA_Mapped);
}

void ZegoBaseDialog::closeEvent(QCloseEvent *e)
{
	QDialog::closeEvent(e);
	GetOut();
	
	emit sigSaveVideoSettings(m_pAVSettings);
	m_lastDialog->show();
}

bool ZegoBaseDialog::eventFilter(QObject *target, QEvent *event)
{
	if (target == ui.m_edInput)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Return && (keyEvent->modifiers() & Qt::ControlModifier))
			{
				ui.m_edInput->insertPlainText("\n");
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				OnButtonSendMessage();
				return true;
			}
		}
	}
	else if (target == ui.m_zoneLiveView_Inner)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
			if (keyEvent->key() == Qt::Key_Escape && m_isLiveFullScreen)
			{
				//qDebug() << "clicl esc";
				//ui.m_zoneLiveView_Inner->setParent(ui.m_zoneLiveView);
				ui.m_zoneLiveView_Inner->setWindowFlags(Qt::SubWindow);
				ui.m_zoneLiveView_Inner->showNormal();
				ui.horizontalLayout_ForAVView->addWidget(ui.m_zoneLiveView_Inner);
				m_isLiveFullScreen = false;
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Escape && !m_isLiveFullScreen)
			{
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
