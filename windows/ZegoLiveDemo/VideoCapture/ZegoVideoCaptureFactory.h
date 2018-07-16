#pragma once

#include "video_capture.h"
#include <mutex>

class ZegoVideoCaptureFactory :
	public AVE::VideoCaptureFactory,
	public AVE::VideoCaptureDevice
{
public:
	ZegoVideoCaptureFactory();
	~ZegoVideoCaptureFactory();

	void SendCapturedDataToSDK(const char* data,
		int length,
		const AVE::VideoCaptureFormat& frame_format,
		unsigned long long reference_time,
		unsigned int reference_time_scale);

public:
	virtual int TakeSnapshot();
private:
	virtual AVE::VideoCaptureDeviceBase* Create(const char* device_id);
	virtual void Destroy(AVE::VideoCaptureDeviceBase *vc);

	virtual void AllocateAndStart(AVE::VideoCaptureDevice::Client* client);
	virtual void StopAndDeAllocate();

	virtual int StartCapture();
	virtual int StopCapture();
	virtual int SetFrameRate(int framerate);
	virtual int SetResolution(int width, int height);
	virtual int SetFrontCam(int bFront);
	virtual int SetView(void *view);
	virtual int SetViewMode(int nMode);
	virtual int SetViewRotation(int nRotation);
	virtual int SetCaptureRotation(int nRotation);
	virtual int StartPreview();
	virtual int StopPreview();
	virtual int EnableTorch(bool bEnable);
	virtual int SetPowerlineFreq(unsigned int nFreq);

private:
	std::mutex m_clientMutex;
	AVE::VideoCaptureDevice::Client *m_pClient = nullptr;

};