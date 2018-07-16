//
//  LiveRoomDefines-Publisher.h
//  zegoliveroom
//
//  Created by Randy Qiu on 2017/1/23.
//
//

#ifndef LiveRoomDefines_Publisher_h
#define LiveRoomDefines_Publisher_h

#include "./LiveRoomDefines.h"
#include "./AVDefines.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        using namespace COMMON;
        
        using COMMON::ZegoPublishFlag;
        
        using COMMON::ZegoPublishingStreamInfo;
        
		extern ZEGO_API const char* kZegoVideoDataMainPublishingStream;
		extern ZEGO_API const char* kZegoVideoDataAuxPublishingStream;
    }
}
#endif /* LiveRoomDefines_Publisher_h */
