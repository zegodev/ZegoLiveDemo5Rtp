#include "ZegoCamera.h"

#include "Base/IncludeZegoLiveRoomApi.h"


class ZegoVideoCapExternalClient : public AVE::VideoCaptureDevice::Client
{
public:
    ZegoVideoCapExternalClient(ZegoVideoCapExternal *pExternal, std::string& deviceId)
        : m_pExternal(pExternal), m_deviceId(deviceId) {}

    ~ZegoVideoCapExternalClient()
    {
        m_pExternal = nullptr;
        m_deviceId.clear();
    }

public:
    void Destroy() override {
        delete this;
    }

    void OnError(const char* reason) override
    {
        if (m_pExternal)
            m_pExternal->OnCaptureDeviceError(m_deviceId, reason);
    }

    void SetFillMode(int mode) override {}

public:
    void OnIncomingCapturedData(
        const char* data,
        int length,
        const AVE::VideoCaptureFormat& frame_format,
        unsigned long long reference_time,
        unsigned int reference_time_scale) override
    {
        if (m_pExternal)
            m_pExternal->OnIncommingCaptureData(m_deviceId, data, length, frame_format, reference_time, reference_time_scale);
    }

    void OnTakeSnapshot(void *image) override 
	{
		if (m_pExternal)
			m_pExternal->OnTakeSnapshot(image);
    }

private:
    ZegoVideoCapExternal *m_pExternal;
    std::string m_deviceId;
};

//
// * ZegoVideoCapExternal
//
std::string ZegoVideoCapExternal::GetDeviceId()
{
	return m_deviceId;
}

int ZegoVideoCapExternal::SetCamera(std::string deviceId)
{
	
	if (deviceId.size() == 0)
	{
		m_deviceId = "";
		return -1;
	}

	if (m_deviceId == deviceId)
	{
		return -1;
	}

#ifdef Q_OS_WIN
	AVE::Camera *pCameraDevice = ZEGO::CAMERA::CreateCamera();
#else
    AVE::Camera *pCameraDevice = nullptr;
#endif

	if (pCameraDevice == nullptr)
	{
		return -2;
	}

	m_deviceId = deviceId;

	AVE::VideoPixelBufferType bufferType = pCameraDevice->SupportBufferType();
	if (bufferType & AVE::PIXEL_BUFFER_TYPE_MEM)
	{
		ZegoVideoCapExternalClient *client = new ZegoVideoCapExternalClient(this, m_deviceId);
		pCameraDevice->AllocateAndStart(client);
		pCameraDevice->SetDeviceId(m_deviceId.c_str());

		m_deviceInfo.cameraDevice = pCameraDevice;
		m_deviceInfo.isCapture = false;
	}
	else
	{
		
#ifdef Q_OS_WIN
		ZEGO::CAMERA::DestroyCamera(pCameraDevice);
#else
        pCameraDevice = nullptr;
#endif
	}

	return 0;
}

int ZegoVideoCapExternal::RemoveCamera()
{
	AVE::Camera *pCameraDevice = m_deviceInfo.cameraDevice;
	if (pCameraDevice)
	{
		pCameraDevice->StopAndDeAllocate();

		
#ifdef Q_OS_WIN
		ZEGO::CAMERA::DestroyCamera(pCameraDevice);
#else
        pCameraDevice = nullptr;
#endif
	}

	m_deviceInfo.Reset();

	return 0;
}


int ZegoVideoCapExternal::StartCapture()
{
	if (m_deviceInfo.isCapture)
		return 0;

	m_deviceInfo.isCapture = true;

	if (m_deviceInfo.cameraDevice)
		m_deviceInfo.cameraDevice->StartCapture();

	return 0;
}

int ZegoVideoCapExternal::StopCapture()
{
	m_deviceInfo.isCapture = false;

	if (m_deviceInfo.cameraDevice)
		m_deviceInfo.cameraDevice->StopCapture();

	return 0;
}

int ZegoVideoCapExternal::SetFrameRate(int framerate)
{
	if (m_deviceInfo.cameraDevice)
		m_deviceInfo.cameraDevice->SetFrameRate(framerate);

	return 0;
}

int ZegoVideoCapExternal::SetCameraResolution(int width, int height)
{
	if (m_deviceInfo.cameraDevice)
		m_deviceInfo.cameraDevice->SetResolution(width, height);

	return 0;
}

void ZegoVideoCapExternal::OnCaptureDeviceError(const std::string& deviceId, const char* reason)
{

	if (m_deviceId != deviceId)
		return;

	//RemoveCamera();

	if (on_device_error_delegate_)
        on_device_error_delegate_(deviceId.c_str(), reason);
}

void ZegoVideoCapExternal::OnIncommingCaptureData(
	const std::string& deviceId,
	const char* data,
	int length,
	const AVE::VideoCaptureFormat& frame_format,
	unsigned long long reference_time,
	unsigned int reference_time_scale)
{
    //auto tmp = VideoFrame::create((const unsigned char*)data, length, frame_format, &pool_);
	auto tmp = std::make_shared< QZegoVideoFrame >((const unsigned char*)data, length, frame_format);

    if (on_video_frame_delegate_) {
        on_video_frame_delegate_(tmp);
    }        
}

void ZegoVideoCapExternal::OnTakeSnapshot(void* image)
{

}



	
