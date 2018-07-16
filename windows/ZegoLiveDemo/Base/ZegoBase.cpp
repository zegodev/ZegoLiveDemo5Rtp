#include <QSharedPointer>
#include "ZegoBase.h"
#include <QDebug>

#include "./IncludeZegoLiveRoomApi.h"
#include "zego-api-external-audio-device.h"

/**
 * Please contact ZEGO support to get the AppID and signKey
 * 请开发者联系 ZEGO support 获取 APPID 与 signKey
**/
static unsigned long g_dwAppID_Udp = 10;
static unsigned char g_bufSignKey_Udp[] =
{
	0x00
};

static unsigned long g_dwAppID_International = 100;
static unsigned char g_bufSignKey_International[] =
{ 
	0x00
};

static unsigned long  g_dwAppID_Custom = 0;
static unsigned char g_bufSignKey_Custom[] =
{
	0x0
};

QZegoBase::QZegoBase(void) : m_dwInitedMask(INIT_NONE)
{
	//日志存放的路径
	//m_strLogPathUTF8 = QDir::currentPath() + "/ZegoLog/";
	appIDs.push_back(g_dwAppID_Udp);
	appIDs.push_back(g_dwAppID_International);
	//appIDs.push_back(g_dwAppID_Wawaji);
	appIDs.push_back(g_dwAppID_Custom);

	appSigns.push_back(g_bufSignKey_Udp);
	appSigns.push_back(g_bufSignKey_International);
	//appSigns.push_back(g_bufSignKey_Wawaji);
	appSigns.push_back(g_bufSignKey_Custom);

	m_pAVSignal = new QZegoAVSignal;

}

QZegoBase::~QZegoBase(void)
{
	UninitAVSDK();
	delete m_pAVSignal;
}

bool QZegoBase::InitAVSDK(QString userID, QString userName)
{
	if (!IsAVSdkInited())
	{
		qDebug() << "SDK init";
		//Qstring对象.toLocal8Bit().data()用于将QString转为const char*
		LIVEROOM::SetLogDir(nullptr);
		LIVEROOM::SetVerbose(true);
		LIVEROOM::SetBusinessType(0);
		LIVEROOM::SetUser(qtoc(userID), qtoc(userName));
		// ToDo: 需要通过代码获取网络类型
		LIVEROOM::SetNetType(2);

		//是否使用测试环境
		LIVEROOM::SetUseTestEnv(isTestEnv);

		//是否使用外部采集
		if (isVideoCapture)
		{
			g_captureFactory = new ZegoVideoCaptureFactory;
			AUDIODEVICE::EnableExternalAudioDevice(true);
		}
		else
		{
			g_captureFactory = NULL;
		}
		LIVEROOM::SetVideoCaptureFactory(g_captureFactory);

		//是否使用外部滤镜
		if (isVideoFilter)
		{
			g_filterFactory = new VideoFilterFactoryGlue;
		}
		else
		{
			g_filterFactory = NULL;
		}
		LIVEROOM::SetVideoFilterFactory(g_filterFactory);

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
		//是否使用截屏推流
		if (isSurfaceMerge)
			SurfaceMergeController::getInstance().init();
#endif
		//设置回调
		LIVEROOM::SetLivePublisherCallback(m_pAVSignal);
		LIVEROOM::SetLivePlayerCallback(m_pAVSignal);
		LIVEROOM::SetRoomCallback(m_pAVSignal);
		LIVEROOM::SetIMCallback(m_pAVSignal);
		LIVEROOM::SetDeviceStateCallback(m_pAVSignal);
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
		SurfaceMergeController::getInstance().setMergeCallback(m_pAVSignal);
#endif
		LIVEROOM::InitSDK(appIDs[key], appSigns[key], 32);
	}

	//为了调用OnUserUpdate
	LIVEROOM::SetRoomConfig(true, true);

	m_dwInitedMask |= INIT_AVSDK;
	return true;
}

bool QZegoBase::InitAVSDKwithCustomAppId(QString userID, QString userName, unsigned int app_id, unsigned char *app_sign)
{
	if (!IsAVSdkInited())
	{
		qDebug() << "SDK init";
		//Qstring对象.toLocal8Bit().data()用于将QString转为const char*
		LIVEROOM::SetLogDir(nullptr);
		LIVEROOM::SetVerbose(true);
		LIVEROOM::SetBusinessType(0);
		LIVEROOM::SetUser(qtoc(userID), qtoc(userName));
		// ToDo: 需要通过代码获取网络类型
		LIVEROOM::SetNetType(2);

		//是否使用测试环境
		LIVEROOM::SetUseTestEnv(isTestEnv);

		//是否使用外部采集
		if (isVideoCapture)
		{
			g_captureFactory = new ZegoVideoCaptureFactory;
			AUDIODEVICE::EnableExternalAudioDevice(true);
		}
		else
		{
			g_captureFactory = NULL;
		}
		LIVEROOM::SetVideoCaptureFactory(g_captureFactory);

		//是否使用外部滤镜
		if (isVideoFilter)
		{
			g_filterFactory = new VideoFilterFactoryGlue;
		}
		else
		{
			g_filterFactory = NULL;
		}
		LIVEROOM::SetVideoFilterFactory(g_filterFactory);

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
		//是否使用截屏推流
		if (isSurfaceMerge)
			SurfaceMergeController::getInstance().init();
#endif
		//设置回调
		LIVEROOM::SetLivePublisherCallback(m_pAVSignal);
		LIVEROOM::SetLivePlayerCallback(m_pAVSignal);
		LIVEROOM::SetRoomCallback(m_pAVSignal);
		LIVEROOM::SetIMCallback(m_pAVSignal);
		LIVEROOM::SetDeviceStateCallback(m_pAVSignal);
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
		SurfaceMergeController::getInstance().setMergeCallback(m_pAVSignal);
#endif
		LIVEROOM::InitSDK(app_id, app_sign, 32);
	}

	//为了调用OnUserUpdate
	LIVEROOM::SetRoomConfig(true, true);

	m_dwInitedMask |= INIT_AVSDK;
	return true;
}

void QZegoBase::UninitAVSDK(void)
{
	if (IsAVSdkInited())
	{
		qDebug() << "SDK uninit";
		LIVEROOM::SetLivePublisherCallback(nullptr);
		LIVEROOM::SetLivePlayerCallback(nullptr);
		LIVEROOM::SetRoomCallback(nullptr);
		LIVEROOM::SetIMCallback(nullptr);
		LIVEROOM::SetDeviceStateCallback(nullptr);
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
		SurfaceMergeController::getInstance().setMergeCallback(nullptr);
#endif

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE) 
		if (isSurfaceMerge)
			SurfaceMergeController::getInstance().uninit();
#endif
		LIVEROOM::UnInitSDK();

		if (g_captureFactory)
		{
			AUDIODEVICE::EnableExternalAudioDevice(false);
			LIVEROOM::SetVideoCaptureFactory(nullptr);
			delete g_captureFactory;
			g_captureFactory = nullptr;
		}

		if (g_filterFactory)
		{
			LIVEROOM::SetVideoFilterFactory(nullptr);
			delete g_filterFactory;
			g_filterFactory = nullptr;
		}

		unsigned long dwNegation = ~(unsigned long)INIT_AVSDK;
		m_dwInitedMask &= dwNegation;
	}
}

bool QZegoBase::IsAVSdkInited(void)
{
	return (m_dwInitedMask & INIT_AVSDK) == INIT_AVSDK;
}

QZegoAVSignal* QZegoBase::GetAVSignal(void)
{
	return m_pAVSignal;
}

ZegoVideoCaptureFactory * QZegoBase::GetVideoFactory()
{
	return g_captureFactory;
}

unsigned long QZegoBase::GetAppID(void)
{
	return appIDs[key];
}

unsigned char* QZegoBase::GetAppSign()
{
	return appSigns[key];
}

void QZegoBase::setKey(int pKey)
{
	key = pKey;
}

int QZegoBase::getKey()
{
	return key;
}

void QZegoBase::setTestEnv(bool isTest)
{
	isTestEnv = isTest;
}

void QZegoBase::setUseVideoCapture(bool isCapture)
{
	isVideoCapture = isCapture;
}

void QZegoBase::setUseVideoFilter(bool isFilter)
{
	isVideoFilter = isFilter;
}

void QZegoBase::setUseSurfaceMerge(bool isSurface)
{
	isSurfaceMerge = isSurface;
}

bool QZegoBase::GetUseSurfaceMerge()
{
	return isSurfaceMerge;
}
