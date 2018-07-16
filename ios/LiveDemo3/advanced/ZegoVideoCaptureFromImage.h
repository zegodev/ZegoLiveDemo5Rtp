//
//  ZegoVideoCaptureFromImage.h
//  LiveDemo2
//
//  Created by Randy Qiu on 6/10/16.
//  Copyright © 2016 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ZegoLiveRoom/ZegoVideoCapture.h>

@interface ZegoVideoCaptureFromImage : NSObject<ZegoVideoCaptureDevice>

@property (atomic, strong) UIImage *videoImage;

@end

@interface ZegoVideoCaptureFactory : NSObject<ZegoVideoCaptureFactory>

- (ZegoVideoCaptureFromImage *)getCaptureDevice;

@end
