//
//  video_capture_encode_callback.m
//  LiveDemo5
//
//  Created by summery on 24/09/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

#import "video_capture_encode_callback.h"
#import <AVFoundation/AVFoundation.h>
#include "video_capture_encoder.h"

namespace demo {
    
    TestCallback::TestCallback(id<ZegoVideoCaptureClientDelegate> client) {
        m_client = client;
    }

    TestCallback::~TestCallback() {
        m_client = nullptr;
    }   

    // 接受编码后数据
    void TestCallback::OnEncodedFrame(const char* data,
                                      int length,
                                      const AVE::VideoCodecConfig& codec_config,
                                      bool b_keyframe, double reference_time_ms) {
        NSData *encodedData = [NSData dataWithBytes:data length:length];
        
        ZegoVideoCodecConfig config;
        config.width = codec_config.width;
        config.height = codec_config.height;
        config.codecType = (ZegoVideoCodecType)codec_config.codec_type;
        
        CMTime time = CMTimeMake(reference_time_ms, 1);
        
        [m_client onEncodedFrame:encodedData config:config bKeyframe:b_keyframe withPresentationTimeStamp:time];
    }


}
