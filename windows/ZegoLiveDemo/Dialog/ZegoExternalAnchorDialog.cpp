#include "ZegoExternalAnchorDialog.h"
#include "Signal/ZegoSDKSignal.h"
#include "Base/IncludeZegoLiveRoomApi.h"

//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoExternalAnchorDialog::ZegoExternalAnchorDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{
	//ui.setupUi(this);

}

ZegoExternalAnchorDialog::ZegoExternalAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, true, parent)
{
	//ui.setupUi(this);
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoExternalAnchorDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoExternalAnchorDialog::OnPublishStateUpdate);
	
	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoExternalAnchorDialog::OnButtonSwitchPublish);

	
	m_render_timer = new QTimer;
	connect(m_render_timer, &QTimer::timeout, this, &ZegoExternalAnchorDialog::OnTimerRefreshView);
	
	m_input = new ZegoInputManager;
}

ZegoExternalAnchorDialog::~ZegoExternalAnchorDialog()
{
	delete m_input;
	m_input = nullptr;

	delete m_render_timer;
	m_render_timer = nullptr;
}

//功能函数
void ZegoExternalAnchorDialog::initDialog()
{
	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("单主播模式(外部采集&渲染)")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	//不需要第二个摄像头
	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	//在主播端，请求连麦的按钮变为直播开关
	ui.m_bRequestJoinLive->setText(tr("停止直播"));

	ZegoBaseDialog::initDialog();

	disconnect(m_device, &ZegoDeviceManager::sigDeviceAdded, this, &ZegoBaseDialog::OnDeviceAdded);
	disconnect(m_device, &ZegoDeviceManager::sigDeviceDeleted, this, &ZegoBaseDialog::OnDeviceDeleted);
	connect(m_device, &ZegoDeviceManager::sigDeviceAdded, this, &ZegoExternalAnchorDialog::OnDeviceAdded);
	connect(m_device, &ZegoDeviceManager::sigDeviceDeleted, this, &ZegoExternalAnchorDialog::OnDeviceDeleted);

	disconnect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice(int)));
	disconnect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice(int)));

	connect(ui.m_cbMircoPhone, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchAudioDevice_External(int)));
	connect(ui.m_cbCamera, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice_External(int)));


   //绑定回调数据
	m_input->Init();

	//启动外部音频采集
	m_input->StartAudioCapture();

	//以定时器开启外部渲染，根据一定频率(30fps)刷新view
	m_render_timer->start(1000 / 30);
	
}

void ZegoExternalAnchorDialog::StartPublishStream()
{
	QString strStreamId;
#ifdef Q_OS_WIN
	strStreamId = QString("s-windows-%1").arg(m_strCurUserID);
#else
	strStreamId = QString("s-mac-%1").arg(m_strCurUserID);
#endif
	m_strPublishStreamID = strStreamId;

	StreamPtr pPublishStream(new QZegoStreamModel(m_strPublishStreamID, m_strCurUserID, m_strCurUserName, "", true));

	m_pChatRoom->addStream(pPublishStream);

	//推流前调用双声道
	LIVEROOM::SetAudioChannelCount(2);

	if (m_avaliableView.size() > 0)
	{

		int nIndex = takeLeastAvaliableViewIndex();
		pPublishStream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MoreAnchor);
		AVViews.last()->setCurUser();
		connect(AVViews.last(), &QZegoAVView::sigSnapShotPreviewOnMoreAnchor, this, &ZegoBaseDialog::OnSnapshotPreview);

		LIVEROOM::SetVideoFPS(m_pAVSettings->GetFps());
		LIVEROOM::SetVideoBitrate(m_pAVSettings->GetBitrate());

		m_input->SetCameraFPS(m_pAVSettings->GetFps());
		if (!m_isUseVerticalCapture)
		{
			m_input->SetCameraResolution(QSize(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy));
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
		}
		else
		{
			m_input->SetCameraResolution(QSize(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx));
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx);
		}
		m_input->SetCameraDeviceID(m_device->GetVideoDeviceId().toStdString());
	}

		QString streamID = m_strPublishStreamID;
		m_anchorStreamInfo = pPublishStream;
		AVViews.last()->setViewStreamID(streamID);
		setWaterPrint();
		qDebug() << "start publishing!";
	
		LIVEROOM::StartPublishing(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_JOIN_PUBLISH, "");
		
		m_bIsPublishing = true;
	
}

void ZegoExternalAnchorDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0){ return; }

	qDebug() << "stop publish view index = " << m_anchorStreamInfo->getPlayView();
	removeAVView(m_anchorStreamInfo->getPlayView());
	LIVEROOM::StopPublishing();

	m_input->SetCameraDeviceID("");
	m_input->StopCameraCapture();

	m_bIsPublishing = false;
	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
	m_strPublishStreamID = "";

}

bool ZegoExternalAnchorDialog::praseJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);

	sharedHlsUrl = hlsUrl.toString();
	sharedRtmpUrl = rtmpUrl.toString();

	return true;
}

void ZegoExternalAnchorDialog::addAVView(int addViewIndex, ZegoDialogType dialogType)
{
	ZegoBaseDialog::addAVView(addViewIndex, dialogType);

	QZegoAVView *view = AVViews.last();
	view->SetOnGetFrameDelegate(std::bind(&ZegoInputManager::GetCamFrame, m_input));
	view->SetUseExternalRender(true);
	
}

void ZegoExternalAnchorDialog::removeAVView(int removeViewIndex)
{
	if (removeViewIndex >= AVViews.size())
		return;

	QZegoAVView *view = AVViews[removeViewIndex];
	view->SetOnGetFrameDelegate(nullptr);
	view->SetUseExternalRender(true);
	ZegoBaseDialog::removeAVView(removeViewIndex);
}

void ZegoExternalAnchorDialog::GetOut()
{
	
	m_input->StopAudioCapture();
	m_input->StopCameraCapture();
	m_input->Uninit();
	m_render_timer->stop();
	for (auto& stream : m_pChatRoom->getStreamList())
	{
		if (stream != nullptr){
			if (stream->isCurUserCreated())
			{
				StopPublishStream(stream->getStreamId());
			}
		}
	}

	ZegoBaseDialog::GetOut();
}


//SDK回调
void ZegoExternalAnchorDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
{
	qDebug() << "Login Room!";
	if (errorCode != 0)
	{
		QMessageBox::information(NULL, tr("提示"), tr("登陆房间失败,错误码: %1").arg(errorCode));
        OnClose();
		return;
	}

	//加入房间列表
	roomMemberAdd(m_strCurUserName);

    StartPublishStream();
}

void ZegoExternalAnchorDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	
	if (stateCode == 0)
	{
		qDebug() << "Publish success!";
		if (streamInfo != nullptr)
		{
			
			if(streamInfo->m_vecHlsUrls.size() > 0)
			    sharedHlsUrl = streamInfo->m_vecHlsUrls[0];
			if(streamInfo->m_vecRtmpUrls.size() > 0)
			    sharedRtmpUrl = streamInfo->m_vecRtmpUrls[0];
		}

		//在连麦模式下，推流成功时需将流媒体地址存到流附加信息中
		if (sharedHlsUrl.size() > 0 && sharedRtmpUrl.size() > 0)
		{
			//封装存放分享地址的json对象
			QMap<QString, QString> mapUrls = QMap<QString, QString>();

			mapUrls.insert(m_FirstAnchor, "true");
			mapUrls.insert(m_HlsKey, sharedHlsUrl);
			mapUrls.insert(m_RtmpKey, sharedRtmpUrl);

			QVariantMap vMap;
			QMapIterator<QString, QString> it(mapUrls);
			while (it.hasNext())
			{
				it.next();
				vMap.insert(it.key(), it.value());
			}

			QJsonDocument doc = QJsonDocument::fromVariant(vMap);
			QByteArray jba = doc.toJson();
			QString jsonString = QString(jba);
			jsonString = jsonString.simplified();
			//设置流附加消息，将混流信息传入
			LIVEROOM::SetPublishStreamExtraInfo(jsonString.toStdString().c_str());
		}
		
		SetOperation(true);
		ui.m_bRequestJoinLive->setText(tr("停止直播"));
		ui.m_bRequestJoinLive->setEnabled(true);

		//推流成功后启动计时器监听麦克风音量
		timer->start(200);

	}
	else
	{
		QMessageBox::warning(NULL, tr("推流失败"), tr("错误码: %1").arg(stateCode));
		ui.m_bRequestJoinLive->setText(tr("开始直播"));
		ui.m_bRequestJoinLive->setEnabled(true);
		EndAux();
		// 停止预览, 回收view
		removeAVView(streamInfo->getPlayView());
		LIVEROOM::StopPreview();
		LIVEROOM::SetPreviewView(nullptr);
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		FreeAVView(pStream);
	}
}

//UI回调
void ZegoExternalAnchorDialog::OnButtonSwitchPublish()
{
	//当前按钮文本为“开始直播”
	if (ui.m_bRequestJoinLive->text() == tr("开始直播"))
	{
		ui.m_bRequestJoinLive->setText(tr("开启中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		//开始推流
		StartPublishStream();

	}
	//当前按钮文本为“停止直播”
	else
	{
		ui.m_bRequestJoinLive->setText(tr("停止中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		StopPublishStream(m_strPublishStreamID);

		if (timer->isActive())
			timer->stop();
		ui.m_bProgMircoPhone->setMyEnabled(false);
		ui.m_bProgMircoPhone->update();

		if (ui.m_bAux->text() == tr("关闭混音"))
		{
			ui.m_bAux->setText(tr("关闭中..."));
			ui.m_bAux->setEnabled(false);

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32)
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
			ui.m_bAux->setText(tr("开启混音"));
		}

		//停止直播后不能混音、声音采集、分享
		ui.m_bAux->setEnabled(false);
		ui.m_bCapture->setEnabled(false);
		ui.m_bShare->setEnabled(false);
		ui.m_bProgMircoPhone->setEnabled(false);
		ui.m_bRequestJoinLive->setEnabled(true);
		ui.m_bRequestJoinLive->setText(tr("开始直播"));
	}
}

void ZegoExternalAnchorDialog::OnTimerRefreshView()
{
	if (AVViews.size() > 0)
	{
		QZegoAVView *view = AVViews.last();
		view->update();
	}
}

void ZegoExternalAnchorDialog::OnDeviceAdded(int device_type, QString device_name)
{
	if (device_type == TYPE_AUDIO)
	{
		ui.m_cbMircoPhone->blockSignals(true);
		insertStringListModelItem(m_cbMircoPhoneModel, device_name, m_cbMircoPhoneModel->rowCount());
		ui.m_cbMircoPhone->blockSignals(false);

		m_vecAudioDevice = m_device->GetAudioDeviceList();

		if (m_vecAudioDevice.size() == 1)
		{
			//LIVEROOM::SetAudioDevice(AV::AudioDeviceType::AudioDevice_Input, qtoc(m_device->GetAudioDeviceId()));
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

			m_input->SetCameraDeviceID(cameraId.toStdString());
			
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

void ZegoExternalAnchorDialog::OnDeviceDeleted(int device_type, int index)
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

		
		if (m_vecVideoDevice.size() == 1)
		{
			ui.m_cbCamera2->blockSignals(true);
			ui.m_cbCamera2->setModel(new QStringListModel(this));
			ui.m_cbCamera2->blockSignals(false);

			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());

			
			//此时是摄像头2设置到摄像头1的位置上的情况
			if (cameraId != m_pAVSettings->GetCameraId())
			{
				m_input->SetCameraDeviceID(cameraId.toStdString());
			}

		}
		else
		{
			ui.m_cbCamera->setCurrentIndexWithoutSignal(m_device->GetVideoDeviceIndex());
			ui.m_cbCamera2->setCurrentIndexWithoutSignal(m_device->GetVideoDevice2Index());

			if (cameraId != m_pAVSettings->GetCameraId())
			{
				m_input->SetCameraDeviceID(cameraId.toStdString());
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

void ZegoExternalAnchorDialog::OnSwitchAudioDevice_External(int id)
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

void ZegoExternalAnchorDialog::OnSwitchVideoDevice_External(int id)
{
	if (id < 0)
		return;

	if (id < m_vecVideoDevice.size())
	{
		QDeviceState state = m_device->SetCameraIdByIndex(id);
	
		m_input->SetCameraDeviceID(m_device->GetVideoDeviceId().toStdString());
		m_pAVSettings->SetCameraId(qtoc(m_device->GetVideoDeviceId()));

		ui.m_cbCamera->setCurrentIndexWithoutSignal(id);
		update();

		//切换设备之后，如果当前设备被关闭，则开启
		if (!ui.m_bCamera->isChecked())
			ui.m_bCamera->setChecked(true);
		qDebug() << "[MoreAnchorDialog::VideoDevice_Changed_1]: current video device_main : " << m_pAVSettings->GetCameraId() << " video device_aux : " << m_pAVSettings->GetCameraId2();
	}
}

