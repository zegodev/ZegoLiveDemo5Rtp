#pragma once

#include "Settings/ZegoSettingsModel.h"
#include "Base/ZegoLiveDemoDefines.h"
#include <QSharedPointer>
#include <QFile>
#include <QSettings>

class QZegoUserConfig
{
public:
	QZegoUserConfig();
	~QZegoUserConfig();

	void LoadConfig(void);
	void SaveConfig(void);

	QString GetUserId(void);
	QString GetUserIdWithRole(void);
	void SetUserId(const QString strUserId);
	
	QString getUserName(void);
	void SetUserName(const QString strUserName);

	bool IsPrimary(void);
	void SetUserRole(bool primary);

	VideoQuality GetVideoQuality(void);
	void SetVideoQuality(VideoQuality quality);

	SettingsPtr GetVideoSettings(void);
	void SetVideoSettings(SettingsPtr curSettings);

	bool GetUseTestEnv();
	void SetUseTestEnv(bool isUseTestEnv);

	AppConfig GetAppConfig();
	void SetAppId(unsigned long appid);
	void SetAppSign(QString appsign);

	int GetAppVersion();
	void SetAppVersion(int ver);

	bool GetUseVerticalCapture();
	void SetUseVerticalCapture(bool isVerticalCapture);

	bool GetUseExternalCaptureAndRender();
	void SetUseExternalCaptureAndRender(bool bUse);

private:
	bool LoadConfigInternal(void);

private:
	QString m_strIniPath;

	QString m_strUserId;
	QString m_strUserName;

	
	bool m_bPrimary;
	bool m_isUseTestEnv;

	bool m_isUseExternalCapture;

	SettingsPtr m_pVideoSettings;

	AppConfig m_customAppConfig;
	int m_appVersion;

	bool m_isVerticalCapture;
};
