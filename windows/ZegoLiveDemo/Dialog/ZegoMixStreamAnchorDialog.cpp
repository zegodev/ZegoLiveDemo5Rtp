#include "ZegoMixStreamAnchorDialog.h"
#include "Signal/ZegoSDKSignal.h"

#ifdef Q_OS_WIN
#include "zego-api-audio-device.h"
#endif

//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoMixStreamAnchorDialog::ZegoMixStreamAnchorDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{

}

ZegoMixStreamAnchorDialog::ZegoMixStreamAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, true, parent)
{
	
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoMixStreamAnchorDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamUpdated, this, &ZegoMixStreamAnchorDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoMixStreamAnchorDialog::OnPublishStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishQualityUpdate2, this, &ZegoMixStreamAnchorDialog::OnPublishQualityUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayStateUpdate, this, &ZegoMixStreamAnchorDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayQualityUpdate, this, &ZegoMixStreamAnchorDialog::OnPlayQualityUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigJoinLiveRequest, this, &ZegoMixStreamAnchorDialog::OnJoinLiveRequest);
	connect(GetAVSignal(), &QZegoAVSignal::sigMixStream, this, &ZegoMixStreamAnchorDialog::OnMixStream);
	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoMixStreamAnchorDialog::OnButtonSwitchPublish);

	//设置混流回调初始值
	m_mixStreamRequestSeq = 1;

}

ZegoMixStreamAnchorDialog::~ZegoMixStreamAnchorDialog()
{

}

//功能函数
void ZegoMixStreamAnchorDialog::initDialog()
{
	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("混流模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	//在主播端，请求连麦的按钮变为直播开关
	ui.m_bRequestJoinLive->setText(tr("停止直播"));

	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	ZegoBaseDialog::initDialog();
	
}

void ZegoMixStreamAnchorDialog::StartPublishStream()
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
#ifdef Q_OS_WIN
    //双声道采集
    //AUDIODEVICE::EnableCaptureStereo(1);
#endif
	//推流前调用双声道编码
	LIVEROOM::SetAudioChannelCount(2);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		pPublishStream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MixStreamAnchor);
		AVViews.last()->setCurUser();
		connect(AVViews.last(), &QZegoAVView::sigSnapShotPreviewOnMixStreamAnchor, this, &ZegoMixStreamAnchorDialog::OnSnapshotPreview);
		qDebug() << "publish nIndex = " << nIndex;

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
		setWaterPrint();
		qDebug() << "start publishing!";
		LIVEROOM::StartPublishing(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_MIX_STREAM, "");
		m_bIsPublishing = true;
	}
}

void ZegoMixStreamAnchorDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0){ return; }

	qDebug() << "stop publish view index = " << m_anchorStreamInfo->getPlayView();
	removeAVView(m_anchorStreamInfo->getPlayView());

	LIVEROOM::SetPreviewView(nullptr);
	LIVEROOM::StopPreview();
	LIVEROOM::StopPublishing();
	m_bIsPublishing = false;
	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
    
    m_strPublishStreamID = "";
}

void ZegoMixStreamAnchorDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	m_pChatRoom->addStream(stream);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playStream nIndex = " << nIndex;
		stream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_MixStreamAudience);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnMixStreamAnchorWithStreamID, this, &ZegoMixStreamAnchorDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(stream->getStreamId());

		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, stream->getStreamId().toStdString().c_str());
		LIVEROOM::StartPlayingStream(stream->getStreamId().toStdString().c_str(), (void *)AVViews.last()->winId());
	}
}

void ZegoMixStreamAnchorDialog::StopPlayStream(const QString& streamID)
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

void ZegoMixStreamAnchorDialog::GetOut()
{
	StopMixStream();
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

bool ZegoMixStreamAnchorDialog::isStreamExisted(QString streamID)
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

void ZegoMixStreamAnchorDialog::StartMixStream()
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

void ZegoMixStreamAnchorDialog::StopMixStream()
{
	AV::ZegoCompleteMixStreamConfig mixStreamConfig;
	qDebug() << "stopMixStream!";
	LIVEROOM::MixStream(mixStreamConfig, m_mixStreamRequestSeq++);
}

void ZegoMixStreamAnchorDialog::MixStreamAdd(QVector<StreamPtr> vStreamList, const QString& roomId)
{
	//主播端流增加，更新混流信息
	int width = m_pAVSettings->GetResolution().cx;
	int height = m_pAVSettings->GetResolution().cy;
	qDebug() << "current mix size = " << m_mixStreamInfos.size();
	for (auto streamInfo : vStreamList)
	{
		StartPlayStream(streamInfo);

		if (m_mixStreamInfos.size() == 1)
		{
			AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
			strcpy(mixStreamInfo->szStreamID, streamInfo->getStreamId().toStdString().c_str());
			mixStreamInfo->layout.top = (int)(height * 2.0 / 3);
			mixStreamInfo->layout.bottom = height;
			mixStreamInfo->layout.left = (int)(width * 2.0 / 3);
			mixStreamInfo->layout.right = width;

			m_mixStreamInfos.push_back(mixStreamInfo);
		}
		else if (m_mixStreamInfos.size() == 2)
		{
			AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
			strcpy(mixStreamInfo->szStreamID, streamInfo->getStreamId().toStdString().c_str());
			mixStreamInfo->layout.top = (int)(height * 2.0 / 3);
			mixStreamInfo->layout.bottom = height;
			mixStreamInfo->layout.left = (int)(width * 1.0 / 3);
			mixStreamInfo->layout.right = (int)(width * 2.0 / 3);

			m_mixStreamInfos.push_back(mixStreamInfo);
		}
		else if (m_mixStreamInfos.size() == 3)
		{
			AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
			strcpy(mixStreamInfo->szStreamID, streamInfo->getStreamId().toStdString().c_str());
			mixStreamInfo->layout.top = (int)(height * 2.0 / 3);
			mixStreamInfo->layout.bottom = height;
			mixStreamInfo->layout.left = 0;
			mixStreamInfo->layout.right = (int)(width * 1.0 / 3);

			m_mixStreamInfos.push_back(mixStreamInfo);
		}
		else if (m_mixStreamInfos.size() == 4)
		{
			AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
			strcpy(mixStreamInfo->szStreamID, streamInfo->getStreamId().toStdString().c_str());
			mixStreamInfo->layout.top = (int)(height * 1.0 / 3);
			mixStreamInfo->layout.bottom = (int)(height * 2.0 / 3);
			mixStreamInfo->layout.left = (int)(width * 2.0 / 3);
			mixStreamInfo->layout.right = width;

			m_mixStreamInfos.push_back(mixStreamInfo);
		}
		else if (m_mixStreamInfos.size() == 5)
		{
			AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
			strcpy(mixStreamInfo->szStreamID, streamInfo->getStreamId().toStdString().c_str());
			mixStreamInfo->layout.top = (int)(height * 1.0 / 3);
			mixStreamInfo->layout.bottom = (int)(height * 2.0 / 3);
			mixStreamInfo->layout.left = (int)(width * 1.0 / 3);
			mixStreamInfo->layout.right = (int)(width * 2.0 / 3);

			m_mixStreamInfos.push_back(mixStreamInfo);
		}
	}

		StartMixStream();
}

void ZegoMixStreamAnchorDialog::MixStreamDelete(QVector<StreamPtr> vStreamList, const QString& roomId)
{
	for (auto bizStream : vStreamList)
	{
		StopPlayStream(bizStream->getStreamId());

		for (int i = 0; i < m_mixStreamInfos.size(); i++)
		{
			if (strcmp(m_mixStreamInfos[i]->szStreamID, bizStream->getStreamId().toStdString().c_str()) == 0)
			{
				m_mixStreamInfos.removeAt(i);
				break;
			}
		}
	}

	StartMixStream();
}


//SDK回调
void ZegoMixStreamAnchorDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
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

	//主播推流
	StartPublishStream();

}

void ZegoMixStreamAnchorDialog::OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type)
{
	
	//在混流模式下，有流更新时需要作混流处理(合并/删除)
	//主播模式下需要执行流变化的混流操作
	if (type == LIVEROOM::ZegoStreamUpdateType::StreamAdded)
	{
		MixStreamAdd(vStreamList, roomId);
	}
	else if (type == LIVEROOM::ZegoStreamUpdateType::StreamDeleted)
	{
		MixStreamDelete(vStreamList, roomId);
	}
		
}

void ZegoMixStreamAnchorDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	qDebug() << "Publish success!";
	if (stateCode == 0)
	{

		//当前直播模式为混流模式，将主播流加到混流中
		Size videoCaptureResolution = m_pAVSettings->GetResolution();
		int width = videoCaptureResolution.cx;
		int height = videoCaptureResolution.cy;

		AV::ZegoMixStreamConfig *mixStreamInfo = new AV::ZegoMixStreamConfig;
		strcpy(mixStreamInfo->szStreamID, m_strPublishStreamID.toStdString().c_str());
		mixStreamInfo->layout.top = 0;
		mixStreamInfo->layout.bottom = height;
		mixStreamInfo->layout.left = 0;
		mixStreamInfo->layout.right = width;
		m_mixStreamInfos.push_back(mixStreamInfo);

		StartMixStream();

	}
	else
	{
		QMessageBox::warning(NULL, tr("推流失败"), tr("错误码: %1").arg(stateCode));
		ui.m_bRequestJoinLive->setText(tr("开始直播"));
		ui.m_bRequestJoinLive->setEnabled(true);

		// 停止预览, 回收view.
		removeAVView(streamInfo->getPlayView());
		LIVEROOM::StopPreview();
		LIVEROOM::SetPreviewView(nullptr);
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		FreeAVView(pStream);
	}
}

void ZegoMixStreamAnchorDialog::OnPlayStateUpdate(int stateCode, const QString& streamId)
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

void ZegoMixStreamAnchorDialog::OnPublishQualityUpdate(const QString& streamId, int quality, double capFPS, double videoFPS, double videoKBS, double audioKBS, int rtt, int pktLostRate)
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
		ui.m_bRequestJoinLive->setText(tr("开始直播"));

	}*/
}

void ZegoMixStreamAnchorDialog::OnPlayQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	AVViews[nIndex]->setCurrentQuality(quality);

}

void ZegoMixStreamAnchorDialog::OnMixStream(unsigned int errorCode, const QString& hlsUrl, const QString& rtmpUrl, const QString& mixStreamID, int seq)
{
	qDebug() << "mixStream update!";

	if (errorCode == 0)
	{
		qDebug() << tr("混流成功！ 其混流ID为：") << mixStreamID;
		qDebug() << "mix hls :" << hlsUrl;
		qDebug() << "mix rtmp :" << rtmpUrl;
		sharedHlsUrl = hlsUrl;
		sharedRtmpUrl = rtmpUrl;

		QJsonObject extraInfo;
		extraInfo.insert(m_RoomName, m_pChatRoom->getRoomName());
		extraInfo.insert(m_FirstAnchor, true);
		extraInfo.insert(m_MixStreamID, mixStreamID);
		//封装存放分享地址的json对象
		if (!sharedHlsUrl.isEmpty())
			extraInfo.insert(m_HlsKey, sharedHlsUrl);

		if (!sharedRtmpUrl.isEmpty())
			extraInfo.insert(m_RtmpKey, sharedRtmpUrl);

		QString jsonString = QJsonDocument(extraInfo).toJson().simplified();
		LIVEROOM::SetPublishStreamExtraInfo(qtoc(jsonString));

		SetOperation(true);
		ui.m_bRequestJoinLive->setEnabled(true);
		ui.m_bRequestJoinLive->setText(tr("停止直播"));

	}
	
}

void ZegoMixStreamAnchorDialog::OnJoinLiveRequest(int seq, const QString& fromUserId, const QString& fromUserName, const QString& roomId)
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
void ZegoMixStreamAnchorDialog::OnButtonSwitchPublish()
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
		StopMixStream();
		StopPublishStream(m_strPublishStreamID);

		ui.m_bRequestJoinLive->setEnabled(true);
		ui.m_bRequestJoinLive->setText(tr("开始直播"));

		//停止直播后不能混音、声音采集、分享
		ui.m_bShare->setEnabled(false);
	}
}

void ZegoMixStreamAnchorDialog::OnKickOut(int reason, const QString& roomId)
{
	if (m_pChatRoom->getRoomId() == roomId)
	{
		QMessageBox::information(NULL, tr("提示"), tr("您已被踢出房间"));
		OnClose();
	}
}
