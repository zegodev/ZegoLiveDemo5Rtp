#include "ZegoPublish2StreamDialog.h"
#include "Signal/ZegoSDKSignal.h"
//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoPublish2StreamDialog::ZegoPublish2StreamDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{

}

ZegoPublish2StreamDialog::ZegoPublish2StreamDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, true, true, parent)
{
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoPublish2StreamDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamUpdated, this, &ZegoPublish2StreamDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoPublish2StreamDialog::OnPublishStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayStateUpdate, this, &ZegoPublish2StreamDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigJoinLiveRequest, this, &ZegoPublish2StreamDialog::OnJoinLiveRequest);
	//UI信号槽
	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoPublish2StreamDialog::OnButtonSwitchPublish);
	connect(ui.m_cbCamera2, SIGNAL(currentIndexChanged(int)), this, SLOT(OnSwitchVideoDevice2(int)));
}

ZegoPublish2StreamDialog::~ZegoPublish2StreamDialog()
{

}

//功能函数
void ZegoPublish2StreamDialog::initDialog()
{

	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("推双流模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	//在主播端，请求连麦的按钮变为直播开关
	ui.m_bRequestJoinLive->setText(tr("停止直播"));

	ui.m_cbCamera2->setEnabled(false);
	ui.m_lbCamera2->setEnabled(false);

	ui.m_vSpacer->changeSize(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

	ZegoBaseDialog::initDialog();
}

void ZegoPublish2StreamDialog::initCameraListView2()
{
	m_cbCameraListView2 = new QListView(this);
	ui.m_cbCamera2->setView(m_cbCameraListView2);
	ui.m_cbCamera2->setModel(m_cbCameraModel);
	ui.m_cbCamera2->setItemDelegate(new NoFocusFrameDelegate(this));
}

void ZegoPublish2StreamDialog::StartPublishStream()
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

		qDebug() << "publish nIndex = " << nIndex << "publish stream id is" << pPublishStream->getStreamId();
	
		
		LIVEROOM::SetVideoFPS(m_pAVSettings->GetFps());
		LIVEROOM::SetVideoBitrate(m_pAVSettings->GetBitrate());

		if (!m_isUseVerticalCapture)
		{
			LIVEROOM::SetVideoCaptureResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
		}
		else
		{
			LIVEROOM::SetVideoCaptureResolution(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx);
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx);
		}
			//配置View
		LIVEROOM::SetPreviewView((void *)AVViews.last()->winId());
		LIVEROOM::SetPreviewViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit);
		LIVEROOM::StartPreview();
		

		QString streamID = m_strPublishStreamID;
		m_anchorStreamInfo = pPublishStream;
		AVViews.last()->setViewStreamID(streamID);
		setWaterPrint(ZEGO::AV::PUBLISH_CHN_MAIN);
		qDebug() << "start publishing!";
		LIVEROOM::StartPublishing2(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_JOIN_PUBLISH, "");
		
		m_bIsPublishing = true;
	}
}

void ZegoPublish2StreamDialog::StartPublishStream_Aux()
{
	QTime currentTime = QTime::currentTime();
	//获取当前时间的毫秒
	int ms = currentTime.msec();
	QString strStreamId;
#ifdef Q_OS_WIN
	strStreamId = QString("s-windows-%1-%2-aux").arg(m_strCurUserID).arg(ms);
#else
	strStreamId = QString("s-mac-%1-%2-aux").arg(m_strCurUserID).arg(ms);
#endif
	m_strPublishStreamID_Aux = strStreamId;

	StreamPtr pPublishStream(new QZegoStreamModel(m_strPublishStreamID_Aux, m_strCurUserID, m_strCurUserName, "", true, true));

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

		qDebug() << "publish nIndex = " << nIndex << "publish stream id is" << pPublishStream->getStreamId();
		
		LIVEROOM::SetVideoFPS(m_pAVSettings->GetFps(), ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::SetVideoBitrate(m_pAVSettings->GetBitrate(), ZEGO::AV::PUBLISH_CHN_AUX);
		if (!m_isUseVerticalCapture)
		{
			LIVEROOM::SetVideoCaptureResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy, ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy, ZEGO::AV::PUBLISH_CHN_AUX);
		}
		else
		{
			LIVEROOM::SetVideoCaptureResolution(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx, ZEGO::AV::PUBLISH_CHN_AUX);
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cy, m_pAVSettings->GetResolution().cx, ZEGO::AV::PUBLISH_CHN_AUX);
		}

		//配置View
		LIVEROOM::SetPreviewView((void *)AVViews.last()->winId(), ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::SetPreviewViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::StartPreview(ZEGO::AV::PUBLISH_CHN_AUX);
		
		QString streamID = m_strPublishStreamID_Aux;
		m_anchorStreamInfo_Aux = pPublishStream;
		AVViews.last()->setViewStreamID(streamID);
		setWaterPrint(ZEGO::AV::PUBLISH_CHN_AUX);
		qDebug() << "start publishing aux!";
		LIVEROOM::StartPublishing2(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_JOIN_PUBLISH, "", ZEGO::AV::PUBLISH_CHN_AUX);
		//m_bIsPublishing = true;
	}
}

void ZegoPublish2StreamDialog::StopPublishStream(const QString& streamID, AV::PublishChannelIndex idx)
{
	if (streamID.size() == 0){ return; }

	LIVEROOM::SetPreviewView(nullptr);
	LIVEROOM::StopPreview();
	if (idx == ZEGO::AV::PUBLISH_CHN_MAIN)
	{
		LIVEROOM::SetPreviewView(nullptr);
		LIVEROOM::StopPreview();
	}
	else
	{
		LIVEROOM::SetPreviewView(nullptr, ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::StopPreview(ZEGO::AV::PUBLISH_CHN_AUX);
	}
	
	if (idx == ZEGO::AV::PUBLISH_CHN_MAIN)
	{
		qDebug() << "stop publish view index = " << m_anchorStreamInfo->getPlayView();
		removeAVView(m_anchorStreamInfo->getPlayView());
		LIVEROOM::StopPublishing();
		m_bIsPublishing = false;
		StreamPtr pStream = m_pChatRoom->removeStream(streamID);
		FreeAVView(pStream);
		m_strPublishStreamID = "";
	}
	else
	{
		qDebug() << "stop publish view index = " << m_anchorStreamInfo_Aux->getPlayView();
		removeAVView(m_anchorStreamInfo_Aux->getPlayView());
		LIVEROOM::StopPublishing(0, 0, ZEGO::AV::PUBLISH_CHN_AUX);
		m_bIsPublishing = false;
		StreamPtr pStream = m_pChatRoom->removeStream(streamID);
		FreeAVView(pStream);
		m_strPublishStreamID_Aux = "";
	}
	
}

void ZegoPublish2StreamDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	m_pChatRoom->addStream(stream);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playStream nIndex = " << nIndex <<" play stream id is "<<stream->getStreamId();
		stream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MoreAnchor);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnMoreAnchorWithStreamID, this, &ZegoPublish2StreamDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(stream->getStreamId());

		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, stream->getStreamId().toStdString().c_str());
		LIVEROOM::StartPlayingStream(stream->getStreamId().toStdString().c_str(), (void *)AVViews.last()->winId());
	}
}

void ZegoPublish2StreamDialog::StopPlayStream(const QString& streamID)
{
	if (streamID.size() == 0) { return; }

	StreamPtr curStream;
	for (auto stream : m_pChatRoom->getStreamList())
	{
		if (streamID == stream->getStreamId())
			curStream = stream;
	}

	qDebug() << "stop play view index = " << curStream->getPlayView();

	removeAVView(curStream->getPlayView());
	LIVEROOM::StopPlayingStream(streamID.toStdString().c_str());

	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
}

bool ZegoPublish2StreamDialog::praseJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);

	sharedHlsUrl = hlsUrl.toString();
	sharedRtmpUrl = rtmpUrl.toString();

	return true;
}

void ZegoPublish2StreamDialog::setWaterPrint(AV::PublishChannelIndex idx)
{
	QString waterPrintPath = QDir::currentPath();
	waterPrintPath += "/Resources/waterprint/";
	if (this->devicePixelRatio() < 2.0)
	{
		waterPrintPath += "waterprint.png";
	}
	else
	{
		waterPrintPath += "waterprint@2x.png";
	}

	QImage waterPrint(waterPrintPath);

	//标准640 * 360，根据标准对当前分辨率的水印进行等比缩放
	int cx = m_pAVSettings->GetResolution().cx;
	int cy = m_pAVSettings->GetResolution().cy;
	float scaleX = cx * 1.0 / 640;
	float scaleY = cy * 1.0 / 360;

	if (idx == ZEGO::AV::PUBLISH_CHN_MAIN)
	{
		LIVEROOM::SetPublishWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY));
		LIVEROOM::SetPreviewWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY));
		LIVEROOM::SetWaterMarkImagePath(waterPrintPath.toStdString().c_str());
	}
	else
	{
		LIVEROOM::SetPublishWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY), ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::SetPreviewWaterMarkRect((int)(20 * scaleX), (int)(20 * scaleY), (int)(123 * scaleX), (int)(69 * scaleY), ZEGO::AV::PUBLISH_CHN_AUX);
		LIVEROOM::SetWaterMarkImagePath(waterPrintPath.toStdString().c_str(), ZEGO::AV::PUBLISH_CHN_AUX);
	}
}

void ZegoPublish2StreamDialog::GetOut()
{
	for (auto& stream : m_pChatRoom->getStreamList())
	{
		if (stream != nullptr){
			if (stream->isCurUserCreated())
			{
				if (!stream->isCurUserCreated_Aux())
					StopPublishStream(stream->getStreamId());
				else
					StopPublishStream(stream->getStreamId(), ZEGO::AV::PUBLISH_CHN_AUX);
			}
			else
			{
				StopPlayStream(stream->getStreamId());
			}
		}
	}

	ZegoBaseDialog::GetOut();
}

//SDK回调
void ZegoPublish2StreamDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
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
	StartPublishStream_Aux();

}

void ZegoPublish2StreamDialog::OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type)
{
	//在连麦模式下，有流更新直接处理
	for (auto& stream : vStreamList)
	{
		if (stream != nullptr){
			if (type == LIVEROOM::ZegoStreamUpdateType::StreamAdded)
			{
				StartPlayStream(stream);

			}
			else if (type == LIVEROOM::ZegoStreamUpdateType::StreamDeleted)
			{
				StopPlayStream(stream->getStreamId());

			}
		}
	}
	
	
}

void ZegoPublish2StreamDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	
	if (stateCode == 0)
	{
		qDebug() << "Publish success!";
		if (streamInfo != nullptr)
		{
			
			sharedHlsUrl = (streamInfo->m_vecHlsUrls.size() > 0) ?
				streamInfo->m_vecHlsUrls[0] : "";
			sharedRtmpUrl = (streamInfo->m_vecRtmpUrls.size() > 0) ?
				streamInfo->m_vecRtmpUrls[0] : "";

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
		if (streamId == m_anchorStreamInfo_Aux->getStreamId())
		{
			ui.m_cbCamera2->setEnabled(true);
			ui.m_lbCamera2->setEnabled(true);
		}
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

void ZegoPublish2StreamDialog::OnPlayStateUpdate(int stateCode, const QString& streamId)
{
	qDebug() << "OnPlay! stateCode = " << stateCode;

	ui.m_bShare->setEnabled(true);

	if (stateCode != 0)
	{
		// 回收view
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		removeAVView(pStream->getPlayView());
		FreeAVView(pStream);
	}


}

void ZegoPublish2StreamDialog::OnJoinLiveRequest(int seq, const QString& fromUserId, const QString& fromUserName, const QString& roomId)
{
	QMessageBox box(QMessageBox::Warning, tr("提示"), QString(tr("%1正在请求连麦")).arg(fromUserId));
	box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (box.exec() == QMessageBox::Ok)
	{
		LIVEROOM::RespondJoinLiveReq(seq, 0);
	}
	else
	{
		LIVEROOM::RespondJoinLiveReq(seq, -1);
	}
}

//UI回调
void ZegoPublish2StreamDialog::OnButtonSwitchPublish()
{
	//当前按钮文本为“开始直播”
	if (ui.m_bRequestJoinLive->text() == tr("开始直播"))
	{
		ui.m_bRequestJoinLive->setText(tr("开启中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		//开始推流
		StartPublishStream();
		StartPublishStream_Aux();

	}
	//当前按钮文本为“停止直播”
	else
	{
		ui.m_bRequestJoinLive->setText(tr("停止中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		StopPublishStream(m_strPublishStreamID);
		StopPublishStream(m_strPublishStreamID_Aux, ZEGO::AV::PUBLISH_CHN_AUX);

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

