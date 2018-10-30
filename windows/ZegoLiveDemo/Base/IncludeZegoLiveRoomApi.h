//
//  IncludeZegoLiveRoomApi.h
//  ZegoLiveDemo
//
//  Created by Randy Qiu on 2017/11/22.
//

#ifndef IncludeZegoLiveRoomApi_h
#define IncludeZegoLiveRoomApi_h


#include <QDebug>
#include "LiveRoom.h"
#include "LiveRoom-IM.h"
#include "LiveRoom-Player.h"
#include "LiveRoom-Publisher.h"
#include "ZegoLiveDemoDefines.h"

extern ZEGOAVKIT_API void ZegoExternalLogWithNotice(const char* content);
inline void log_string_notice(const char* content) { ZegoExternalLogWithNotice(content); qDebug() << content; }

#define qtoc(content) content.toStdString().c_str()

#if defined(Q_OS_WIN)

namespace ZEGO
{
    namespace CAMERA
    {
        ZEGO_API AVE::Camera* CreateCamera();
        
        ZEGO_API void DestroyCamera(AVE::Camera *pCamera);
    }
}


/*#if defined(USE_SURFACE_MERGE) && defined(Q_PROCESSOR_X86_32)
#include "Module/ZegoSurfaceMergeApi.h"
#endif
*/

#if defined(Q_PROCESSOR_X86_32) && !defined(BUILD_FOR_XP)
#define USE_EXTERNAL_SDK
#endif

#elif defined(Q_OS_MAC)


#else
static_assert(false, "Unkown Platform");
#endif


#endif /* IncludeZegoLiveRoomApi_h */
