//
//  IncludeZegoLiveRoomApi.h
//  ZegoLiveDemo
//
//  Created by Randy Qiu on 2017/11/22.
//

#ifndef IncludeZegoLiveRoomApi_h
#define IncludeZegoLiveRoomApi_h


#include <QDebug>

#if defined(Q_OS_WIN)

#include "LiveRoom.h"
#include "LiveRoom-IM.h"
#include "LiveRoom-Player.h"
#include "LiveRoom-Publisher.h"

extern ZEGOAVKIT_API void ZegoExternalLogWithNotice(const char* content);
inline void log_string_notice(const char* content) { ZegoExternalLogWithNotice(content); qDebug() << content; }

namespace ZEGO
{
	namespace CAMERA
	{
		ZEGO_API AVE::Camera* CreateCamera();

		ZEGO_API void DestroyCamera(AVE::Camera *pCamera);
	}
}

#define qtoc(content) content.toStdString().c_str()

#define USE_SURFACE_MERGE
#if defined(USE_SURFACE_MERGE) && defined(Q_PROCESSOR_X86_32)
#include "Module/ZegoSurfaceMergeApi.h"
#endif

#elif defined(Q_OS_MAC)

#include "LiveRoom.h"
#include "LiveRoom-IM.h"
#include "LiveRoom-Player.h"
#include "LiveRoom-Publisher.h"

#else
static_assert(false, "Unkown Platform");
#endif


#endif /* IncludeZegoLiveRoomApi_h */
