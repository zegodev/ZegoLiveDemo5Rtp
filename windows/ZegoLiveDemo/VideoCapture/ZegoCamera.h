#pragma once

#include "video_capture.h"
#include <string>
#include <functional>
#include "Model/ZegoVideoFrame.h"

using OnCaptureDeviceErrorDelegate = std::function<void(const char *deviceId, const char *reason)>;

/*
1. control camera
    - select device
    - set fps
    - set resolution 
    - start cap
    - stop cap

2. callback 
    - video frame data
    - device error
*/

class ZegoVideoCapExternal
{
public:
	ZegoVideoCapExternal() {}
	~ZegoVideoCapExternal() {}

public:
    void SetOnVideoFrameDelegate(OnVideoFrameDelegate d) {
        on_video_frame_delegate_ = d;
    }

    void SetOnCaptureDeviceErrorDelegate(OnCaptureDeviceErrorDelegate d) {
        on_device_error_delegate_ = d;
    }

	std::string GetDeviceId();

	int SetCamera(std::string deviceId);
	int RemoveCamera();

	int StartCapture();
	int StopCapture();

	int SetFrameRate(int framerate);

	int SetCameraResolution(int width, int height);

public:
	void OnCaptureDeviceError(const std::string& deviceId, const char* reason);
	void OnIncommingCaptureData(const std::string& deviceId,
		const char* data,
		int length,
		const AVE::VideoCaptureFormat& frame_format,
		unsigned long long reference_time,
		unsigned int reference_time_scale);
	void OnTakeSnapshot(void* image);

private:
	struct CameraDeviceInfo
	{
		CameraDeviceInfo()
		{
			Reset();
		}

		~CameraDeviceInfo()
		{
			Reset();
		}

		void Reset()
		{
			cameraDevice = nullptr;
			isCapture = false;
		}

		AVE::Camera *cameraDevice;
		bool isCapture;
	};

private:
    OnVideoFrameDelegate on_video_frame_delegate_;
    OnCaptureDeviceErrorDelegate on_device_error_delegate_;
	std::string m_deviceId;
	CameraDeviceInfo m_deviceInfo;
};

