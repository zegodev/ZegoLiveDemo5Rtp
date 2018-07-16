//
//  ZegoLiveApi-utils.h
//  zegoavkit
//
//  Created by Randy Qiu on 2016/12/9.
//  Copyright © 2016年 Zego. All rights reserved.
//

#import <ZegoLiveRoom/ZegoLiveRoom.h>
#import <AVFoundation/AVFoundation.h>

@interface ZegoLiveRoomApi (Utils)

+ (bool)createPixelBufferPool:(CVPixelBufferPoolRef*)pool width:(int)width height:(int)height;
+ (void)destroyPixelBufferPool:(CVPixelBufferPoolRef*)pool;
+ (bool)copyPixelBufferFrom:(CVPixelBufferRef)src to:(CVPixelBufferRef)dst;

+ (UIImage *)imageFromString:(NSString *)string attributes:(NSDictionary *)attributes;
+ (CIImage *)overlayImage:(CIImage *)backgroundImage image:(CIImage *)image size:(CGSize)size;
+ (CVPixelBufferRef)pixelBufferFromCGImage:(CGImageRef)image;
+ (CGImageRef)createCGImageFromCVPixelBuffer:(CVPixelBufferRef)pixels;

@end
