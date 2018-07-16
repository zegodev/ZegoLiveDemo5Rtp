#include "ZegoUserConfig.h"
#include "Base/ZegoBase.h"
#include <random>
#include <QSharedPointer>

QZegoUserConfig::QZegoUserConfig()
{
    //生成ini文件,用于在本地保存用户配置信息
	m_strIniPath =  "Config/ZegoUserConfig.ini";
}

QZegoUserConfig::~QZegoUserConfig()
{

}

void QZegoUserConfig::LoadConfig(void)
{
	if (LoadConfigInternal())
	{
		return;
	}

	//随机生成编号为10000000-99999999的用户ID
	std::random_device rd;
	std::uniform_int_distribution<int> dist(10000000, 99999999);
	//int to QString
	m_strUserId = QString::number(dist(rd), 10);
#ifdef Q_OS_WIN
	m_strUserName = "windows-" + m_strUserId;
#else
	m_strUserName = "mac-" + m_strUserId;
#endif
	m_bPrimary = true;
	m_isUseTestEnv = false;

	m_isVerticalCapture = false;

	m_appVersion = ZEGO_PROTOCOL_UDP;
	m_customAppConfig.m_customAppId = "";
	m_customAppConfig.m_customAppSign = "";

	if (m_pVideoSettings == nullptr)
	{
		m_pVideoSettings = SettingsPtr::create();
	}

	m_pVideoSettings->SetQuality(m_bPrimary, VQ_Middle);

	SaveConfig();
}

bool QZegoUserConfig::LoadConfigInternal(void)
{
	QSettings *configIni = new QSettings(m_strIniPath, QSettings::IniFormat);
	if (configIni == nullptr)
	{
		return false;
	}

	QString strUserId = configIni->value("/sUserRecords/kUserId").toString();
	QString strUserName = configIni->value("/sUserRecords/kUserName").toString();

	int nRole = configIni->value("/sUserRecords/kIsPrimary").toInt();
	if (strUserId.isEmpty() || strUserName.isEmpty() || nRole == 0)
	{
		return false;
	}

	Size sizeResolution;
	sizeResolution.cx = configIni->value("/sUserRecords/kResolutionX").toLongLong();
	sizeResolution.cy = configIni->value("/sUserRecords/kResolutionY").toLongLong();
	int nBitrate = configIni->value("/sUserRecords/kBitrate").toInt();
	int nFps = configIni->value("/sUserRecords/kFps").toInt();
	bool nIsUseTest = configIni->value("/sUserRecords/kIsTestEnv").toBool();

	bool nIsVerticalCapture = configIni->value("/sUserRecords/kIsVerticalCapture").toBool();

	int nAppVer = configIni->value("/sUserRecords/kAppVersion").toInt();
	QString nAppId = configIni->value("/sUserRecords/kAppId").toString();
	QString nAppSign = configIni->value("/sUserRecords/kAppSign").toString();
	//读ini文件完毕后释放指针
	delete configIni;

	if (sizeResolution.cx == 0 || sizeResolution.cy == 0 || nBitrate == 0 || nFps == 0)
	{
		return false;
	}

	m_strUserId = strUserId;
	m_strUserName = strUserName;
	//m_bPrimary = nRole == 1;
	m_bPrimary = true;
	m_isUseTestEnv = nIsUseTest;
	m_isVerticalCapture = nIsVerticalCapture;

	m_appVersion = nAppVer;
	m_customAppConfig.m_customAppId = nAppId;
	m_customAppConfig.m_customAppSign = nAppSign;

	if (m_pVideoSettings == nullptr)
	{
		m_pVideoSettings = SettingsPtr::create();
	}
	m_pVideoSettings->SetResolution(sizeResolution);
	m_pVideoSettings->SetBitrate(nBitrate);
	m_pVideoSettings->SetFps(nFps);
	return true;
}
void QZegoUserConfig::SaveConfig()
{
	QSettings *configIni = new QSettings(m_strIniPath, QSettings::IniFormat);
	if (m_strUserId.isEmpty() || m_strUserName.isEmpty() || m_pVideoSettings == nullptr)
	{
		return;
	}

	configIni->setValue("/sUserRecords/kUserId", m_strUserId);
	configIni->setValue("/sUserRecords/kUserName", m_strUserName);
	configIni->setValue("/sUserRecords/kIsPrimary", m_bPrimary ? 1 : 2);

	configIni->setValue("/sUserRecords/kResolutionX", m_pVideoSettings->GetResolution().cx);
	configIni->setValue("/sUserRecords/kResolutionY", m_pVideoSettings->GetResolution().cy);
	configIni->setValue("/sUserRecords/kBitrate", m_pVideoSettings->GetBitrate());
	configIni->setValue("/sUserRecords/kFps", m_pVideoSettings->GetFps());
	configIni->setValue("/sUserRecords/kIsTestEnv", m_isUseTestEnv);

	configIni->setValue("/sUserRecords/kAppVersion", m_appVersion);
	configIni->setValue("/sUserRecords/kAppId", m_customAppConfig.m_customAppId);
	configIni->setValue("/sUserRecords/kAppSign", m_customAppConfig.m_customAppSign);

	configIni->setValue("/sUserRecords/kIsVerticalCapture", m_isVerticalCapture);

	delete configIni;

}

QString QZegoUserConfig::GetUserId(void)
{
	return m_strUserId;
}

QString QZegoUserConfig::GetUserIdWithRole(void)
{
	QString strUserIdWithRole = m_strUserId;
	if (m_bPrimary)
	{
		strUserIdWithRole += "_primary";
	}
	return strUserIdWithRole;
}

void QZegoUserConfig::SetUserId(QString strUserId)
{
	if (!strUserId.isEmpty())
	{
		m_strUserId = strUserId;
	}
}

QString QZegoUserConfig::getUserName(void)
{
	return m_strUserName;
}

void QZegoUserConfig::SetUserName(QString strUserName)
{
	if (!strUserName.isEmpty())
	{
		m_strUserName = strUserName;
	}
}

bool QZegoUserConfig::IsPrimary(void)
{
	return m_bPrimary;
}

void QZegoUserConfig::SetUserRole(bool primary)
{
	if (m_bPrimary == primary)
	{
		return;
	}

	if (m_pVideoSettings != nullptr)
	{
		VideoQuality quality = m_pVideoSettings->GetQuality(m_bPrimary);
		if (quality != VQ_SelfDef)
		{
			m_pVideoSettings->SetQuality(primary, quality);
		}
	}

	m_bPrimary = primary;
}

VideoQuality QZegoUserConfig::GetVideoQuality(void)
{
	if (m_pVideoSettings != nullptr)
	{
		return m_pVideoSettings->GetQuality(m_bPrimary);
	}
	return VQ_SelfDef;
}

void QZegoUserConfig::SetVideoQuality(VideoQuality quality)
{
	if (m_pVideoSettings != nullptr)
	{
		m_pVideoSettings->SetQuality(m_bPrimary, quality);
	}
}

SettingsPtr QZegoUserConfig::GetVideoSettings(void)
{
	return m_pVideoSettings;
}

void QZegoUserConfig::SetVideoSettings(SettingsPtr curSettings)
{
	m_pVideoSettings->SetResolution(curSettings->GetResolution());
	m_pVideoSettings->SetBitrate(curSettings->GetBitrate());
	m_pVideoSettings->SetFps(curSettings->GetFps());
	m_pVideoSettings->SetMicrophoneId(curSettings->GetMircophoneId());
	m_pVideoSettings->SetCameraId(curSettings->GetCameraId());
	m_pVideoSettings->SetCameraId2(curSettings->GetCameraId2());
	//m_pVideoSettings->SetQuality(curSettings->GetQuality());
}

bool QZegoUserConfig::GetUseTestEnv()
{
	return m_isUseTestEnv;
}

void QZegoUserConfig::SetUseTestEnv(bool isUseTestEnv)
{
	m_isUseTestEnv = isUseTestEnv;
}

AppConfig QZegoUserConfig::GetAppConfig()
{
	return m_customAppConfig;
}

void QZegoUserConfig::SetAppId(QString appid)
{
	m_customAppConfig.m_customAppId = appid;
}

void QZegoUserConfig::SetAppSign(QString appsign)
{
	m_customAppConfig.m_customAppSign = appsign;
}

int QZegoUserConfig::GetAppVersion()
{
	return m_appVersion;
}

void QZegoUserConfig::SetAppVersion(int ver)
{
	m_appVersion = ver;
}

bool QZegoUserConfig::GetUseVerticalCapture()
{
	return m_isVerticalCapture;
}

void QZegoUserConfig::SetUseVerticalCapture(bool isVerticalCapture)
{
	m_isVerticalCapture = isVerticalCapture;
}

bool QZegoUserConfig::GetUseExternalCaptureAndRender()
{
	return m_isUseExternalCapture;
}

void QZegoUserConfig::SetUseExternalCaptureAndRender(bool bUse)
{
	m_isUseExternalCapture = bUse;
}
