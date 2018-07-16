//
//  ZegoVideoCaptureFromImage.h
//  LiveDemo2
//
//  Copyright © 2016 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ZegoLiveRoom/ZegoVideoCapture.h>

@interface ZegoVideoFilterDemo : NSObject<ZegoVideoFilter, ZegoVideoBufferPool>

@end

@interface ZegoVideoFilterDemo2 : NSObject<ZegoVideoFilter, ZegoVideoFilterDelegate>

@end

@interface ZegoVideoFilterI420Demo : NSObject<ZegoVideoFilter, ZegoVideoBufferPool>

@end

@interface ZegoVideoFilterFactoryDemo : NSObject<ZegoVideoFilterFactory>

@end
