//
//  video_capture_external_demo.h
//  ve_demo
//
//  Created by robotding on 16/5/30.
//  Copyright © 2016年 jjams. All rights reserved.
//

#ifndef video_capture_external_demo_h
#define video_capture_external_demo_h

#include <ZegoLiveRoom/ZegoVideoCapture.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface VideoCaptureDeviceDemo : NSObject<ZegoVideoCaptureDevice, AVCaptureVideoDataOutputSampleBufferDelegate>

@property (atomic, strong) UIImage *videoImage;

@end

@interface VideoCaptureFactoryDemo : NSObject<ZegoVideoCaptureFactory>

- (VideoCaptureDeviceDemo *)getCaptureDevice;

@end

#endif /* video_capture_external_demo_h */
