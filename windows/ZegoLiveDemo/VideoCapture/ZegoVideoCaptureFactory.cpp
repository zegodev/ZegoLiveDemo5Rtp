#include "ZegoVideoCaptureFactory.h"
#include "Base/IncludeZegoLiveRoomApi.h"

ZegoVideoCaptureFactory::ZegoVideoCaptureFactory()
{

}

ZegoVideoCaptureFactory::~ZegoVideoCaptureFactory()
{

}

void ZegoVideoCaptureFactory::SendCapturedDataToSDK(const char* data,
	int length,
	const AVE::VideoCaptureFormat& frame_format,
	unsigned long long reference_time,
	unsigned int reference_time_scale)
{
	if (!m_pClient)
		return;

	m_pClient->OnIncomingCapturedData(data, length, frame_format, reference_time, reference_time_scale);
}

AVE::VideoCaptureDeviceBase* ZegoVideoCaptureFactory::Create(const char* device_id)
{
	log_string_notice(__FUNCTION__);
	return this;
}

void ZegoVideoCaptureFactory::Destroy(AVE::VideoCaptureDeviceBase *vc)
{
	log_string_notice(__FUNCTION__);
}

void ZegoVideoCaptureFactory::AllocateAndStart(AVE::VideoCaptureDevice::Client* client)
{
	log_string_notice(__FUNCTION__);

	std::lock_guard<std::mutex> lg(m_clientMutex);
	m_pClient = client;
}

void ZegoVideoCaptureFactory::StopAndDeAllocate()
{
	log_string_notice(__FUNCTION__);

	std::lock_guard<std::mutex> lg(m_clientMutex);

	if (m_pClient)
	{
		m_pClient->Destroy();
		m_pClient = nullptr;
	}
}

int ZegoVideoCaptureFactory::StartCapture()
{
	return 0;
}

int ZegoVideoCaptureFactory::StopCapture()
{
	return 0;
}

int ZegoVideoCaptureFactory::SetFrameRate(int framerate)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetResolution(int width, int height)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetFrontCam(int bFront)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetView(void *view)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetViewMode(int nMode)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetViewRotation(int nRotation)
{
	return 0;
}

int ZegoVideoCaptureFactory::SetCaptureRotation(int nRotation)
{
	return 0;
}

int ZegoVideoCaptureFactory::StartPreview()
{
	return 0;
}

int ZegoVideoCaptureFactory::StopPreview()
{
	return 0;
}

int ZegoVideoCaptureFactory::EnableTorch(bool bEnable)
{
	return 0;
}

int ZegoVideoCaptureFactory::TakeSnapshot()
{
	return 0;
}

int ZegoVideoCaptureFactory::SetPowerlineFreq(unsigned int nFreq)
{
	return 0;
}