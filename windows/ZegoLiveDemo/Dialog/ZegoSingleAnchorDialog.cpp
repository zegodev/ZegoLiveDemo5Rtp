#include "ZegoSingleAnchorDialog.h"
#include "Signal/ZegoSDKSignal.h"
#include "zego-api-audio-device.h"
//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoSingleAnchorDialog::ZegoSingleAnchorDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{
	
}

ZegoSingleAnchorDialog::ZegoSingleAnchorDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, true, parent)
{
	
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoSingleAnchorDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigPublishStateUpdate, this, &ZegoSingleAnchorDialog::OnPublishStateUpdate);

	connect(ui.m_bRequestJoinLive, &QPushButton::clicked, this, &ZegoSingleAnchorDialog::OnButtonSwitchPublish);

}

ZegoSingleAnchorDialog::~ZegoSingleAnchorDialog()
{

}

//功能函数
void ZegoSingleAnchorDialog::initDialog()
{
	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("单主播模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	if (mBase.GetUseSurfaceMerge())
		ui.m_bFullScreen->setEnabled(false);

	//单主播模式不需要第二个摄像头
	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	//在主播端，请求连麦的按钮变为直播开关
	ui.m_bRequestJoinLive->setText(tr("停止直播"));

	ZegoBaseDialog::initDialog();
}

void ZegoSingleAnchorDialog::StartPublishStream()
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
		addAVView(nIndex, ZEGODIALOG_SingleAnchor);
		AVViews.last()->setCurUser();
		connect(AVViews.last(), &QZegoAVView::sigSnapShotPreviewOnSingleAnchor, this, &ZegoBaseDialog::OnSnapshotPreview);

		qDebug() << "publish nIndex = " << nIndex;
		if (m_pAVSettings->GetSurfaceMerge())
		{
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE) 
			SurfaceMergeController::getInstance().setSurfaceSize(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
			SurfaceMergeController::getInstance().setSurfaceFps(m_pAVSettings->GetFps());
			SurfaceMergeController::getInstance().setSurfaceCameraId(m_pAVSettings->GetCameraId());
			SurfaceMergeController::getInstance().setRenderView(AVViews.last());
			SurfaceMergeController::getInstance().startSurfaceMerge();

			LIVEROOM::SetVideoFPS(m_pAVSettings->GetFps());
			LIVEROOM::SetVideoBitrate(m_pAVSettings->GetBitrate());
			LIVEROOM::SetVideoEncodeResolution(m_pAVSettings->GetResolution().cx, m_pAVSettings->GetResolution().cy);
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
			LIVEROOM::SetPreviewView((void *)AVViews[nIndex]->winId());
			LIVEROOM::SetPreviewViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit);
			LIVEROOM::StartPreview();

		}

		m_anchorStreamInfo = pPublishStream;
		qDebug() << m_anchorStreamInfo->getPlayView();
		//推流前设置水印(必须在设置好编码分辨率之后)
		setWaterPrint();
		QString streamID = m_strPublishStreamID;
		AVViews.last()->setViewStreamID(streamID);
		qDebug() << "start publishing!";
		LIVEROOM::StartPublishing(m_pChatRoom->getRoomName().toStdString().c_str(), streamID.toStdString().c_str(), LIVEROOM::ZEGO_SINGLE_ANCHOR, "");

		m_bIsPublishing = true;
	}
}

void ZegoSingleAnchorDialog::StopPublishStream(const QString& streamID)
{
	if (streamID.size() == 0){ return; }

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

	removeAVView(m_anchorStreamInfo->getPlayView());
	LIVEROOM::StopPublishing();
	m_bIsPublishing = false;
	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);
    m_strPublishStreamID = "";

}

void ZegoSingleAnchorDialog::GetOut()
{
	StopPublishStream(m_strPublishStreamID);

	ZegoBaseDialog::GetOut();
}

//SDK回调
void ZegoSingleAnchorDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
{
	qDebug() << "Login Room! Room ID = "<<strRoomID;
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


void ZegoSingleAnchorDialog::OnPublishStateUpdate(int stateCode, const QString& streamId, StreamPtr streamInfo)
{
	qDebug() << "Publish success!";
	if (stateCode == 0)
	{
		if (streamInfo != nullptr)
		{
			sharedHlsUrl = (streamInfo->m_vecHlsUrls.size() > 0) ?
				streamInfo->m_vecHlsUrls[0] : "";
			sharedRtmpUrl = (streamInfo->m_vecRtmpUrls.size() > 0) ?
				streamInfo->m_vecRtmpUrls[0] : "";

		}

		QJsonObject extraInfo;
		extraInfo.insert(m_RoomName, m_pChatRoom->getRoomName());
		extraInfo.insert(m_FirstAnchor, true);

		//在单主播模式下，推流成功时需将流媒体地址存到流附加信息中
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

			mapUrls.insert(m_FirstAnchor, QString::number(true));
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
		LIVEROOM::StopPreview();
		LIVEROOM::SetPreviewView(nullptr);
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		FreeAVView(pStream);
	}
}

//UI回调
void ZegoSingleAnchorDialog::OnButtonSwitchPublish()
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