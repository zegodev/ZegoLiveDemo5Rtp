#include "ZegoMixStreamAudienceDialog.h"
#include "Signal/ZegoSDKSignal.h"

#ifdef Q_OS_WIN
#include "zego-api-audio-device.h"
#endif

//Objective-C Header
#ifdef Q_OS_MAC
//#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoMixStreamAudienceDialog::ZegoMixStreamAudienceDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{
	
}

ZegoMixStreamAudienceDialog::ZegoMixStreamAudienceDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, false, parent)
{
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoMixStreamAudienceDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamUpdated, this, &ZegoMixStreamAudienceDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoMixStreamAudienceDialog::OnPublishStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishQualityUpdate2, this, &ZegoMixStreamAudienceDialog::OnPublishQualityUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayStateUpdate, this, &ZegoMixStreamAudienceDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayQualityUpdate, this, &ZegoMixStreamAudienceDialog::OnPlayQualityUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigJoinLiveResponse, this, &ZegoMixStreamAudienceDialog::OnJoinLiveResponse);
	connect(GetAVSignal(), &QZegoAVSignal::sigMixStream, this, &ZegoMixStreamAudienceDialog::OnMixStream);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamExtraInfoUpdated, this, &ZegoMixStreamAudienceDialog::OnStreamExtraInfoUpdated);
	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoMixStreamAudienceDialog::OnButtonJoinLive);

	//设置混流回调初始值
	m_mixStreamRequestSeq = 1;
}

ZegoMixStreamAudienceDialog::~ZegoMixStreamAudienceDialog()
{

}

//功能函数
void ZegoMixStreamAudienceDialog::initDialog()
{

	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("混流模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	ZegoBaseDialog::initDialog();
}

void ZegoMixStreamAudienceDialog::StartPublishStream()
{
	QString strStreamId;
#ifdef Q_OS_WIN
	strStreamId = QString("s-windows-%1").arg(m_strCurUserID);
#else
	strStreamId = QString("s-mac-%1").arg(m_strCurUserID);
#endif
	m_strPublishStreamID = strStreamId;
	m_myMixStreamID = "mix-" + m_strPublishStreamID;

	StreamPtr pPublishStream(new QZegoStreamModel(m_strPublishStreamID, m_strCurUserID, m_strCurUserName, "", true));

	m_pChatRoom->addStream(pPublishStream);

	//使用了双声道采集后，混响和虚拟立体声均无效。
	//双声道采集
#ifdef Q_OS_WIN
	//AUDIODEVICE::EnableCaptureStereo(1);
#endif
	//推流前调用双声道编码
	LIVEROOM::SetAudioChannelCount(2);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		pPublishStream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MixStreamAudience);
		AVViews.last()->setCurUser();
		connect(AVViews.last(), &QZegoAVView::sigSnapShotPreviewOnMixStreamAudience, this, &ZegoMixStreamAudienceDialog::OnSnapshotPreview);
		qDebug() << "publish nIndex = " << nIndex <<"publish stream id is "<<pPublishStream->getStreamId();

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
		qDebug() << "start publishing!";
		setWaterPrint();
		LIVEROOM::StartPublishing(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_MIX_STREAM, "");
	}
}

void ZegoMixStreamAudienceDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0){ return; }

	StreamPtr curStream;
	for (auto stream : m_pChatRoom->getStreamList())
	{
		if (streamID == stream->getStreamId())
			curStream = stream;
	}

	qDebug() << "stop publish view index = " << curStream->getPlayView();
	removeAVView(curStream->getPlayView());

	LIVEROOM::SetPreviewView(nullptr);
	LIVEROOM::StopPreview();
	LIVEROOM::StopPublishing();
	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
    
    m_strPublishStreamID = "";
}

void ZegoMixStreamAudienceDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	m_pChatRoom->addStream(stream);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playStream nIndex = " << nIndex << "play stream id is "<< stream->getStreamId();
		stream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MixStreamAudience);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnMixStreamAudienceWithStreamID, this, &ZegoMixStreamAudienceDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(stream->getStreamId());

		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, stream->getStreamId().toStdString().c_str());
		LIVEROOM::StartPlayingStream(stream->getStreamId().toStdString().c_str(), (void *)AVViews.last()->winId());
	}
}

void ZegoMixStreamAudienceDialog::StopPlayStream(const QString& streamID)
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

void ZegoMixStreamAudienceDialog::GetOut()
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

bool ZegoMixStreamAudienceDialog::isStreamExisted(QString streamID)
{
	bool isExisted = false;

	if (m_strPublishStreamID == streamID)
		return true;

	//获取房间流列表
	QVector<StreamPtr> streamList = m_pChatRoom->getStreamList();
	for (auto streamInfo : streamList)
		if (streamInfo->getStreamId() == streamID)
			return true;

	return false;
}

void ZegoMixStreamAudienceDialog::StartMixStream()
{
	int size = m_mixStreamInfos.size();
	int width = m_pAVSettings->GetResolution().cx;
	int height = m_pAVSettings->GetResolution().cy;

	AV::ZegoCompleteMixStreamConfig mixStreamConfig;
	mixStreamConfig.pInputStreamList = new AV::ZegoMixStreamConfig[size];

	for (int i = 0; i < size; i++)
	{
		strcpy(mixStreamConfig.pInputStreamList[i].szStreamID, m_mixStreamInfos[i]->szStreamID);
		mixStreamConfig.pInputStreamList[i].layout.top = m_mixStreamInfos[i]->layout.top;
		mixStreamConfig.pInputStreamList[i].layout.bottom = m_mixStreamInfos[i]->layout.bottom;
		mixStreamConfig.pInputStreamList[i].layout.left = m_mixStreamInfos[i]->layout.left;
		mixStreamConfig.pInputStreamList[i].layout.right = m_mixStreamInfos[i]->layout.right;
	}

	mixStreamConfig.nInputStreamCount = size;
	strcpy(mixStreamConfig.szOutputStream, m_myMixStreamID.toStdString().c_str());
	mixStreamConfig.bOutputIsUrl = false;
	mixStreamConfig.nOutputWidth = width;
	mixStreamConfig.nOutputHeight = height;
	mixStreamConfig.nOutputFps = m_pAVSettings->GetFps();
	mixStreamConfig.nOutputBitrate = m_pAVSettings->GetBitrate();
	mixStreamConfig.nChannels = 2;

	qDebug() << "startMixStream!";
	LIVEROOM::MixStream(mixStreamConfig, m_mixStreamRequestSeq++);
}

void ZegoMixStreamAudienceDialog::StopPlayMixStream(QVector<StreamPtr> vStreamList)
{
	//只有主播流退出了才会停止拉混流
	for (auto stream : vStreamList)
	{
		if (stream->getStreamId() == m_anchorStreamInfo->getStreamId())
		{
			removeAVView(m_anchorStreamInfo->getPlayView());
			LIVEROOM::StopPlayingStream(m_anchorMixStreamID.toStdString().c_str());
			StreamPtr pStream = m_pChatRoom->removeStream(stream->getStreamId());
			FreeAVView(pStream);

		}
	}
}

void ZegoMixStreamAudienceDialog::StartPlayMixStream(StreamPtr streamInfo)
{
	qDebug() << "startPlayMixStream!";
	
	if (streamInfo == nullptr) { return; }

	m_pChatRoom->addStream(streamInfo);

	//保存当前混流主播的流信息
	m_anchorStreamInfo = streamInfo;

	if (m_avaliableView.size() > 0)
	{
		
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playMixStream index = " << nIndex;

		streamInfo->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MixStreamAudience);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnMixStreamAudienceWithStreamID, this, &ZegoMixStreamAudienceDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(m_anchorMixStreamID);
		
		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, m_anchorMixStreamID.toStdString().c_str());
		LIVEROOM::StartPlayingStream(m_anchorMixStreamID.toStdString().c_str(), (void *)AVViews.last()->winId());
	}

}

void ZegoMixStreamAudienceDialog::StartPlaySingleStream(QVector<StreamPtr> streamList)
{
	for (auto stream : streamList)
	{
		if (stream->getStreamId() != m_strPublishStreamID)
			StartPlayStream(stream);
	}
}

void ZegoMixStreamAudienceDialog::StopPlaySingleStream()
{
	QVector<StreamPtr> roomStreamList = m_pChatRoom->getStreamList();
	qDebug() << "roomSize = " << roomStreamList.size();

	for (auto stream : roomStreamList)
	{
		if (stream->getStreamId() != m_strPublishStreamID)
		{
			m_mixStreamList.push_back(stream);
			StopPlayStream(stream->getStreamId());
		}

	}

}

void ZegoMixStreamAudienceDialog::MixStreamAdd(QVector<StreamPtr> vStreamList, const QString& roomId)
{
	
}

void ZegoMixStreamAudienceDialog::MixStreamDelete(QVector<StreamPtr> vStreamList, const QString& roomId)
{
	for (auto bizStream : vStreamList)
	{
		StopPlayStream(bizStream->getStreamId());

		for (int i = 0; i < m_mixStreamInfos.size(); i++)
		{
			if (strcmp(m_mixStreamInfos[i]->szStreamID, bizStream->getStreamId().toStdString().c_str()) == 0)
				m_mixStreamInfos.removeAt(i);
			break;
		}
	}

	StartMixStream();
}


bool ZegoMixStreamAudienceDialog::praseMixJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue mixStreamId = obj.take(m_MixStreamID);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);
	QString roomName = obj.take(m_RoomName).toString();

	QVariant tmpValue = isFirstAnchor.toString();
	bool isFirst = tmpValue.toBool();

	if ((isFirst || isFirstAnchor.toBool()) && !mixStreamId.toString().isEmpty())
	{
		m_anchorMixStreamID = mixStreamId.toString();
		sharedHlsUrl = hlsUrl.toString();
		sharedRtmpUrl = rtmpUrl.toString();

		if (!roomName.isEmpty())
			m_pChatRoom->setRoomName(roomName);
		//更新标题内容
		QString strTitle = QString(tr("【%1】%2")).arg(tr("混流模式")).arg(m_pChatRoom->getRoomName());
		ui.m_lbRoomName->setText(strTitle);
		return true;
	}

	return false;
}

//SDK回调
void ZegoMixStreamAudienceDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
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

	
	for (auto stream : vStreamList)
		m_mixStreamList.push_back(stream);



	//当前房间的直播模式为混流模式，拉一条混流
	if (vStreamList.size() > 0){
		bool isSuccess = false;
		//遍历找出第一主播的流，找到extraInfo流附加消息并进行解析
		for (auto streamInfo : vStreamList)
		{
			QByteArray jsonArray = streamInfo->getExtraInfo().toUtf8();

			QJsonParseError json_error;
			QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &json_error);

			if (json_error.error != QJsonParseError::NoError){ continue; }

			if (!doc.isObject()) { continue; }

			if (praseMixJsonData(doc))
			{
				StartPlayMixStream(streamInfo);
				isSuccess = true;
				break;
			}
		}

		if (!isSuccess)
		QMessageBox::warning(NULL, tr("警告"), tr("拉混流失败，不存在第一主播"));
	}
		
	
}

void ZegoMixStreamAudienceDialog::OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type)
{
	
	//在混流模式下，有流更新时需要作混流处理(合并/删除)
	//观众看别人增减流,观众段需要变化房间的流列表
	if (!m_bIsJoinLive && m_mixStreamList.size() > 0)
	{
		if (type == LIVEROOM::ZegoStreamUpdateType::StreamAdded)
		{
			for (auto stream : vStreamList)
			{
				if (isStreamExisted(stream->getStreamId()))
					continue;

				m_mixStreamList.push_back(stream);
			}
		}
		else if (type == LIVEROOM::ZegoStreamUpdateType::StreamDeleted)
		{
			for (int i = 0; i < vStreamList.size(); i++)
			{
				if (!isStreamExisted(vStreamList[i]->getStreamId()))
					continue;

				m_mixStreamList.remove(i);
			}

			StopPlayMixStream(vStreamList);
		}
	}
	else if (m_bIsJoinLive)
	{
		if (type == LIVEROOM::ZegoStreamUpdateType::StreamAdded)
		{
			for (auto stream : vStreamList)
			{
				if (isStreamExisted(stream->getStreamId()))
					continue;

				StartPlayStream(stream);
			}
		}
		else if (type == LIVEROOM::ZegoStreamUpdateType::StreamDeleted)
		{
			for (int i = 0; i < vStreamList.size(); i++)
			{
				if (!isStreamExisted(vStreamList[i]->getStreamId()))
					continue;

				StopPlayStream(vStreamList[i]->getStreamId());
			}
		}
	}
		
}

void ZegoMixStreamAudienceDialog::OnStreamExtraInfoUpdated(const QString& roomId, QVector<StreamPtr> vStreamList)
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
			if (newRoomName != m_pChatRoom->getRoomName() && !newRoomName.isEmpty())
			{
				m_pChatRoom->setRoomName(newRoomName);
				QString strTitle = QString(tr("【%1】%2")).arg(tr("混流模式")).arg(m_pChatRoom->getRoomName());
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

void ZegoMixStreamAudienceDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	qDebug() << "Publish success!";
	if (stateCode == 0)
	{
		
		//观众端在混流模式下请求连麦时，需要断开混流改为拉单流
	
		//此时表明0号ViEW正在用于拉混流
		if (m_avaliableView.size() >= m_mixStreamList.size())
		{
			//停止拉混流
			//LIVEROOM::StopPlayingStream(m_mixStreamID.toStdString().c_str());
			//FreeAVView(streamInfo);

			//逐条拉单流
			StartPlaySingleStream(m_mixStreamList);
			m_mixStreamList.clear();
		}
		
		ui.m_bAux->setEnabled(true);
		ui.m_bCapture->setEnabled(true);
		ui.m_bShare->setEnabled(true);

		//连麦成功时，以下控件可用
		if (m_bIsJoinLive)
		{
			ui.m_bRequestJoinLive->setEnabled(true);
			ui.m_bRequestJoinLive->setText(tr("停止连麦"));
			SetOperation(true);
		}

	}
	else
	{
		QMessageBox::warning(NULL, tr("推流失败"), tr("错误码: %1").arg(stateCode));
		ui.m_bRequestJoinLive->setText(tr("请求连麦"));
		ui.m_bRequestJoinLive->setEnabled(true);

		// 停止预览, 回收view
		removeAVView(streamInfo->getPlayView());
		LIVEROOM::StopPreview();
		LIVEROOM::SetPreviewView(nullptr);
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		FreeAVView(pStream);
	}
}

void ZegoMixStreamAudienceDialog::OnPlayStateUpdate(int stateCode, const QString& streamId)
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

void ZegoMixStreamAudienceDialog::OnPublishQualityUpdate(const QString& streamId, int quality, double capFPS, double videoFPS, double videoKBS, double audioKBS, int rtt, int pktLostRate)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	AVViews[nIndex]->setCurrentQuality(quality);

	/*if (capFPS == 0)
	{
		QMessageBox::warning(NULL, tr("警告"), tr("摄像头采集异常，停止推流"));
		ui.m_bRequestJoinLive->setText(tr("停止中..."));
		ui.m_bRequestJoinLive->setEnabled(false);
		StopPublishStream(streamId);
		ui.m_bRequestJoinLive->setEnabled(true);
		ui.m_bRequestJoinLive->setText(tr("请求连麦"));

	}*/
}

void ZegoMixStreamAudienceDialog::OnPlayQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	AVViews[nIndex]->setCurrentQuality(quality);

}

void ZegoMixStreamAudienceDialog::OnMixStream(unsigned int errorCode, const QString& hlsUrl, const QString& rtmpUrl, const QString& mixStreamID, int seq)
{
	qDebug() << "mixStream update!";
}

void ZegoMixStreamAudienceDialog::OnJoinLiveResponse(int result, const QString& fromUserId, const QString& fromUserName, int seq)
{
	if (seq == m_iRequestJoinLiveSeq)
	{

		if (result == 0)
		{
			//停止拉混流
			StopPlayMixStream(m_mixStreamList);
			StartPublishStream();
			
			m_bIsJoinLive = true;
			
		}
		else
		{
			ui.m_bRequestJoinLive->setText(tr("请求连麦"));
			QMessageBox::information(NULL, tr("提示"), tr("连麦请求被拒绝"));
			ui.m_bRequestJoinLive->setEnabled(true);
		}

	}
	
}

void ZegoMixStreamAudienceDialog::OnRecvEndJoinLiveCommand(const QString& userId, const QString& userName, const QString& roomId)
{
	StopPlaySingleStream();
	StopPublishStream(m_strPublishStreamID);
	StartPlayMixStream(m_anchorStreamInfo);
	m_bIsJoinLive = false;
	SetOperation(false);
	QMessageBox::information(NULL, tr("提示"), tr("主播 %1 已结束与您的连麦"));
}

void ZegoMixStreamAudienceDialog::OnButtonJoinLive()
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
		//停止连麦时，停止拉单流改为拉混流
		StopPlaySingleStream();
		StopPublishStream(m_strPublishStreamID);
		StartPlayMixStream(m_anchorStreamInfo);
		
		//if (timer->isActive())
			//timer->stop();
		ui.m_bProgMircoPhone->setMyEnabled(false);
		ui.m_bProgMircoPhone->update();

		if (ui.m_bAux->text() == tr("关闭混音"))
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
			ui.m_bAux->setText(tr("开启混音"));
		}
		//停止直播后不能混音、声音采集、分享,并且不能使用麦克风
		ui.m_bAux->setEnabled(false);
		ui.m_bCapture->setEnabled(false);
		ui.m_bShare->setEnabled(false);
		ui.m_bProgMircoPhone->setEnabled(false);
		ui.m_bRequestJoinLive->setText(tr("请求连麦"));
		ui.m_bRequestJoinLive->setEnabled(true);
	}
}
