#include "ZegoMoreAudienceDialog.h"
#include "Signal/ZegoSDKSignal.h"
//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoMoreAudienceDialog::ZegoMoreAudienceDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{
	//UI的信号槽
	connect(ui.m_bMin, &QPushButton::clicked, this, &ZegoMoreAudienceDialog::OnClickTitleButton);
	connect(ui.m_bMax, &QPushButton::clicked, this, &ZegoMoreAudienceDialog::OnClickTitleButton);
	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoMoreAudienceDialog::OnClickTitleButton);
}

ZegoMoreAudienceDialog::ZegoMoreAudienceDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, false, parent)
{
	
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoMoreAudienceDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamUpdated, this, &ZegoMoreAudienceDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoMoreAudienceDialog::OnPublishStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayStateUpdate, this, &ZegoMoreAudienceDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamExtraInfoUpdated, this, &ZegoMoreAudienceDialog::OnStreamExtraInfoUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigJoinLiveResponse, this, &ZegoMoreAudienceDialog::OnJoinLiveResponse);
	
	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoMoreAudienceDialog::OnButtonJoinLive);

}

ZegoMoreAudienceDialog::~ZegoMoreAudienceDialog()
{

}

//功能函数
void ZegoMoreAudienceDialog::initDialog()
{
	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("连麦模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	//连麦模式不需要第二个摄像头
	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	ZegoBaseDialog::initDialog();
}

void ZegoMoreAudienceDialog::StartPublishStream()
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
		addAVView(nIndex, ZEGODIALOG_MoreAudience);
		AVViews.last()->setCurUser();
		connect(AVViews.last(), &QZegoAVView::sigSnapShotPreviewOnMoreAudience, this, &ZegoBaseDialog::OnSnapshotPreview);

		qDebug() << "publish nIndex = " << nIndex;
		if(m_pAVSettings->GetSurfaceMerge())
		{
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE) 
			SurfaceMergeController::getInstance().setSurfaceSize(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
			SurfaceMergeController::getInstance().setSurfaceFps(m_pAVSettings->GetFps());
			SurfaceMergeController::getInstance().setSurfaceCameraId(m_pAVSettings->GetCameraId());
			SurfaceMergeController::getInstance().setRenderView(AVViews.last());
			SurfaceMergeController::getInstance().startSurfaceMerge();
#endif
		}
		else
		{
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
		}

		QString streamID = m_strPublishStreamID;
		setWaterPrint();
		qDebug() << "start publishing!";
		LIVEROOM::StartPublishing(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_JOIN_PUBLISH, "");
		
	}
}

void ZegoMoreAudienceDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0){ return; }

	StreamPtr curStream;
	for (auto stream : m_pChatRoom->getStreamList())
	{
		if (streamID == stream->getStreamId())
			curStream = stream;
	}

	if (m_pAVSettings->GetSurfaceMerge())
	{
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE) 
		SurfaceMerge::SetRenderView(nullptr);
		SurfaceMerge::UpdateSurface(nullptr, 0);
#endif
	}
	else
	{
		LIVEROOM::SetPreviewView(nullptr);
		LIVEROOM::StopPreview();
	}

	qDebug() << "stop publish view index = " << curStream->getPlayView();
	removeAVView(curStream->getPlayView());

	LIVEROOM::StopPublishing();

	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
    
    m_strPublishStreamID = "";
}

void ZegoMoreAudienceDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	m_pChatRoom->addStream(stream);

	if (m_avaliableView.size() > 0)
	{
		//int nIndex = m_avaliableView.top();
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playStream nIndex = " << nIndex << " play stream id is " << stream->getStreamId();
		stream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MoreAudience);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnMoreAudienceWithStreamID, this, &ZegoBaseDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(stream->getStreamId());

		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, stream->getStreamId().toStdString().c_str());
		LIVEROOM::StartPlayingStream(stream->getStreamId().toStdString().c_str(), (void *)AVViews.last()->winId());
	}
}

void ZegoMoreAudienceDialog::StopPlayStream(const QString& streamID)
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

bool ZegoMoreAudienceDialog::praseFirstAnchorJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);

	QVariant tmpValue = isFirstAnchor.toString();
	bool isFirst = tmpValue.toBool();
	if (isFirst || isFirstAnchor.toBool())
	{
		sharedHlsUrl = hlsUrl.toString();
		sharedRtmpUrl = rtmpUrl.toString();
		return true;
	}

	return false;
}

void ZegoMoreAudienceDialog::praseOtherAnchorJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);

	sharedHlsUrl = hlsUrl.toString();
	sharedRtmpUrl = rtmpUrl.toString();

}

void ZegoMoreAudienceDialog::GetOut()
{
	for (auto& stream : m_pChatRoom->getStreamList())
	{
		if (stream != nullptr){
			if (stream->isCurUserCreated())
			{
				StopPublishStream(stream->getStreamId());
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
void ZegoMoreAudienceDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
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

	//如果当前房间的直播模式为单主播模式或者连麦模式，则直接拉多路流
	for (auto& stream : vStreamList)
	{
		StartPlayStream(stream);
	}

	bool isExistFirstAnchor = false;

	//保存将第一主播流信息，若第一主播不存在了则将流列表里第一个主播作为第一主播
	for (auto stream : m_pChatRoom->getStreamList())
	{
		QByteArray jsonArray = stream->getExtraInfo().toUtf8();

		QJsonParseError json_error;
		QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &json_error);

		if (json_error.error != QJsonParseError::NoError){ continue; }

		if (!doc.isObject()) { continue; }

		if (praseFirstAnchorJsonData(doc))
		{
			m_anchorStreamInfo = stream;
			isExistFirstAnchor = true;
			break;
		}
	}

	if (m_pChatRoom->getStreamCount() > 0 && !isExistFirstAnchor)
	{
		m_anchorStreamInfo = m_pChatRoom->getStreamList()[0];
		QByteArray jsonArray = m_anchorStreamInfo->getExtraInfo().toUtf8();

		QJsonParseError json_error;
		QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &json_error);

		if (json_error.error != QJsonParseError::NoError){ return; }

		if (!doc.isObject()) { return; }

		praseOtherAnchorJsonData(doc);
	}
}
	

void ZegoMoreAudienceDialog::OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type)
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

				//当第一主播流被删除后，房间仍有其他主播在，则分享链接需要改变
				if ((stream->getStreamId() == m_anchorStreamInfo->getStreamId()) && m_pChatRoom->getStreamCount() > 0)
				{
					m_anchorStreamInfo = m_pChatRoom->getStreamList()[0];
					QByteArray jsonArray = m_anchorStreamInfo->getExtraInfo().toUtf8();

					QJsonParseError json_error;
					QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &json_error);

					if (json_error.error != QJsonParseError::NoError){ continue; }

					if (!doc.isObject()) { continue; }

					praseOtherAnchorJsonData(doc);

				}
			}
		}
	}
	
}

void ZegoMoreAudienceDialog::OnStreamExtraInfoUpdated(const QString& roomId, QVector<StreamPtr> vStreamList)
{
	for (auto& stream : vStreamList)
	{
		if (stream)
		{
			QString extraInfo = stream->getExtraInfo();
			QJsonDocument jsonDocument = QJsonDocument::fromJson(extraInfo.toLocal8Bit().data());
			if (jsonDocument.isNull())
				continue;

			QJsonObject jsonObject = jsonDocument.object();
			if (!jsonObject[m_FirstAnchor].toBool())
				continue;

			//假如当前主播推流后退出房间重新进入，有可能会改房间名
			QString newRoomName = jsonObject[m_RoomName].toString();
			if (newRoomName != m_pChatRoom->getRoomName())
			{
				m_pChatRoom->setRoomName(newRoomName);
				QString strTitle = QString(tr("【%1】%2")).arg(tr("连麦模式")).arg(m_pChatRoom->getRoomName());
				ui.m_lbRoomName->setText(strTitle);
			}

			QString newHlsUrl = jsonObject[m_HlsKey].toString();
			if (sharedHlsUrl != newHlsUrl)
				sharedHlsUrl = newHlsUrl;

			QString newRtmpUrl = jsonObject[m_RtmpKey].toString();
			if (sharedRtmpUrl != newRtmpUrl)
				sharedRtmpUrl = newRtmpUrl;
		}
	}
}

void ZegoMoreAudienceDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	
	if (stateCode == 0)
	{
		qDebug() << "Publish success!";
	
		QJsonObject extraInfo;
		extraInfo.insert(m_RoomName, m_pChatRoom->getRoomName());
		extraInfo.insert(m_FirstAnchor, false);

		//在连麦模式下，推流成功时需将流媒体地址存到流附加信息中
		if (!sharedHlsUrl.isEmpty())
			extraInfo.insert(m_HlsKey, sharedHlsUrl);

		if (!sharedRtmpUrl.isEmpty())
			extraInfo.insert(m_RtmpKey, sharedRtmpUrl);

		QString jsonString = QJsonDocument(extraInfo).toJson().simplified();
		LIVEROOM::SetPublishStreamExtraInfo(qtoc(jsonString));
		/*if (sharedHlsUrl.size() > 0 && sharedRtmpUrl.size() > 0)
		{
			//封装存放分享地址的json对象
			QMap<QString, QString> mapUrls = QMap<QString, QString>();

			mapUrls.insert(m_FirstAnchor, "false");
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
		}*/
		
		SetOperation(true);

		//当连麦成功时以下控件可用
		if (m_bIsJoinLive)
		{
			ui.m_bRequestJoinLive->setText(tr("停止连麦"));
			ui.m_bRequestJoinLive->setEnabled(true);
			
		}

		//推流成功后启动计时器监听麦克风音量
		timer->start(200);

	}
	else
	{
		QMessageBox::warning(NULL, tr("推流失败"), tr("错误码: %1").arg(stateCode));
		ui.m_bRequestJoinLive->setText(tr("请求连麦"));
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

void ZegoMoreAudienceDialog::OnPlayStateUpdate(int stateCode, const QString& streamId)
{
	qDebug() << "OnPlay! stateCode = " << stateCode;

	ui.m_bShare->setEnabled(true);
	ui.m_bRequestJoinLive->setEnabled(true);

	if (stateCode != 0)
	{
		// 回收view
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		removeAVView(pStream->getPlayView());
		FreeAVView(pStream);
	}
}

void ZegoMoreAudienceDialog::OnJoinLiveResponse(int result, const QString& fromUserId, const QString& fromUserName, int seq)
{
	if (seq == m_iRequestJoinLiveSeq)
	{

		if (result == 0)
		{
			m_bIsJoinLive = true;
			StartPublishStream();
		}
		else
		{
			ui.m_bRequestJoinLive->setText(tr("请求连麦"));
			QMessageBox::information(NULL, tr("提示"), tr("连麦请求被拒绝"));
			ui.m_bRequestJoinLive->setEnabled(true);
		}

	}
	
}

void ZegoMoreAudienceDialog::OnRecvEndJoinLiveCommand(const QString& userId, const QString& userName, const QString& roomId)
{
	StopPublishStream(m_strPublishStreamID);
	m_bIsJoinLive = false;
	SetOperation(false);
	QMessageBox::information(NULL, tr("提示"), tr("主播 %1 已结束与您的连麦"));
}

void ZegoMoreAudienceDialog::OnButtonJoinLive()
{
	//当前按钮文本为“开始连麦”
	if (ui.m_bRequestJoinLive->text() == tr("请求连麦"))
	{
		ui.m_bRequestJoinLive->setText(tr("请求中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		// 请求连麦
		m_iRequestJoinLiveSeq = LIVEROOM::RequestJoinLive();

	}
	//当前按钮文本为“停止连麦”
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
		ui.m_bRequestJoinLive->setEnabled(false);
		ui.m_bRequestJoinLive->setEnabled(true);
		m_bIsJoinLive = false;
		SetOperation(false);
		ui.m_bRequestJoinLive->setText(tr("请求连麦"));
	}
}

