#pragma once

#include <QObject>
#include "LiveRoom.h"
#include "LiveRoom-IM.h"
#include "LiveRoom-Publisher.h"
#include "LiveRoom-Player.h"
#include "LiveRoomDefines.h"
#include "LiveRoomDefines-IM.h"

using namespace ZEGO;

typedef struct resolutionSIZE
{
	qlonglong cx;
	qlonglong cy;
}Size;

//视频质量的枚举类型
typedef enum _VideoQuality
{
	VQ_SuperLow = 0,
	VQ_Low = 1,
	VQ_Middle = 2,
	VQ_High = 3,
	VQ_SuperHigh = 4,
	VQ_ExtremelyHigh = 5,
	VQ_SelfDef = 6,
}VideoQuality;

//分辨率
/*static Size g_Resolution[] =
{
	{ 1920, 1200 }, { 1728, 1080 }, { 1644, 1028 }, { 1440, 900 }, { 1280, 800 }, { 1152, 720 },
	{ 1044, 654 }, { 720, 640 }, { 640, 480 }, { 480, 320 }, { 320, 240 }, { 160, 120 },
};*/
static Size g_Resolution[] = 
{
	{ 1920, 1080 }, { 1280, 720 }, { 960, 540 }, { 640, 480 }, { 640, 360 }, 
	 { 480, 270 },   { 352, 288 }, { 320, 240 }, { 320, 180 }, { 176, 144 }
};

/*static SIZE g_Resolution[] =
{
	{ 1200, 1920 }, { 1080, 1728 }, { 1028, 1644 }, { 900, 1440 }, { 800, 1280 }, { 720, 1152 },
	{ 654, 1044 }, { 640, 720 }, { 480, 640 }, { 320, 480 }, { 240, 320 }, { 120, 160 },
};*/

/*static SIZE g_Resolution[] =
{
	{ 1920, 1080 }, { 1080, 1728 }, { 1028, 1644 }, { 900, 1440 }, { 800, 1280 }, { 720, 1152 },
	{ 654, 1044 }, { 640, 720 }, { 480, 640 }, { 320, 480 }, { 240, 320 }, { 120, 160 },
};*/

//码率
static int g_Bitrate[] =
{
	4000 * 1000, 3000 * 1000, 2200 * 1000, 2000 * 1000, 1800 * 1000, 
	1500 * 1000, 1200 * 1000, 1000 * 1000,  800 * 1000,  700 * 1000,  
	 650 * 1000,  600 * 1000,  550 * 1000,  500 * 1000,  450 * 1000,  
	 400 * 1000,  350 * 1000,  300 * 1000,  250 * 1000,  180 * 1000,  
	 150 * 1000,  120 * 1000,  100 * 1000,
};

//帧率
static int g_Fps[] = { 30, 25, 20, 15, 10, 5 };

//宏定义三种视频属性的长度-1
#define g_Resolution_length (sizeof(g_Resolution) / sizeof(g_Resolution[0])) - 1
#define g_Bitrate_length (sizeof(g_Bitrate) / sizeof(g_Bitrate[0])) - 1
#define g_FPS_length (sizeof(g_Fps) / sizeof(g_Fps[0])) - 1


//三种属性的索引结构体
struct IndexSet
{
	unsigned int indexResolution;
	unsigned int indexBitrate;
	unsigned int indexFps;

	bool operator ==(const IndexSet& otherSet)
	{
		return indexResolution == otherSet.indexResolution &&
			indexBitrate == otherSet.indexBitrate &&
			indexFps == otherSet.indexFps;
	}
};

class QZegoSettingsModel
{
public:
	QZegoSettingsModel();
	QZegoSettingsModel(const IndexSet& index);

	VideoQuality GetQuality(bool primary);
	void SetQuality(bool primary, VideoQuality quality);

	Size GetResolution(void);
	void SetResolution(Size resolution);

	int  GetBitrate(void);
	void SetBitrate(int bitrate);

	int  GetFps(void);
	void SetFps(int fps);

	QString GetCameraId(void);
	void SetCameraId(const QString& cameraId);

	QString GetCameraId2(void);
	void SetCameraId2(const QString& cameraId);

	QString GetMircophoneId(void);
	void SetMicrophoneId(const QString& microphoneId);

	void SetSurfaceMerge(bool isSurface);
	bool GetSurfaceMerge(void);

	void SetUsePublish2Stream(bool isPublish2Stream);
	bool GetUsePublish2Stream(void);

	void InitDeviceId(void);

	IndexSet getIndex();
private:
	void InitByIndex(void);

	IndexSet m_index;
	Size m_sizeResolution;
	int m_nBitrate;
	int m_nFps;
	QString m_strCameraId;
	QString m_strCameraId2;
	QString m_strMicrophoneId;
	//是否使用截屏推流
	bool m_isUseSurfaceMerge = false;
	//是否使用推两路流
	bool m_isUsePublish2Stream = false;
};

using SettingsPtr = QSharedPointer< QZegoSettingsModel >;
