#include "ZegoSettingsModel.h"

//默认的索引组合类型（视频质量的组合）
static IndexSet g_PrimaryDefConf[] = { { 8, 17, 3 }, { 5, 15, 3 }, { 4, 11, 3 }, { 2, 6, 3 }, { 1, 5, 3 }, { 0, 0, 3 } };

QZegoSettingsModel::QZegoSettingsModel()
{
	m_index = { 8, 12, 3 };
	InitDeviceId();
}

QZegoSettingsModel::QZegoSettingsModel(const IndexSet& index)
{
	m_index = index;
	InitByIndex();
	InitDeviceId();
}

void QZegoSettingsModel::SetResolution(Size resolution)
{
	m_sizeResolution = resolution;
	for (int i = 0; i < sizeof(g_Resolution) / sizeof(g_Resolution[0]); i++)
	{
		if (g_Resolution[i].cx == resolution.cx &&
			g_Resolution[i].cy == resolution.cy)
		{
			m_index.indexResolution = i;
			break;
		}
	}
}

Size QZegoSettingsModel::GetResolution(void)
{
	return m_sizeResolution;
}

void QZegoSettingsModel::SetBitrate(int bitrate)
{
	m_nBitrate = bitrate;
	for (int i = 0; i < sizeof(g_Bitrate) / sizeof(g_Bitrate[0]); i++)
	{
		if (g_Bitrate[i] == bitrate)
		{
			m_index.indexBitrate = i;
			break;
		}
	}
}

int  QZegoSettingsModel::GetBitrate(void)
{
	return m_nBitrate;
}

void QZegoSettingsModel::SetFps(int fps)
{
	m_nFps = fps;
	for (int i = 0; i < sizeof(g_Fps) / sizeof(g_Fps[0]); i++)
	{
		if (g_Fps[i] == fps)
		{
			m_index.indexFps = i;
			break;
		}
	}
}

int  QZegoSettingsModel::GetFps(void)
{
	return m_nFps;
}

void QZegoSettingsModel::SetCameraId(const QString& cameraId)
{
	m_strCameraId = cameraId;
}

QString QZegoSettingsModel::GetCameraId(void)
{
	return m_strCameraId;
}

QString QZegoSettingsModel::GetCameraId2(void)
{
	return m_strCameraId2;
}

void QZegoSettingsModel::SetCameraId2(const QString& cameraId)
{
	m_strCameraId2 = cameraId;
}

void QZegoSettingsModel::SetMicrophoneId(const QString& microphoneId)
{
	m_strMicrophoneId = microphoneId;
}

QString QZegoSettingsModel::GetMircophoneId(void)
{
	return m_strMicrophoneId;
}

//通过索引初始化
void QZegoSettingsModel::InitByIndex(void)
{
	m_sizeResolution = g_Resolution[m_index.indexResolution];
	m_nBitrate = g_Bitrate[m_index.indexBitrate];
	m_nFps = g_Fps[m_index.indexFps];
}

void QZegoSettingsModel::InitDeviceId(void)
{
	int nDeviceCount(0);
	AV::DeviceInfo* pDeviceList(NULL);

	pDeviceList = LIVEROOM::GetAudioDeviceList(ZEGO::AV::AudioDevice_Input, nDeviceCount);
	if (nDeviceCount > 0 && pDeviceList != NULL)
		m_strMicrophoneId = pDeviceList[0].szDeviceId;
	LIVEROOM::FreeDeviceList(pDeviceList);
	pDeviceList = NULL;

	pDeviceList = LIVEROOM::GetVideoDeviceList(nDeviceCount);
	if (nDeviceCount > 0 && pDeviceList != NULL)
		m_strCameraId = pDeviceList[0].szDeviceId;
	LIVEROOM::FreeDeviceList(pDeviceList);
	pDeviceList = NULL;
}

VideoQuality QZegoSettingsModel::GetQuality(bool primary)
{
	VideoQuality quality = VQ_SelfDef;

	//if (primary)
	//{
		for (int i = 0; i < sizeof(g_PrimaryDefConf) / sizeof(g_PrimaryDefConf[0]); i++)
		{
			if (g_PrimaryDefConf[i] == m_index)
			{
				quality = (VideoQuality)i;
				break;
			}
		}
	//}
	/*else
	{
		for (int i = 0; i < sizeof(g_StudentDefConf) / sizeof(g_StudentDefConf[0]); i++)
		{
			if (g_StudentDefConf[i] == m_index)
			{
				quality = (VideoQuality)i;
				break;
			}
		}
	}
	*/
	return quality;
}

void QZegoSettingsModel::SetQuality(bool primary, VideoQuality quality)
{
	if (quality == VQ_SelfDef)
	{
		return;
	}

	//if (primary)
	//{
		m_index = g_PrimaryDefConf[quality];
	//}
	/*else
	{
		m_index = g_StudentDefConf[quality];
	}*/

	InitByIndex();
}

IndexSet QZegoSettingsModel::getIndex()
{
	return m_index;
}

void QZegoSettingsModel::SetSurfaceMerge(bool isSurface)
{
	m_isUseSurfaceMerge = isSurface;
}

bool QZegoSettingsModel::GetSurfaceMerge(void)
{
	return m_isUseSurfaceMerge;
}

void QZegoSettingsModel::SetUsePublish2Stream(bool isPublish2Stream)
{
	m_isUsePublish2Stream = isPublish2Stream;
}

bool QZegoSettingsModel::GetUsePublish2Stream(void)
{
	return m_isUsePublish2Stream;
}