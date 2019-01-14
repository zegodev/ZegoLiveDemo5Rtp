#include "Signal/ZegoSDKSignal.h"
#include <QMetaType>
#include <QDebug>

QZegoAVSignal::QZegoAVSignal()
{
	qRegisterMetaType< QVector<StreamPtr> >("QVector<StreamPtr>");
	qRegisterMetaType< QVector<RoomMsgPtr> >("QVector<RoomMsgPtr>");
	qRegisterMetaType<StreamPtr>("StreamPtr");
	qRegisterMetaType<LIVEROOM::ZegoStreamUpdateType>("LIVEROOM::ZegoStreamUpdateType");
	qRegisterMetaType<LIVEROOM::ZegoUserInfo>("LIVEROOM::ZegoUserInfo");
	qRegisterMetaType<LIVEROOM::ZegoUserUpdateType>("LIVEROOM::ZegoUserUpdateType");
	qRegisterMetaType< QVector<QString> >(" QVector<QString> ");
	qRegisterMetaType< QVector<int> >(" QVector<int> ");
	qRegisterMetaType<AV::ZegoMixStreamResult>("AV::ZegoMixStreamResult");
	qRegisterMetaType< AV::AudioDeviceType >("AV::AudioDeviceType");
	qRegisterMetaType< AV::DeviceState >("AV::DeviceState");
}

QZegoAVSignal::~QZegoAVSignal()
{

}

void QZegoAVSignal::OnInitSDK(int nError)
{
	emit sigInitSDK(nError);
}

void QZegoAVSignal::OnLoginRoom(int errorCode, const char *pszRoomID, const LIVEROOM::ZegoStreamInfo *pStreamInfo, unsigned int streamCount)
{
	QString strRoomID = pszRoomID ? pszRoomID : "";

	QVector<StreamPtr> vStreamList;

	for (int i = 0; i < streamCount; i++)
	{
		LIVEROOM::ZegoStreamInfo zegoStreamInfo = pStreamInfo[i];
		StreamPtr pStream(new QZegoStreamModel(zegoStreamInfo.szStreamId, zegoStreamInfo.szUserId, zegoStreamInfo.szUserName, zegoStreamInfo.szExtraInfo));
		vStreamList.push_back(pStream);
	}

	emit sigLoginRoom(errorCode, strRoomID, vStreamList);
	
}

void QZegoAVSignal::OnLogoutRoom(int errorCode, const char *pszRoomID)
{
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigLogoutRoom(errorCode, strRoomID);
	
}

void QZegoAVSignal::OnDisconnect(int errorCode, const char *pszRoomID)
{
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigDisconnect(errorCode, strRoomID);
	
}

void QZegoAVSignal::OnKickOut(int reason, const char *pszRoomID)
{
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigKickOut(reason, strRoomID);
	
}

void QZegoAVSignal::OnSendRoomMessage(int errorCode, const char *pszRoomID, int sendSeq, unsigned long long messageId)
{
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigSendRoomMessage(errorCode, strRoomID, sendSeq, messageId);
	
}

void QZegoAVSignal::OnRecvRoomMessage(ROOM::ZegoRoomMessage *pMessageInfo, unsigned int messageCount, const char *pszRoomID)
{
	if (pMessageInfo == nullptr || messageCount == 0)
	{
		return;
	}

	QString strRoomID = pszRoomID ? pszRoomID : "";

	QVector<RoomMsgPtr> vRoomMsgList;
	for (int i = 0; i < messageCount; i++)
	{
		ROOM::ZegoRoomMessage zegoRoomMessage = pMessageInfo[i];
		RoomMsgPtr pRoomMsg(new QZegoRoomMsgModel(zegoRoomMessage.szUserId, zegoRoomMessage.szUserName,
			zegoRoomMessage.szContent, zegoRoomMessage.messageId, zegoRoomMessage.type, zegoRoomMessage.priority, zegoRoomMessage.category));
		vRoomMsgList.push_back(pRoomMsg);
	}

	emit sigRecvRoomMessage(strRoomID, vRoomMsgList);
	
}

void QZegoAVSignal::OnStreamUpdated(LIVEROOM::ZegoStreamUpdateType type, LIVEROOM::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID)
{
	if (pStreamInfo == nullptr || streamCount == 0)
	{
		return;
	}

	QString strRoomID = pszRoomID ? pszRoomID : "";

	QVector<StreamPtr> vStreamList;
	for (int i = 0; i < streamCount; i++)
	{
		LIVEROOM::ZegoStreamInfo zegoStreamInfo = pStreamInfo[i];
		StreamPtr pStream(new QZegoStreamModel(zegoStreamInfo.szStreamId, zegoStreamInfo.szUserId, zegoStreamInfo.szUserName, zegoStreamInfo.szExtraInfo));
		vStreamList.push_back(pStream);
	}

	emit sigStreamUpdated(strRoomID, vStreamList, type);
	
}

void QZegoAVSignal::OnStreamExtraInfoUpdated(LIVEROOM::ZegoStreamInfo *pStreamInfo, unsigned int streamCount, const char *pszRoomID)
{
	if (pStreamInfo == nullptr || streamCount == 0)
	{
		return;
	}

	QString strRoomID = pszRoomID ? pszRoomID : "";

	QVector<StreamPtr> vStreamList;
	for (int i = 0; i < streamCount; i++)
	{
		LIVEROOM::ZegoStreamInfo zegoStreamInfo = pStreamInfo[i];
		StreamPtr pStream(new QZegoStreamModel(zegoStreamInfo.szStreamId, zegoStreamInfo.szUserId, zegoStreamInfo.szUserName, zegoStreamInfo.szExtraInfo));
		vStreamList.push_back(pStream);
	}

	emit sigStreamExtraInfoUpdated(strRoomID, vStreamList);
}

void QZegoAVSignal::OnPublishStateUpdate(int stateCode, const char* pszStreamID, const LIVEROOM::ZegoPublishingStreamInfo& oStreamInfo)
{

	QString strStreamID = pszStreamID ? pszStreamID : "";

	StreamPtr pStream(new QZegoStreamModel(strStreamID, "", "", "", true));

	for (unsigned int i = 0; i < oStreamInfo.uiRtmpURLCount; i++)
	{
		pStream->m_vecRtmpUrls.push_back(oStreamInfo.arrRtmpURLs[i]);
	}

	for (unsigned int i = 0; i < oStreamInfo.uiFlvURLCount; i++)
	{
		pStream->m_vecFlvUrls.push_back(oStreamInfo.arrFlvURLs[i]);
	}

	for (unsigned int i = 0; i < oStreamInfo.uiHlsURLCount; i++)
	{
		pStream->m_vecHlsUrls.push_back(oStreamInfo.arrHlsURLs[i]);
	}

	emit sigPublishStateUpdate(stateCode, strStreamID, pStream);
	
}

void QZegoAVSignal::OnPlayStateUpdate(int stateCode, const char* pszStreamID)
{
	QString strStreamID = pszStreamID ? pszStreamID : "";

	emit sigPlayStateUpdate(stateCode, strStreamID);
	
}

void QZegoAVSignal::OnPublishQulityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS)
{
	QString strStreamID = pszStreamID ? pszStreamID : "";
	//去掉StreamId后面CDN的地址
	//int index = strStreamID.indexOf("?");
	//strStreamID = strStreamID.left(index);
	
	emit sigPublishQualityUpdate(strStreamID, quality, videoFPS, videoKBS);
	
}

void QZegoAVSignal::OnPublishQualityUpdate(const char* pszStreamID, LIVEROOM::ZegoPublishQuality publishQuality)
{
	QString strStreamID = pszStreamID ? pszStreamID : "";
	int quality = publishQuality.quality;
	double capFPS = publishQuality.cfps;
	double videoFPS = publishQuality.fps;
	double videoKBS = publishQuality.kbps;
	double audioKBS = publishQuality.akbps;
	int rtt = publishQuality.rtt;
	int pktLostRate = publishQuality.pktLostRate;

	emit sigPublishQualityUpdate2(strStreamID, quality, capFPS, videoFPS, videoKBS, audioKBS, rtt, pktLostRate);
}

void QZegoAVSignal::OnPlayQualityUpdate(const char* pszStreamID, int quality, double videoFPS, double videoKBS)
{
	QString strStreamID = pszStreamID ? pszStreamID : "";
	//去掉StreamId后面CDN的地址
	//int index = strStreamID.indexOf("?");
	//strStreamID = strStreamID.left(index);

	emit sigPlayQualityUpdate(strStreamID, quality, videoFPS, videoKBS);
	
}

void QZegoAVSignal::OnAuxCallback(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels)
{
	int pDataLenValue = *pDataLen;
	//qDebug() << "pdataLen = " << *pDataLen;
	emit sigAuxInput(pData, pDataLen, pDataLenValue, pSampleRate, pNumChannels);
}

void QZegoAVSignal::OnJoinLiveRequest(int seq, const char *pszFromUserId, const char *pszFromUserName, const char *pszRoomID)
{
	QString strFromUserID = pszFromUserId ? pszFromUserId : "";
	QString strFromUserName = pszFromUserName ? pszFromUserName : "";
	QString strRoomID = pszRoomID ? pszRoomID : "";

	emit sigJoinLiveRequest(seq, strFromUserID, strFromUserName, strRoomID);

}

void QZegoAVSignal::OnJoinLiveResponse(int result, const char* pszFromUserId, const char* pszFromUserName, int seq)
{
	QString strFromUserID = pszFromUserId ? pszFromUserId : "";
	QString strFromUserName = pszFromUserName ? pszFromUserName : "";

    emit sigJoinLiveResponse(result, strFromUserID, strFromUserName, seq);
	
}

void QZegoAVSignal::OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, AV::DeviceInfo *deviceInfo, AV::DeviceState state)
{
	if (deviceInfo == nullptr)
		return;

	qDebug() << "audioDevice " << state;

	QString strDeviceId = deviceInfo->szDeviceId;
	QString strDeviceName = deviceInfo->szDeviceName;

	emit sigAudioDeviceChanged(deviceType, strDeviceId, strDeviceName, state);

}

void QZegoAVSignal::OnVideoDeviceStateChanged(AV::DeviceInfo *deviceInfo, AV::DeviceState state)
{
	if (deviceInfo == nullptr)
		return;

	QString strDeviceId = deviceInfo->szDeviceId;
	QString strDeviceName = deviceInfo->szDeviceName;
    
    qDebug() << "videoDevice " << state<<" video device id: "<<strDeviceId<<" name:"<<strDeviceName;
    
	emit sigVideoDeviceChanged(strDeviceId, strDeviceName, state);
	
}

void QZegoAVSignal::OnUserUpdate(const LIVEROOM::ZegoUserInfo *pUserInfo, unsigned int userCount, LIVEROOM::ZegoUserUpdateType type)
{
	QVector<QString> userIDs;
	QVector<QString> userNames;
	QVector<int> userFlags;
	QVector<int> userRoles;

	for (int i = 0; i < userCount; i++)
	{
		QString strUserId = pUserInfo[i].szUserId;
		QString strUserName = pUserInfo[i].szUserName;
		userIDs.push_back(strUserId);
		userNames.push_back(strUserName);
		userFlags.push_back(pUserInfo[i].udapteFlag);
		userRoles.push_back(pUserInfo[i].role);
	}

	emit sigUserUpdate(userIDs, userNames, userFlags, userRoles, userCount, type);
}

void QZegoAVSignal::OnMixStream(const AV::ZegoMixStreamResult& result, const char* pszMixStreamID, int seq)
{
	unsigned int errorCode = result.uiErrorCode;
	QString mixStreamID = pszMixStreamID ? pszMixStreamID : "";
	QString hlsUrl = result.oStreamInfo.arrHlsURLs[0];
	QString rtmpUrl = result.oStreamInfo.arrRtmpURLs[0];

	emit sigMixStream(errorCode, hlsUrl, rtmpUrl, mixStreamID, seq);
}

void QZegoAVSignal::OnMixStreamEx(const AV::ZegoMixStreamResultEx& result, const char* pszMixStreamID, int seq)
{
	unsigned int errorCode = result.uiErrorCode;
	int outputCount = result.nStreamInfoCount;
	QString mixStreamID = pszMixStreamID ? pszMixStreamID : "";

	QString hlsUrl = (outputCount > 0) ? result.pStreamInfoList[0].arrHlsURLs[0] : "url is null";
	QString rtmpUrl = (outputCount > 0) ? result.pStreamInfoList[0].arrRtmpURLs[0] : "url is null";

	emit sigMixStreamEx(errorCode, hlsUrl, rtmpUrl, mixStreamID, seq);
}

void QZegoAVSignal::OnRecvEndJoinLiveCommand(const char* pszFromUserId, const char* pszFromUserName, const char *pszRoomID)
{
	QString userId = pszFromUserId;
	QString userName = pszFromUserName;
	QString roomId = pszRoomID;
	
	emit sigRecvEndJoinLiveCommand(userId, userName, roomId);
}

void QZegoAVSignal::OnPreviewSnapshot(void *pImage)
{
	emit sigPreviewSnapshot(pImage);
}

void QZegoAVSignal::OnSnapshot(void *pImage, const char* pszStreamID)
{
	QString streamID = pszStreamID;
	emit sigSnapshot(pImage, streamID);
}

#ifdef USE_EXTERNAL_SDK
void QZegoAVSignal::OnSurfaceMergeResult(
	unsigned char *surfaceMergeData,
	int datalength,
	const AVE::VideoCaptureFormat& frameFormat,
	unsigned long long reference_time,
	unsigned int reference_time_scale)
{
	emit sigSurfaceMergeResult(surfaceMergeData, datalength);
}

#endif

void QZegoAVSignal::OnDeviceError(const char* deviceName, int errorCode)
{
	qDebug() << "deviceName = " << deviceName << " error = " << errorCode;
}

void QZegoAVSignal::OnSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pSoundLevelList, unsigned int soundLevelCount)
{

}

void QZegoAVSignal::OnCaptureSoundLevelUpdate(SOUNDLEVEL::ZegoSoundLevelInfo *pCaptureSoundLevel)
{
	if (!pCaptureSoundLevel)
		return;

	emit sigCaptureSoundLevelUpdate(pCaptureSoundLevel->soundLevel);
}
