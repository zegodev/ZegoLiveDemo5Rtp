#include "ZegoLiveDemo.h"

QZegoLiveDemoApp::QZegoLiveDemoApp()
{
	
}

//全局唯一的base对象
QZegoLiveDemoApp theApp;

QZegoBase& QZegoLiveDemoApp::GetBase()
{
	return m_base;
}

QZegoUserConfig &QZegoLiveDemoApp::GetConfig()
{
	return m_config;
}

QZegoAVSignal * GetAVSignal()
{
	return theApp.GetBase().GetAVSignal();
}
