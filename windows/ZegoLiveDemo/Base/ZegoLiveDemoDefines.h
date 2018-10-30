#pragma once

#define mConfig theApp.GetConfig()
#define mBase theApp.GetBase()

#define MAX_VIEW_COUNT 12

/*#define BUILD_FOR_XP*/

#define m_FirstAnchor "first"
#define m_HlsKey "Hls"
#define m_RtmpKey "rtmp"
#define m_RoomName "RoomName"

struct AppConfig
{
	unsigned long m_customAppId;
	QString m_customAppSign;

	const AppConfig& operator=(const AppConfig& other)
	{
		if (this == &other)
		{
			return *this;
		}

		m_customAppId = other.m_customAppId;
		m_customAppSign = other.m_customAppSign;
		return *this;
	}

	bool operator==(const AppConfig& other)
	{
		if (m_customAppId == other.m_customAppId && m_customAppSign == other.m_customAppSign)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};