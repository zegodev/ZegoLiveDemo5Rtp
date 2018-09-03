#pragma once

#include <QObject>
#include <QVector>
#include "AVDefines.h"
#include "LiveRoom.h"
#include "zego-api-sound-level.h"

using namespace ZEGO;

struct QDeviceInfo
{
	QString deviceId;
	QString deviceName;
};

enum QDeviceType
{
	TYPE_AUDIO = 0,
	TYPE_VIDEO
};

enum QDeviceState
{
	STATE_ERROR = -1,
	STATE_NORMAL,
	STATE_SWAP
};

class ZegoDeviceManager : public QObject
{
	Q_OBJECT

signals:
	void sigDeviceAdded(int type, QString deviceName);
	void sigDeviceDeleted(int type, int index);

	void sigDeviceNone(int type);
	void sigDeviceExist(int type);

public:
	ZegoDeviceManager();
	~ZegoDeviceManager();

	void EnumAudioDeviceList();
	void EnumVideoDeviceList();
	QDeviceState SetMicrophoneIdByIndex(int index);
	QDeviceState SetCameraIdByIndex(int index);
	QDeviceState SetCameraId2ByIndex(int index);

	int GetAudioDeviceIndex();
	int GetVideoDeviceIndex();
	int GetVideoDevice2Index();

	void SetMicVolume(int volume);
	int GetMicVolume();

	void SetPlayVolume(int volume);
	int GetPlayVolume();

	void SetMicEnabled(bool isUse);
	bool GetMicEnabled();

	void SetSpeakerEnabled(bool isUse);
	bool GetSpeakerEnabled();

	void SetCameraEnabled(bool isUse);
	bool GetCameraEnabled();

	QVector<QDeviceInfo> GetAudioDeviceList();
	QVector<QDeviceInfo> GetVideoDeviceList();

	const QString& GetAudioDeviceId();
	const QString& GetVideoDeviceId();
	const QString& GetVideoDeviceId2();

	void StartMicCaptureMonitor(int cycle = 200);
	void StopMicCaptureMonitor();

signals:
	void sigCameraIdChanged(QString deviceId);
	void sigCameraId2Changed(QString deviceId);
	void sigMicIdChanged(QString deviceId);

	void sigMicCaptureSoundLevelUpdate(float soundlevel);

protected slots:
	void OnAudioDeviceStateChanged(AV::AudioDeviceType deviceType, const QString& strDeviceId, const QString& strDeviceName, AV::DeviceState state);
	void OnVideoDeviceStateChanged(const QString& strDeviceId, const QString& strDeviceName, AV::DeviceState state);

	void OnMicCaptureSoundLevelUpdate(float soundlevel);
private:
	void RefreshCameraIndex();
	void RefreshMicIndex();

private:
	QVector<QDeviceInfo> m_audioDeviceList;
	QVector<QDeviceInfo> m_videoDeviceList;

	QString m_audioDeviceId;
	QString m_videoDeviceId;
	QString m_videoDeviceId2;

	int m_micVolume = 100;
	int m_playVolume = 100;

    bool m_micEnabled = true;
	bool m_speakerEnabled = true;
	bool m_cameraEnabled = true;
	bool m_camera2Enabled = true;

	int m_micListIndex = -1;
	int m_cameraListIndex = -1;
	int m_camera2ListIndex = -1;
};
