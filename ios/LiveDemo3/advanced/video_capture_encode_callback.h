//
//  video_capture_encode_callback_h
//  LiveDemo5
//
//  Created by summery on 24/09/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

//#ifndef video_capture_encode_callback_h
//#define video_capture_encode_callback_h

#include "video_capture.h"
#import <ZegoLiveRoom/ZegoVideoCapture.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

// onEncodedFrame 测试类
namespace demo {
    
    class TestCallback : public AVE::VideoCaptureEncodedFrameCallback
    {
    public:
        TestCallback(id<ZegoVideoCaptureClientDelegate> client);
        ~TestCallback();

    public:
        void OnEncodedFrame(const char* data, int length,
                            const AVE::VideoCodecConfig& codec_config,
                            bool b_keyframe, double reference_time_ms);
    
    private:
        id<ZegoVideoCaptureClientDelegate> m_client;
    };
    
}
