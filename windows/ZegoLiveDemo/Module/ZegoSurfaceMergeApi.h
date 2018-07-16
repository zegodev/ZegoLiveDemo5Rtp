
#ifndef ZegoSurfaceMergeApi_H
#define ZegoSurfaceMergeApi_H

#include "ZegoSurfaceMerge.h"
#include "ZegoSurfaceMergeCallback.h"
#include "ZegoSurfaceMergeDefine.h"
#include "ZegoAVView.h"

using namespace ZEGO;

class SurfaceMergeController
{
public:
	static SurfaceMergeController& getInstance()
	{
		static SurfaceMergeController instance;
		return instance;
	}

	//传入分辨率、帧率和摄像头ID
	void setSurfaceSize(int surfaceWidth, int surfaceHeight);
	void setSurfaceFps(int nFps);
	void setSurfaceCameraId(QString cameraID);

	//设置需要渲染的view
	void setRenderView(void *pView);
	//设置回调
	void setMergeCallback(SurfaceMerge::IZegoSurfaceMergeCallback *pCallback);
	//初始化
	void init();
	//反初始化
	void uninit();
	//开始使用SurfaceMerge
	void startSurfaceMerge();

private:
	SurfaceMergeController();
	SurfaceMergeController(const SurfaceMergeController&){}
	SurfaceMergeController& operator=(const SurfaceMergeController&){}
	~SurfaceMergeController(){}

	//static SurfaceMergeController* instance;

	bool m_isRunningSurfaceMerge;
	int m_surfaceWidth;
	int m_surfaceHeight;
	int m_surfaceFps;
	QString m_surfaceCameraID;
	QZegoAVView *m_surfaceView;
};

#endif