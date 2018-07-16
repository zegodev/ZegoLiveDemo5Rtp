//
//  ZegoVideoCaptureFromImage.m
//  LiveDemo2
//
//  Created by Randy Qiu on 6/10/16.
//  Copyright © 2016 Zego. All rights reserved.
//

#import "ZegoVideoCaptureFromImage.h"
#import <sys/time.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import "video_capture_encoder.h"
#import "video_capture_encode_callback.h"

// ！！！请注意，采集设备输出类型宏定义，需手动指定当前类型
#define ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_CV_PIXCEL_BUFFER    // pixel buffer 类型
//#define ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID       // gl texture id 类型， WARNING: 1. may cause bad performance! 2. do not support simulator!
//#define ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME       // encoded frame 类型

@implementation ZegoVideoCaptureFromImage {
    struct {
        int fps;
        int width;
        int height;
        bool front;
        int rotation;
        int torch;
    } m_oSettings;
    
    struct RunningState {
        bool preview;
        bool capture;
    } m_oState;
    
    id<ZegoVideoCaptureClientDelegate> client_;
    
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME
    demo::TestCallback* callback_;
    demo::VideoEncoder* encoder_;
#elif defined ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID
    EAGLContext *m_pGLContext;
    CVOpenGLESTextureCacheRef m_pTexCache;
#endif
}

- (void)zego_allocateAndStart:(id<ZegoVideoCaptureClientDelegate>) client {
    client_ = client;
}

- (void)zego_stopAndDeAllocate {
    [client_ destroy];
    client_ = nil;
    
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID
    if (m_pTexCache) {
        CFRelease(m_pTexCache);
        m_pTexCache = 0;
    }
#endif
}

NSTimer *g_fps_timer = nil;
static CVPixelBufferRef pb = NULL;

- (int)zego_startCapture {
    if(m_oState.capture) {
        // * already started
        return 0;
    }
    
    m_oState.capture = true;
    
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME
    callback_ = new demo::TestCallback(client_);
    encoder_ = new demo::VideoEncoder(callback_);
#endif
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [g_fps_timer invalidate];
        int fps = m_oSettings.fps > 0 ?: 15;
        fps = 15;
        NSLog(@"%s, fps: %d", __func__, fps);
        
        g_fps_timer = [NSTimer scheduledTimerWithTimeInterval:1.0/fps target:self selector:@selector(handleTick) userInfo:nil repeats:YES];
        
        if (pb) {
            CVPixelBufferRelease(pb);
            pb = NULL;
        }
    });
    return 0;
}

- (int)zego_stopCapture {
    if(!m_oState.capture) {
        // * capture is not started
        return 0;
    }
    
    m_oState.capture = false;
    
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME
    callback_ = nil;
    encoder_ = nil;
#endif
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [g_fps_timer invalidate];
        g_fps_timer = nil;
    });
    return 0;
}

- (ZegoVideoCaptureDeviceOutputBufferType)zego_supportBufferType {
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_CV_PIXCEL_BUFFER
    return ZegoVideoCaptureDeviceOutputBufferTypeCVPixelBuffer;
#elif defined ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID
    return ZegoVideoCaptureDeviceOutputBufferTypeGlTexture2D;
#elif defined ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME
    return ZegoVideoCaptureDeviceOutputBufferTypeEncodedFrame;
#endif
}

- (int)zego_setFrameRate:(int)framerate {
    // * no change
    if(m_oSettings.fps == framerate) {
        return 0;
    }
    
    m_oSettings.fps = framerate;
    dispatch_async(dispatch_get_main_queue(), ^{
        if (g_fps_timer) {
            [g_fps_timer invalidate];
            int fps = m_oSettings.fps > 0 ?: 15;
            g_fps_timer = [NSTimer scheduledTimerWithTimeInterval:1.0/fps target:self selector:@selector(handleTick) userInfo:nil repeats:YES];
        }
    });
    return 0;
}

- (int)zego_setWidth:(int)width andHeight:(int)height {
    if ((m_oSettings.height == height) && (m_oSettings.width == width)) {
        return 0;
    }
    
    m_oSettings.width = width;
    m_oSettings.height = height;
    return 0;
}

- (int)zego_startPreview {
    if(m_oState.preview) {
        // * preview already started
        return 0;
    }
    
    m_oState.preview = true;
    dispatch_async(dispatch_get_main_queue(), ^{
        [self zego_startCapture];
    });
    
    return 0;
}

- (int)zego_stopPreview {
    if(!m_oState.preview) {
        // * preview not started
        return 0;
    }
    
    m_oState.preview = false;
    
    if(!m_oState.capture) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self zego_stopCapture];
        });
    }
    
    return 0;
}

#pragma mark - Private

- (CGImageRef)CreateBGRAImageFromRGBAImage:(CGImageRef)rgbaImageRef {
    
    if (!rgbaImageRef) {
        return NULL;
    }
    
    const size_t bitsPerPixel = CGImageGetBitsPerPixel(rgbaImageRef);
    const size_t bitsPerComponent = CGImageGetBitsPerComponent(rgbaImageRef);
    
    const size_t channelCount = bitsPerPixel / bitsPerComponent;
    if (bitsPerPixel != 32 || channelCount != 4) {
        assert(false);
        return NULL;
    }
    
    const size_t width = CGImageGetWidth(rgbaImageRef);
    const size_t height = CGImageGetHeight(rgbaImageRef);
    const size_t bytesPerRow = CGImageGetBytesPerRow(rgbaImageRef);
    
    // rgba to bgra: swap blue and red channel
    CFDataRef bgraData = CGDataProviderCopyData(CGImageGetDataProvider(rgbaImageRef));
    UInt8 *pixelData = (UInt8 *)CFDataGetBytePtr(bgraData);
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < bytesPerRow - 4; col += 4) {
            size_t idx = row * bytesPerRow + col;
            UInt8 tmpByte = pixelData[idx]; // red
            pixelData[idx] = pixelData[idx+2];
            pixelData[idx+2] = tmpByte;
        }
    }
    
    CGColorSpaceRef colorspace = CGImageGetColorSpace(rgbaImageRef);
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(rgbaImageRef);
    
    CGDataProviderRef provider = CGDataProviderCreateWithCFData(bgraData);
    CGImageRef bgraImageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow,
                                            colorspace, bitmapInfo, provider,
                                            NULL, true, kCGRenderingIntentDefault);
    
    CFRelease(bgraData);
    CGDataProviderRelease(provider);
    
    return bgraImageRef;
}

- (CVPixelBufferRef)createBGRAPixelBufferFromCGImage:(CGImageRef)image {
    
    int width = m_oSettings.width;
    int height = m_oSettings.height;
    
    CVReturn status;
    CVPixelBufferRef pixelBuffer;
    
    {
        
    // empty value for attr value.
    CFDictionaryRef empty = CFDictionaryCreate(kCFAllocatorDefault,
                                               NULL, NULL, 0,
                                               &kCFTypeDictionaryKeyCallBacks,
                                               &kCFTypeDictionaryValueCallBacks); // our empty IOSurface properties dictionary
    
    CFMutableDictionaryRef attrs = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                                             1,
                                                             &kCFTypeDictionaryKeyCallBacks,
                                                             &kCFTypeDictionaryValueCallBacks);
    
    CFDictionarySetValue(attrs, kCVPixelBufferIOSurfacePropertiesKey, empty);
    CFDictionarySetValue(attrs, kCVPixelBufferIOSurfacePropertiesKey, empty);
    
    
    status = CVPixelBufferCreate(kCFAllocatorDefault,
                                 width,
                                 height,
                                 kCVPixelFormatType_32BGRA, // no support kCVPixelFormatType_32RGBA?
                                 attrs,
                                 &pixelBuffer);
    CFRelease(attrs);
    CFRelease(empty);
        
    }
    
    if (status != kCVReturnSuccess) {
        return NULL;
    }
    
    time_t currentTime = time(0);
    
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    void *data = CVPixelBufferGetBaseAddress(pixelBuffer);
    char color[4] = {0};
    
    color[0] = (currentTime * 1) % 0xFF;
    color[1] = (currentTime * 2) % 0xFF;
    color[2] = (currentTime * 3) % 0xFF;
    color[3] = (currentTime * 4) % 0xFF;
    memset_pattern4(data, color, CVPixelBufferGetDataSize(pixelBuffer));
    
    
    
    CGFloat imageWith = CGImageGetWidth(image);
    CGFloat imageHeight = CGImageGetHeight(image);
    
    static CGPoint origin = {0, 0};
    static time_t lastTime = 0;
    
    if (lastTime != currentTime) {
        origin.x = rand() % (int)(width - imageWith);
        origin.y = rand() % (int)(height - imageHeight);
        
        lastTime = currentTime;
    }

    {
    
    CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
        
    CGContextRef context = CGBitmapContextCreate(data, width, height, 8,
                                                 CVPixelBufferGetBytesPerRow(pixelBuffer),
                                                 rgbColorSpace,
                                                 kCGImageAlphaPremultipliedLast);
        
    CGImageRef bgraImage = [self CreateBGRAImageFromRGBAImage:image];
    
    CGContextDrawImage(context,
                       CGRectMake(origin.x, origin.y, CGImageGetWidth(image), CGImageGetHeight(image)),
                       bgraImage);
    
    CGImageRelease(bgraImage);
    CGContextRelease(context);
    CGColorSpaceRelease(rgbColorSpace);
        
    }
    
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    return pixelBuffer;
}

- (CVReturn)createNV12PixelBuffer:(CVPixelBufferRef *)ppixelBuffer width:(int)width height:(int)height{
    CVReturn err = CVPixelBufferCreate(kCFAllocatorDefault,
                                       width, height,
                                       kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange,
                                       nil, ppixelBuffer);

    err = CVPixelBufferLockBaseAddress(*ppixelBuffer, 0);
    if (err != kCVReturnSuccess) {
        return err;
    }

    size_t plane_count = CVPixelBufferGetPlaneCount(*ppixelBuffer);
    for (int i = 0; i < plane_count; i++) {
        unsigned char* offset_dst = (unsigned char*)CVPixelBufferGetBaseAddressOfPlane(*ppixelBuffer, i);
        int stride = (int)CVPixelBufferGetBytesPerRowOfPlane(*ppixelBuffer, i);
        int height = (int)CVPixelBufferGetHeightOfPlane(*ppixelBuffer, i);

        i = 0;
        memset(offset_dst, ++i % 128, stride * height);
    }

    CVPixelBufferUnlockBaseAddress(*ppixelBuffer, 0);

    return err;
}

- (void)handleTick {
    if (pb) {
        CVPixelBufferRelease(pb);
        pb = NULL;
    }
    
    if (!pb) {
        UIImage *img = [UIImage imageNamed:@"zego.png"];
        pb = [self createBGRAPixelBufferFromCGImage:img.CGImage];
        
        CGImageRef image = [self createCGImageFromCVPixelBuffer:pb];
        self.videoImage = [UIImage imageWithCGImage:image];
        CGImageRelease(image);
    }
    
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    unsigned long long t = (unsigned long long)(tv_now.tv_sec) * 1000 + tv_now.tv_usec / 1000;
    
    CMTime pts = CMTimeMakeWithSeconds(t, 1000);
    
#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_CV_PIXCEL_BUFFER
    [client_ onIncomingCapturedData:pb withPresentationTimeStamp:pts];
#elif defined ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_ENCODED_FRAME
    // 对原始帧进行编码，编码结果由 video_capture_encode_callback 处理
    if (encoder_) {
        encoder_->Encode(pb, (double)pts.value / pts.timescale * 1000.0f);
    }
#elif defined ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID
    if (!m_pGLContext) {
        m_pGLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    }

    EAGLContext *pOldGLContext = nil;
    if([EAGLContext currentContext] != m_pGLContext) {
        pOldGLContext = [EAGLContext currentContext];
        [EAGLContext setCurrentContext:m_pGLContext];
    }

    if (!m_pTexCache) {
        CVOpenGLESTextureCacheCreate(kCFAllocatorDefault, NULL, m_pGLContext, NULL, &m_pTexCache);
    }

    CVOpenGLESTextureRef texture = NULL;
    if ([self createTexture:&texture FromPixelBuffer:pb] == 0) {
        [client_ onIncomingCapturedData:CVOpenGLESTextureGetName(texture)
                                  width:(int)CVPixelBufferGetWidth(pb)
                                 height:(int)CVPixelBufferGetHeight(pb)
              withPresentationTimeStamp:pts];
    }

    if (texture) {
        glBindTexture(CVOpenGLESTextureGetTarget(texture), 0);
        CFRelease(texture);
        texture = nil;
    }

    // * restore context
    if (pOldGLContext != nil) {
        [EAGLContext setCurrentContext:pOldGLContext];
    }
    
#endif
}

- (CGImageRef)createCGImageFromCVPixelBuffer:(CVPixelBufferRef)pixels {
    
    CVPixelBufferLockBaseAddress(pixels, kCVPixelBufferLock_ReadOnly);
    
    CIImage *ciImage = [CIImage imageWithCVPixelBuffer:pixels];
    CIContext *temporaryContext = [CIContext contextWithOptions:nil];
    CGImageRef videoImage = [temporaryContext createCGImage:ciImage fromRect:CGRectMake(0, 0, CVPixelBufferGetWidth(pixels), CVPixelBufferGetHeight(pixels))];
    
    CVPixelBufferUnlockBaseAddress(pixels, kCVPixelBufferLock_ReadOnly);
    
    return videoImage;
}

#ifdef ZEGO_DEMO_EXTERNAL_VIDEO_CAPTURE_DEVICE_OUTPUT_TYPE_GL_TEXTURE_ID
- (int)createTexture:(CVOpenGLESTextureRef*)texture FromPixelBuffer:(CVPixelBufferRef)pixelBuffer {
    int width = (int)CVPixelBufferGetWidth(pixelBuffer);
    int height = (int)CVPixelBufferGetHeight(pixelBuffer);
    
    CVReturn err = CVOpenGLESTextureCacheCreateTextureFromImage(kCFAllocatorDefault,
                                                                m_pTexCache,
                                                                pixelBuffer,
                                                                NULL,
                                                                GL_TEXTURE_2D,
                                                                GL_RGBA,
                                                                (GLsizei)width,
                                                                (GLsizei)height,
                                                                GL_BGRA,
                                                                GL_UNSIGNED_BYTE,
                                                                0,
                                                                texture);
    if (err != kCVReturnSuccess) {
        if (texture) {
            CFRelease(*texture);
        }
        return -1;
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(CVOpenGLESTextureGetTarget(*texture), CVOpenGLESTextureGetName(*texture));
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    return 0;
}
#endif

@end


@implementation ZegoVideoCaptureFactory {
    ZegoVideoCaptureFromImage * g_device_;
}

- (id<ZegoVideoCaptureDevice>)zego_create:(NSString*)deviceId {
    if (g_device_ == nil) {
        g_device_ = [[ZegoVideoCaptureFromImage alloc]init];
    }
    return g_device_;
}

- (void)zego_destroy:(id<ZegoVideoCaptureDevice>)device {
    
}

- (ZegoVideoCaptureFromImage *)getCaptureDevice {
    return g_device_;
}

@end

