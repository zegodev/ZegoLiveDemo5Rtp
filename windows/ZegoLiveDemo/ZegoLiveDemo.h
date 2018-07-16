#pragma once

#include "Base/ZegoBase.h"
#include "Config/ZegoUserConfig.h"

class QZegoLiveDemoApp
{
public:
	QZegoLiveDemoApp();

public:
	QZegoBase &GetBase();
	QZegoUserConfig &GetConfig();

private:
	QZegoBase m_base;
	QZegoUserConfig m_config;
};

extern QZegoLiveDemoApp theApp;

QZegoAVSignal * GetAVSignal(void);
