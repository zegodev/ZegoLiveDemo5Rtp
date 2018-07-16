//
//  ZegoVideoFilterDemo.m
//  LiveDemo2
//
//  Copyright © 2016 Zego. All rights reserved.
//

#import "ZegoVideoFilterDemo.h"
#import <ZegoImageFilter/ZegoImageFilter.h>
#import "ZegoLiveApi-utils.h"
#import "ZegoAVKitManager.h"


#pragma mark - ZegoVideoFilterDemo

@interface ZegoVideoFilterDemo()
@property (atomic) int pendingCount;

//视频显示时间相关信息
@property (nonatomic, strong) NSDictionary *attributes;
@property (nonatomic, strong) NSDateFormatter *formatter;

@end

@implementation ZegoVideoFilterDemo {
    id<ZegoVideoFilterClient> client_;      // SDK 创建的外部滤镜客户端，用于传递数据
    id<ZegoVideoBufferPool> buffer_pool_;
    
    dispatch_queue_t queue_;
    int width_;
    int height_;
    int stride_;
    
    CVPixelBufferPoolRef pool_;
    int buffer_count_;
    
    ZegoImageFilter* filter_;
}

#pragma mark -- ZegoVideoFilter Delgate

// 初始化外部滤镜使用的资源
- (void)zego_allocateAndStart:(id<ZegoVideoFilterClient>) client {
    client_ = client;
    if ([client_ conformsToProtocol:@protocol(ZegoVideoBufferPool)]) {
        buffer_pool_ = (id<ZegoVideoBufferPool>)client;
    }
    
    width_ = 0;
    height_ = 0;
    stride_ = 0;
    pool_ = nil;
    buffer_count_ = 4;
    self.pendingCount = 0;
    
    if ([ZegoDemoHelper recordTime])
    {
        self.attributes = @{NSFontAttributeName: [UIFont systemFontOfSize:14], NSForegroundColorAttributeName: [UIColor redColor], NSBackgroundColorAttributeName: [UIColor lightGrayColor]};
        
        self.formatter = [[NSDateFormatter alloc] init];
        self.formatter.dateFormat = @"HH:mm:ss:SSS";
        self.formatter.timeZone = [NSTimeZone timeZoneWithAbbreviation:@"GMT+0800"];
    }
    
    queue_ = dispatch_queue_create("video.filter", nil);
    dispatch_async(queue_, ^ {
        filter_ = [[ZegoImageFilter alloc] init];
        [filter_ create];
        if ([ZegoDemoHelper recordTime])
        {
            [filter_ setCustomizedFilter:ZEGO_FILTER_CUSTOM_NONE];
            [filter_ enableBeautifying:ZEGO_FILTER_BEAUTIFY_POLISH | ZEGO_FILTER_BEAUTIFY_WHITEN];
            
            // 展示计时器时，使用美颜
            [filter_ setPolishFactor:4.0];
            [filter_ setPolishStep:4.0];
            [filter_ setWhitenFactor:0.6];
        }
        else
            [filter_ setCustomizedFilter:ZEGO_FILTER_CUSTOM_LOMO];
    });

}

// 停止并释放外部滤镜占用的资源
- (void)zego_stopAndDeAllocate {
    dispatch_sync(queue_, ^ {
        [filter_ destroy];
        filter_ = nil;
    });
    
    if (pool_) {
        [ZegoLiveRoomApi destroyPixelBufferPool:&pool_];
    }
    queue_ = nil;
    
    [client_ destroy];
    client_ = nil;
    buffer_pool_ = nil;
}

- (ZegoVideoBufferType)supportBufferType {
    // * 返回滤镜的类型：此滤镜为异步滤镜
    return ZegoVideoBufferTypeAsyncPixelBuffer;
}

#pragma mark -- ZegoVideoBufferPool Delegate

// SDK 回调。从 App 获取 CVPixelBufferRef 对象，用于保存视频帧数据
- (CVPixelBufferRef)dequeueInputBuffer:(int)width height:(int)height stride:(int)stride {
    // * 按需创建 CVPixelBufferPool
    if (width_ != width || height_ != height || stride_ != stride) {
        if (pool_) {
            [ZegoLiveRoomApi destroyPixelBufferPool:&pool_];
        }
        
        if ([ZegoLiveRoomApi createPixelBufferPool:&pool_ width:width height:height]) {
            width_ = width;
            height_ = height;
            stride_ = stride;
        } else {
            return nil;
        }
    }
    
    // * 如果处理不及时，未处理帧超过了 pool 的大小，则丢弃该帧
    if (self.pendingCount >= buffer_count_) {
        return nil;
    }
    
    CVPixelBufferRef pixel_buffer = nil;
    CVReturn ret = CVPixelBufferPoolCreatePixelBuffer(kCFAllocatorDefault, pool_, &pixel_buffer);
    
    if (ret != kCVReturnSuccess) {
        return nil;
    } else {
        self.pendingCount = self.pendingCount + 1;
        // * 返回一个可以用于存储采集到的图像的 CVPixelBuffer 实例
        return pixel_buffer;
    }
}

// SDK 回调。App 在此接口中获取 SDK 采集到的视频帧数据，并进行处理
- (void)queueInputBuffer:(CVPixelBufferRef)pixel_buffer timestamp:(unsigned long long)timestamp_100n {
    // * 采集到的图像数据通过这个传进来，这个点需要异步处理
    dispatch_async(queue_, ^ {
        // * 图像滤镜处理
        if ([ZegoDemoHelper recordTime])
        {
            CVPixelBufferRef output = [filter_ render:pixel_buffer];
            [self processRecordTime:output timestamp:timestamp_100n];
        }
        else
        {
            CVPixelBufferRef output = [filter_ render:pixel_buffer];
            [self copyPixelBufferToPool:output timestamp:timestamp_100n];
        }
        
        CVPixelBufferRelease(pixel_buffer);
    });
}

#pragma mark -- Private method

// App 处理采集到的视频帧数据。此处处理为：在原视频帧上添加倒计时水印
- (void)processRecordTime:(CVPixelBufferRef)inputPixelBuffer timestamp:(unsigned long long)timestamp_100n
{
    NSString *currentTime = [self.formatter stringFromDate:[NSDate date]];
    UIImage *textImage = [ZegoLiveRoomApi imageFromString:currentTime attributes:self.attributes];
    
    CGImageRef videoImage = [ZegoLiveRoomApi createCGImageFromCVPixelBuffer:inputPixelBuffer];
    
    int imageWidth = (int)CVPixelBufferGetWidth(inputPixelBuffer);
    int imageHeight = (int)CVPixelBufferGetHeight(inputPixelBuffer);
    int imageStride = (int)CVPixelBufferGetBytesPerRowOfPlane(inputPixelBuffer, 0);
    
    CIImage *blendImage = [ZegoLiveRoomApi overlayImage:[CIImage imageWithCGImage:videoImage] image:[CIImage imageWithCGImage:textImage.CGImage] size:CGSizeMake(ceilf(imageWidth * 0.1), ceilf(imageHeight * 0.7))];
    
//    CIContext *context = [CIContext contextWithCGContext:UIGraphicsGetCurrentContext() options:nil];
    CIContext *context = [CIContext contextWithOptions:nil];

    // 从 SDK 获取 CVPixelBufferRef 对象，用于存储 App 处理后的数据
    CVPixelBufferRef dst = [buffer_pool_ dequeueInputBuffer:imageWidth height:imageHeight stride:imageStride];
    if (dst)
    {
        [context render:blendImage toCVPixelBuffer:dst];
        
        [buffer_pool_ queueInputBuffer:dst timestamp:timestamp_100n];
        
        self.pendingCount = self.pendingCount - 1;
    }
    
    CGImageRelease(videoImage);
    
}

// App 将处理好的数据，传递回 SDK
- (void)copyPixelBufferToPool:(CVPixelBufferRef)output timestamp:(unsigned long long)timestamp_100n
{
    int imageWidth = 0;
    int imageHeight = 0;
    int imageStride = 0;
    
    if (output) {
        imageWidth = (int)CVPixelBufferGetWidth(output);
        imageHeight = (int)CVPixelBufferGetHeight(output);
        imageStride = (int)CVPixelBufferGetBytesPerRowOfPlane(output, 0);
    }
    
    // * 处理完图像，需要从 buffer pool 中取出一个 CVPixelBuffer 实例，把处理过的图像数据拷贝到该实例中
    CVPixelBufferRef dst = [buffer_pool_ dequeueInputBuffer:imageWidth height:imageHeight stride:imageStride];
    if (!dst) {
        return ;
    }
    
    if ([ZegoLiveRoomApi copyPixelBufferFrom:output to:dst]) {
        // * 把从 buffer pool 中得到的 CVPixelBuffer 实例传进来
        [buffer_pool_ queueInputBuffer:dst timestamp:timestamp_100n];
    }
    
    self.pendingCount = self.pendingCount - 1;
}
             
@end


#pragma mark - ZegoVideoFilterDemo2

@implementation ZegoVideoFilterDemo2 {
    id<ZegoVideoFilterClient> client_;
    id<ZegoVideoFilterDelegate> delegate_;
    ZegoImageFilter* filter_;
}

- (void)zego_allocateAndStart:(id<ZegoVideoFilterClient>) client {
    client_ = client;
    if ([client_ conformsToProtocol:@protocol(ZegoVideoFilterDelegate)]) {
        delegate_ = (id<ZegoVideoFilterDelegate>)client;
    }
    
    filter_ = [[ZegoImageFilter alloc] init];
    [filter_ create];
    [filter_ setCustomizedFilter:ZEGO_FILTER_CUSTOM_LOMO];
}

- (void)zego_stopAndDeAllocate {
    [filter_ destroy];
    filter_ = nil;

    [client_ destroy];
    client_ = nil;
    delegate_ = nil;
}

- (ZegoVideoBufferType)supportBufferType {
    // * 返回滤镜的类型：此滤镜为同步滤镜
    return ZegoVideoBufferTypeSyncPixelBuffer;
}

- (void)onProcess:(CVPixelBufferRef)pixel_buffer withTimeStatmp:(unsigned long long)timestamp_100 {
    // * 采集到的图像数据通过这个传进来，同步处理完返回处理结果
    CVPixelBufferRef output = [filter_ render:pixel_buffer];
    [delegate_ onProcess:output withTimeStatmp:timestamp_100];
}

@end


#pragma mark - ZegoVideoFilterI420Demo

@interface ZegoVideoFilterI420Demo()
@property (atomic) int pendingCount;
@end

@implementation ZegoVideoFilterI420Demo {
    id<ZegoVideoFilterClient> client_;
    id<ZegoVideoBufferPool> buffer_pool_;
    
    dispatch_queue_t queue_;
    int width_;
    int height_;
    int stride_;
    
    CVPixelBufferPoolRef pool_;
    int buffer_count_;
}

- (void)zego_allocateAndStart:(id<ZegoVideoFilterClient>) client {
    client_ = client;
    if ([client_ conformsToProtocol:@protocol(ZegoVideoBufferPool)]) {
        buffer_pool_ = (id<ZegoVideoBufferPool>)client;
    }
    
    width_ = 0;
    height_ = 0;
    stride_ = 0;
    pool_ = nil;
    buffer_count_ = 4;
    self.pendingCount = 0;
    
    queue_ = dispatch_queue_create("video.filter", nil);
}

- (void)zego_stopAndDeAllocate {
    if (queue_) {
        dispatch_sync(queue_, ^ {
        });
        queue_ = nil;
    }
    
    if (pool_) {
        [self destroyPool:&pool_];
        pool_ = nil;
    }
    
    if (client_) {
        [client_ destroy];
        client_ = nil;
        buffer_pool_ = nil;
    }
}

- (ZegoVideoBufferType)supportBufferType {
    return ZegoVideoBufferTypeAsyncI420PixelBuffer;
}

- (CVPixelBufferRef)dequeueInputBuffer:(int)width height:(int)height stride:(int)stride {
    if (width_ != width || height_ != height || stride_ != stride) {
        if (pool_) {
            [self destroyPool:&pool_];
        }
        
        if ([self createPool:width height:height pool:&pool_]) {
            width_ = width;
            height_ = height;
            stride_ = stride;
        } else {
            return nil;
        }
    }
    
    if (self.pendingCount >= buffer_count_) {
        return nil;
    }
    
    CVPixelBufferRef pixel_buffer = nil;
    CVReturn ret = CVPixelBufferPoolCreatePixelBuffer(kCFAllocatorDefault, pool_, &pixel_buffer);
    
    if (ret != kCVReturnSuccess) {
        return nil;
    } else {
        self.pendingCount = self.pendingCount + 1;
        return pixel_buffer;
    }
}

- (void)queueInputBuffer:(CVPixelBufferRef)pixel_buffer timestamp:(unsigned long long)timestamp_100n {
    dispatch_async(queue_, ^ {
        int imageWidth = (int)CVPixelBufferGetWidth(pixel_buffer);
        int imageHeight = (int)CVPixelBufferGetHeight(pixel_buffer);
        int imageStride = (int)CVPixelBufferGetBytesPerRowOfPlane(pixel_buffer, 0);
        
        CVPixelBufferRef dst = [buffer_pool_ dequeueInputBuffer:imageWidth height:imageHeight stride:imageStride];
        if (!dst) {
            return ;
        }
        
        // add your own code here
        if ([self copyVideoFrame:pixel_buffer toPixelBuffer:dst]) {
            [buffer_pool_ queueInputBuffer:dst timestamp:timestamp_100n];
        }
        
        self.pendingCount = self.pendingCount - 1;
        
        CVPixelBufferRelease(pixel_buffer);
    });
}

- (bool) createPool:(int)width height:(int)height pool:(CVPixelBufferPoolRef*)pool {
    CFMutableDictionaryRef attrs;
    
    SInt32 cvPixelFormatTypeValue = kCVPixelFormatType_420YpCbCr8Planar;
    CFNumberRef cfPixelFormat = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvPixelFormatTypeValue)));
    SInt32 cvWidthValue = width;
    CFNumberRef cfWidth = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvWidthValue)));
    SInt32 cvHeightValue = height;
    CFNumberRef cfHeight = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvHeightValue)));
    
    attrs = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                      3,
                                      &kCFTypeDictionaryKeyCallBacks,
                                      &kCFTypeDictionaryValueCallBacks);
    
    CFDictionarySetValue(attrs, kCVPixelBufferPixelFormatTypeKey, cfPixelFormat);
    CFDictionarySetValue(attrs, kCVPixelBufferWidthKey, cfWidth);
    CFDictionarySetValue(attrs, kCVPixelBufferHeightKey, cfHeight);
    
    CVReturn ret = CVPixelBufferPoolCreate(kCFAllocatorDefault, nil, attrs, pool);
    
    CFRelease(attrs);
    CFRelease(cfPixelFormat);
    CFRelease(cfWidth);
    CFRelease(cfHeight);
    
    if (ret != kCVReturnSuccess) {
        return false;
    }
    
    return true;
}

- (void) destroyPool:(CVPixelBufferPoolRef*) pool {
    CVPixelBufferPoolRelease(*pool);
    *pool = nil;
}

- (bool) copyVideoFrame:(CVPixelBufferRef)src toPixelBuffer:(CVPixelBufferRef)dst {
    bool ret = true;
    
    CVPixelBufferLockBaseAddress(src, kCVPixelBufferLock_ReadOnly);
    
    unsigned char* pb = (unsigned char*)CVPixelBufferGetBaseAddressOfPlane(src, 0);
    int height = (int)CVPixelBufferGetHeight(src);
    int stride = (int)CVPixelBufferGetBytesPerRow(src);
    int size = (int)CVPixelBufferGetDataSize(src);
    
    while (1) {
        CVReturn cvRet = CVPixelBufferLockBaseAddress(dst, 0);
        if (cvRet != kCVReturnSuccess) {
            ret = false;
            break;
        }
        
        int dst_height = (int)CVPixelBufferGetHeight(dst);
        int dst_stride = (int)CVPixelBufferGetBytesPerRow(dst);
        int dst_size = (int)CVPixelBufferGetDataSize(dst);
        
        if (stride == dst_stride && dst_size == size) {
            unsigned char* temp = (unsigned char*)CVPixelBufferGetBaseAddressOfPlane(dst, 0);
            memcpy(temp, pb, size);
        } else {
            int copy_height = height > dst_height ? dst_height : height;
            int copy_stride = stride > dst_stride ? dst_stride : stride;
            
            unsigned char* offset_dst = (unsigned char*)CVPixelBufferGetBaseAddressOfPlane(dst, 0);
            unsigned char* offset_src = pb;
            for (int i = 0; i < copy_height; i++) {
                memcpy(offset_dst, offset_src, copy_stride);
                offset_src += stride;
                offset_dst += dst_stride;
            }
        }
        
        CVPixelBufferUnlockBaseAddress(dst, 0);
        break;
    }
    
    CVPixelBufferUnlockBaseAddress(src, kCVPixelBufferLock_ReadOnly);
    return ret;
}

@end

#pragma mark - ZegoVideoFilterFactoryDemo

@implementation ZegoVideoFilterFactoryDemo {
    id<ZegoVideoFilter> g_filter_;
}

- (id<ZegoVideoFilter>)zego_create {
    if (g_filter_ == nil) {
        bool async = true;
        bool useI420 = false;
        if (useI420)
        {
            g_filter_ = [[ZegoVideoFilterI420Demo alloc] init];
        }
        else if (async) {
            g_filter_ = [[ZegoVideoFilterDemo alloc]init];
        } else {
            g_filter_ = [[ZegoVideoFilterDemo2 alloc]init];
        }
    }
    return g_filter_;
}

- (void)zego_destroy:(id<ZegoVideoFilter>)filter {
    if (g_filter_ == filter) {
        g_filter_ = nil;
    }
}

@end
