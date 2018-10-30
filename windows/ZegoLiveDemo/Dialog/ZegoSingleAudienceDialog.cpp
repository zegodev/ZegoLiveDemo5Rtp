#include "ZegoSingleAudienceDialog.h"
#include "Signal/ZegoSDKSignal.h"
//Objective-C Header
#ifdef Q_OS_MAC
#include "OSX_Objective-C/ZegoAVDevice.h"
#include "OSX_Objective-C/ZegoCGImageToQImage.h"
#endif
ZegoSingleAudienceDialog::ZegoSingleAudienceDialog(QWidget *parent)
	: ZegoBaseDialog(parent)
{

}

ZegoSingleAudienceDialog::ZegoSingleAudienceDialog(RoomPtr room, ZegoDeviceManager *device, QStringListModel *micModel, QStringListModel *cameraModel, QDialog *lastDialog, QDialog *parent)
	: ZegoBaseDialog(room, device, micModel, cameraModel, lastDialog, false, false, parent)
{
	//通过sdk的信号连接到本类的槽函数中
	connect(GetAVSignal(), &QZegoAVSignal::sigLoginRoom, this, &ZegoSingleAudienceDialog::OnLoginRoom);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamUpdated, this, &ZegoSingleAudienceDialog::OnStreamUpdated);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayStateUpdate, this, &ZegoSingleAudienceDialog::OnPlayStateUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigPlayQualityUpdate, this, &ZegoSingleAudienceDialog::OnPlayQualityUpdate);
	connect(GetAVSignal(), &QZegoAVSignal::sigStreamExtraInfoUpdated, this, &ZegoSingleAudienceDialog::OnStreamExtraInfoUpdated);
}

ZegoSingleAudienceDialog::~ZegoSingleAudienceDialog()
{

}

//功能函数
void ZegoSingleAudienceDialog::initDialog()
{
	//读取标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("单主播模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	ui.m_bRequestJoinLive->setVisible(false);
	ui.m_lbCamera2->setVisible(false);
	ui.m_cbCamera2->setVisible(false);

	ZegoBaseDialog::initDialog();
}

void ZegoSingleAudienceDialog::StartPlayStream(StreamPtr stream)
{
	if (stream == nullptr) { return; }

	m_pChatRoom->addStream(stream);

	if (m_avaliableView.size() > 0)
	{
		int nIndex = takeLeastAvaliableViewIndex();
		qDebug() << "playStream nIndex = " << nIndex;
		stream->setPlayView(nIndex);
		addAVView(nIndex, ZEGODIALOG_SingleAudience);
		connect(AVViews.last(), &QZegoAVView::sigSnapShotOnSingleAudienceWithStreamID, this, &ZegoBaseDialog::OnSnapshotWithStreamID);
		AVViews.last()->setViewStreamID(stream->getStreamId());

		m_anchorStreamInfo = stream;
		//配置View
		LIVEROOM::SetViewMode(LIVEROOM::ZegoVideoViewModeScaleAspectFit, stream->getStreamId().toStdString().c_str());
		LIVEROOM::StartPlayingStream(stream->getStreamId().toStdString().c_str(), (void *)AVViews[nIndex]->winId());
	}
}

void ZegoSingleAudienceDialog::StopPlayStream(const QString& streamID)
{
	if (streamID.size() == 0) { return; }

	removeAVView(m_anchorStreamInfo->getPlayView());
	LIVEROOM::StopPlayingStream(streamID.toStdString().c_str());

	StreamPtr pStream = m_pChatRoom->removeStream(streamID);
	FreeAVView(pStream);

	//m_mainLiveView->setViewStreamID("");
}

bool ZegoSingleAudienceDialog::praseJsonData(QJsonDocument doc)
{
	QJsonObject obj = doc.object();

	QJsonValue isFirstAnchor = obj.take(m_FirstAnchor);
	QJsonValue hlsUrl = obj.take(m_HlsKey);
	QJsonValue rtmpUrl = obj.take(m_RtmpKey);

	QString roomName = obj.take(m_RoomName).toString();

	sharedHlsUrl = hlsUrl.toString();
	sharedRtmpUrl = rtmpUrl.toString();

	if(!roomName.isEmpty())
	    m_pChatRoom->setRoomName(roomName);
	//更新标题内容
	QString strTitle = QString(tr("【%1】%2")).arg(tr("单主播模式")).arg(m_pChatRoom->getRoomName());
	ui.m_lbRoomName->setText(strTitle);

	return true;
}

void ZegoSingleAudienceDialog::GetOut()
{
	for (auto& stream : m_pChatRoom->getStreamList())
	{
		if (stream != nullptr)
		    StopPlayStream(stream->getStreamId());
	}

	ZegoBaseDialog::GetOut();
}

//SDK回调
void ZegoSingleAudienceDialog::OnLoginRoom(int errorCode, const QString& strRoomID, QVector<StreamPtr> vStreamList)
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


	//当前房间的直播模式为单主播模式，直接拉多路流
	for (auto& stream : vStreamList)
	{
		StartPlayStream(stream);
	}

	//将第一个流信息作为主播流信息
	if (m_pChatRoom->getStreamCount() > 0)
	{

		m_anchorStreamInfo = m_pChatRoom->getStreamList()[0];
		QByteArray jsonArray = m_anchorStreamInfo->getExtraInfo().toUtf8();

		QJsonParseError json_error;
		QJsonDocument doc = QJsonDocument::fromJson(jsonArray, &json_error);

		if (json_error.error != QJsonParseError::NoError){ return; }

		if (!doc.isObject()) { return; }

		praseJsonData(doc);
	}
		

}

void ZegoSingleAudienceDialog::OnStreamUpdated(const QString& roomId, QVector<StreamPtr> vStreamList, LIVEROOM::ZegoStreamUpdateType type)
{
	//在单主播模式下，有流更新直接处理
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

void ZegoSingleAudienceDialog::OnStreamExtraInfoUpdated(const QString& roomId, QVector<StreamPtr> vStreamList)
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
				QString strTitle = QString(tr("【%1】%2")).arg(tr("单主播模式")).arg(m_pChatRoom->getRoomName());
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

void ZegoSingleAudienceDialog::OnPlayStateUpdate(int stateCode, const QString& streamId)
{
	qDebug() << "OnPlay! stateCode = " << stateCode;

	ui.m_bShare->setEnabled(true);

	if (stateCode != 0)
	{
		// 回收view
		removeAVView(m_anchorStreamInfo->getPlayView());
		StreamPtr pStream = m_pChatRoom->removeStream(streamId);
		FreeAVView(pStream);
	}
}

void ZegoSingleAudienceDialog::OnPlayQualityUpdate(const QString& streamId, int quality, double videoFPS, double videoKBS)
{
	StreamPtr pStream = m_pChatRoom->getStreamById(streamId);

	if (pStream == nullptr)
		return;

	int nIndex = pStream->getPlayView();

	if (nIndex < 0 || nIndex > 11)
		return;

	//AVViews[nIndex]->setCurrentQuality(quality);

}