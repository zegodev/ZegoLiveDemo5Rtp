#include "ZegoSurfaceMergeApi.h"

SurfaceMergeController::SurfaceMergeController()
{
	m_surfaceWidth = 0;
	m_surfaceHeight = 0;
	m_surfaceFps = 0;
}

//传入分辨率
void SurfaceMergeController::setSurfaceSize(int surfaceWidth, int surfaceHeight)
{
	m_surfaceWidth = surfaceWidth;
	m_surfaceHeight = surfaceHeight;
}
//传入帧率
void SurfaceMergeController::setSurfaceFps(int nFps)
{
	m_surfaceFps = nFps;
}
//传入摄像头ID
void SurfaceMergeController::setSurfaceCameraId(QString cameraID)
{
	m_surfaceCameraID = cameraID;
}
//传入需要渲染的View
void SurfaceMergeController::setRenderView(void *pView)
{
	m_surfaceView = (QZegoAVView *)pView;
}

//设置回调
void SurfaceMergeController::setMergeCallback(SurfaceMerge::IZegoSurfaceMergeCallback *pCallback)
{
	SurfaceMerge::SetMergeCallback(pCallback);
}

//初始化
void SurfaceMergeController::init()
{
	SurfaceMerge::Init();
}

//反初始化
void SurfaceMergeController::uninit()
{
	SurfaceMerge::UnInit();
}

//开始使用SurfaceMerge
void SurfaceMergeController::startSurfaceMerge()
{
	if (m_surfaceWidth == 0 || m_surfaceHeight == 0 || m_surfaceFps == 0)
		return;
	
	SurfaceMerge::SetFPS(m_surfaceFps);
	SurfaceMerge::SetCursorVisible(true);
	SurfaceMerge::SetSurfaceSize(m_surfaceWidth, m_surfaceHeight);

	SurfaceMerge::ZegoCaptureItem *itemList = new SurfaceMerge::ZegoCaptureItem[2];

	SurfaceMerge::ZegoCaptureItem itemCam;
	strcpy(itemCam.captureSource.deviceId, m_surfaceCameraID.toStdString().c_str());
	itemCam.captureType = SurfaceMerge::CaptureType::Camera;
	itemCam.position = { m_surfaceWidth - m_surfaceWidth / 4, m_surfaceHeight - m_surfaceHeight / 4, m_surfaceWidth / 4, m_surfaceHeight / 4 };  //摄像头默认置于右下角

	unsigned int count = 0;
	SurfaceMerge::ScreenItem *screenList = SurfaceMerge::EnumScreenList(count);
	SurfaceMerge::ZegoCaptureItem itemWin;
	for (int i = 0; i < count; i++)
	{
		if (screenList[i].bPrimary)
		{
			strcpy(itemWin.captureSource.screenName, screenList[i].szName);
			break;
		}
	}

	itemWin.captureType = SurfaceMerge::CaptureType::Screen;
	itemWin.position = { 0, 0, m_surfaceWidth, m_surfaceHeight };
	itemList[0] = itemCam;
	itemList[1] = itemWin;

	SurfaceMerge::UpdateSurface(itemList, 2);
	m_surfaceView->setSurfaceMergeView(true);
	m_surfaceView->setSurfaceMergeItemRect(itemWin, itemCam);
	SurfaceMerge::SetRenderView((void *)m_surfaceView->winId());

	delete[]itemList;
	SurfaceMerge::FreeScreenList(screenList);
}

