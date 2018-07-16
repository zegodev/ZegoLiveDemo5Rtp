#include "ZegoInputManager.h"
#include "Base/IncludeZegoLiveRoomApi.h"
#include "ZegoLiveDemo.h"
#include <QPainter>
#include <windows.h>

using namespace ZEGO;
using AutoLock = std::lock_guard<std::mutex>;
using std::placeholders::_1;
using std::placeholders::_2;


ZegoInputManager::ZegoInputManager()
{
	m_pCamera = new ZegoVideoCapExternal;

	QImage defaultImg(QSize(640, 360), QImage::Format_ARGB32);
	defaultImg.fill(qRgb(22, 22, 22));
	AVE::VideoCaptureFormat qFormat;
	qFormat.width = 640;
	qFormat.height = 360;
	qFormat.strides[0] = 4 * 640;
	qFormat.pixel_format = AVE::VideoPixelFormat::PIXEL_FORMAT_BGRA32;
	cam_frame_ = std::make_shared< QZegoVideoFrame >(defaultImg, qFormat);

	m_audio_factory = ZEGO::AUDIODEVICE::GetIAudioDataInOutput();
	
	m_audio_capture_thread = new QThread(this);

	LoadPCM();   //测试用pcm

	m_audio_frame.frameType = AVE::FrameType::TYPE_PCM;
	m_audio_frame.channels = 2;
	m_audio_frame.sampleRate = 44100;
	m_audio_frame.bytesPerSample = 2 * 2;
	m_audio_frame.samples = 882;
	// 长度 = 采样率 * 20 / 1000 * 位深字节数 * 通道数 位深字节数固定为2
    //计算公式 length = 44100 * 20 / 1000 * 2 * 2 = 3528
	m_audio_frame.bufLen = 3528;

	m_audio_frame.buffer = new unsigned char[3528];
}

ZegoInputManager::~ZegoInputManager()
{
	//delete m_audio_factory;
	m_audio_factory = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;

	cam_frame_ = nullptr;
}

void ZegoInputManager::Init()
{
    m_pCamera->SetOnVideoFrameDelegate(
        std::bind(&ZegoInputManager::OnCamVideoFrame, this, _1)
    );
    m_pCamera->SetOnCaptureDeviceErrorDelegate(
        std::bind(&ZegoInputManager::OnCamDeviceError, this, _1, _2)
    );
}

void ZegoInputManager::Uninit()
{
    m_pCamera->SetOnVideoFrameDelegate(nullptr);
    m_pCamera->SetOnCaptureDeviceErrorDelegate(nullptr);
}

//
// * Camera Settings
//
int ZegoInputManager::SetCameraDeviceID(std::string device_id)
{
	if(device_id != m_pCamera->GetDeviceId())
	    m_pCamera->RemoveCamera();

    int isSuccess = m_pCamera->SetCamera(device_id);
	if (isSuccess == 0)
	{
		m_pCamera->SetFrameRate(m_fps);
		m_pCamera->SetCameraResolution(m_resolution.width(), m_resolution.height());
		m_pCamera->StartCapture();
	}

	return isSuccess;
}

int ZegoInputManager::SetCameraFPS(int fps)
{
	m_fps = fps;
    return m_pCamera->SetFrameRate(m_fps);
}

void ZegoInputManager::SetCameraResolution(QSize size)
{
	m_resolution = size;
	m_pCamera->SetCameraResolution(m_resolution.width(), m_resolution.height());
}

void ZegoInputManager::StartCameraCapture()
{
	m_pCamera->StartCapture();
}

void ZegoInputManager::StopCameraCapture()
{
	m_pCamera->StopCapture();
}

VideoFrame ZegoInputManager::GetCamFrame()
{
    AutoLock al(cam_frame_lock_);    
    auto tmp = cam_frame_;
    return tmp;
}

void ZegoInputManager::OnCamVideoFrame(VideoFrame f)
{
	theApp.GetBase().GetVideoFactory()->SendCapturedDataToSDK((const char*)f->getData(), f->frameLength(), f->getCurrentFormat(), GetTickCount(), 1000);

    AutoLock al(cam_frame_lock_);
    cam_frame_ = f;


}

void ZegoInputManager::OnCamDeviceError(const char *deviceId, const char *reason)
{

}

void ZegoInputManager::LoadPCM()
{
	QString PcmFilePath = QDir::currentPath() + "/Resources/a.pcm";

	if (!PcmFilePath.isEmpty())
	{
		FILE* fAux;
		fAux = fopen(PcmFilePath.toStdString().c_str(), "rb");

		if (fAux == NULL)
		{
			return;
		}

		fseek(fAux, 0, SEEK_END);
		m_nPcmDataLen = ftell(fAux);

		if (m_nPcmDataLen > 0)
		{
			m_PcmData = new unsigned char[m_nPcmDataLen];
			memset(m_PcmData, 0, m_nPcmDataLen);
		}
		rewind(fAux);

		int nReadDataLen = fread(m_PcmData, sizeof(unsigned char), m_nPcmDataLen, fAux);

		fseek(fAux, 0, 0);

		fclose(fAux);

	}
}

void ZegoInputManager::StartAudioCapture()
{
	if(m_audio_factory)
	    m_audio_factory->startCapture();

	m_audio_capture_timer = new QTimer;
	m_audio_capture_timer->setTimerType(Qt::PreciseTimer);

	m_audio_capture_timer->moveToThread(m_audio_capture_thread);
	//20毫秒采样一次
	m_audio_capture_timer->setInterval(20);
	connect(m_audio_capture_thread, SIGNAL(started()), m_audio_capture_timer, SLOT(start()));
	connect(m_audio_capture_thread, SIGNAL(finished()), m_audio_capture_timer, SLOT(stop()));

	connect(m_audio_capture_timer, &QTimer::timeout, this, &ZegoInputManager::OnAudioDataCaptured, Qt::DirectConnection);

	m_audio_capture_thread->start();
}

void ZegoInputManager::StopAudioCapture()
{
	m_audio_capture_thread->quit();
	m_audio_capture_thread->wait();

	disconnect(m_audio_capture_timer, &QTimer::timeout, this, &ZegoInputManager::OnAudioDataCaptured);

	if (m_audio_factory)
	    m_audio_factory->stopCapture();

	delete m_audio_capture_timer;
	m_audio_capture_timer = nullptr;
}

void ZegoInputManager::OnAudioDataCaptured()
{
	
	if (m_pcmDataPos + m_audio_frame.bufLen > m_nPcmDataLen)
	{
		m_pcmDataPos = 0;
	}
	int nCopyLen = m_audio_frame.bufLen;
	memcpy(m_audio_frame.buffer, m_PcmData + m_pcmDataPos, nCopyLen);

	m_pcmDataPos += nCopyLen;

	if (m_audio_factory)
	    m_audio_factory->onRecordAudioFrame(m_audio_frame);
}
