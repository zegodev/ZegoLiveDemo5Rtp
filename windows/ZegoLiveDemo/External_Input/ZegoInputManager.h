#pragma once

#include "VideoCapture/ZegoCamera.h"
#include "zego-api-external-audio-device.h"
#include "Model/ZegoVideoFrame.h"

#include <mutex>
class ZegoInputManager : public QObject
{

	Q_OBJECT

public:
	ZegoInputManager();
	~ZegoInputManager();

	void Init();
	void Uninit();

	// * camera 
    int SetCameraDeviceID(std::string device_id);
    int SetCameraFPS(int fps);
	void SetCameraResolution(QSize size);
	void StartCameraCapture();
	void StopCameraCapture();
	VideoFrame GetCamFrame();

	//audio
	void LoadPCM();
	void StartAudioCapture();
	void StopAudioCapture();

private:
	// * Camera Callback
    void OnCamVideoFrame(VideoFrame f);
    void OnCamDeviceError(const char *deviceId, const char *reason);
    
private slots:
	void OnAudioDataCaptured();

private:
	//外部视频采集相关参数
	ZegoVideoCapExternal *m_pCamera = nullptr;

    std::mutex cam_frame_lock_;
	VideoFrame cam_frame_;

	//缓存上次设置的Camera参数
	int m_fps = 15;
	QSize m_resolution = { 640, 360 };
	//---------------------

	//外部音频采集相关参数
	//ZegoAudioCaptureFactory *m_audio_factory = nullptr;
	AVE::IAudioDataInOutput *m_audio_factory = nullptr;

	int m_nPcmDataLen = 0;
	unsigned char* m_PcmData = nullptr;
	int m_pcmDataPos = 0;

	AVE::AudioFrame m_audio_frame;
	QTimer *m_audio_capture_timer = nullptr;
	QThread *m_audio_capture_thread = nullptr;
	//-------------------
};