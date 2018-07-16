//
//  ZegoLiveApi-utils.m
//  zegoavkit
//
//  Created by Randy Qiu on 2016/12/9.
//  Copyright © 2016年 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZegoLiveApi-utils.h"

@implementation ZegoLiveRoomApi (Utils)

+ (bool)createPixelBufferPool:(CVPixelBufferPoolRef*)pool width:(int)width height:(int)height
{
    CFDictionaryRef empty; // empty value for attr value.
    CFMutableDictionaryRef attrs;
    
    empty = CFDictionaryCreate(kCFAllocatorDefault,
                               NULL, NULL, 0,
                               &kCFTypeDictionaryKeyCallBacks,
                               &kCFTypeDictionaryValueCallBacks); // our empty IOSurface properties dictionary
    
    SInt32 cvPixelFormatTypeValue = kCVPixelFormatType_32BGRA;
    CFNumberRef cfPixelFormat = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvPixelFormatTypeValue)));
    
    SInt32 cvWidthValue = width;
    CFNumberRef cfWidth = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvWidthValue)));
    SInt32 cvHeightValue = height;
    CFNumberRef cfHeight = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, (const void*)(&(cvHeightValue)));
    
    attrs = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                      4,
                                      &kCFTypeDictionaryKeyCallBacks,
                                      &kCFTypeDictionaryValueCallBacks);
    
    CFDictionarySetValue(attrs, kCVPixelBufferIOSurfacePropertiesKey, empty);
    CFDictionarySetValue(attrs, kCVPixelBufferPixelFormatTypeKey, cfPixelFormat);
    CFDictionarySetValue(attrs, kCVPixelBufferWidthKey, cfWidth);
    CFDictionarySetValue(attrs, kCVPixelBufferHeightKey, cfHeight);
    
    CVReturn ret = CVPixelBufferPoolCreate(kCFAllocatorDefault, nil, attrs, pool);
    
    CFRelease(attrs);
    CFRelease(empty);
    CFRelease(cfPixelFormat);
    CFRelease(cfWidth);
    CFRelease(cfHeight);
    
    if (ret != kCVReturnSuccess) {
        return false;
    }
    
    return true;
}

+ (void)destroyPixelBufferPool:(CVPixelBufferPoolRef*)pool {
    CVPixelBufferPoolRelease(*pool);
    *pool = nil;
}

+ (bool)copyPixelBufferFrom:(CVPixelBufferRef)src to:(CVPixelBufferRef)dst {
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

+ (UIImage *)imageFromString:(NSString *)string attributes:(NSDictionary *)attributes
{
    NSAttributedString *attributeString = [[NSAttributedString alloc] initWithString:string attributes:attributes];
    CGRect rect = [attributeString boundingRectWithSize:CGSizeMake(100, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesFontLeading context:nil];
    
    UIGraphicsBeginImageContextWithOptions(CGSizeMake(rect.size.width, rect.size.height), YES, 0);
    
    [string drawInRect:CGRectMake(0, 0, rect.size.width, rect.size.height) withAttributes:attributes];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return image;
}

+ (CIImage *)overlayImage:(CIImage *)backgroundImage image:(CIImage *)image size:(CGSize)size
{
    CIFilter *filter = [CIFilter filterWithName:@"CISourceOverCompositing"];
    [filter setDefaults];
    [filter setValue:backgroundImage forKey:kCIInputBackgroundImageKey];
    [filter setValue:[image imageByApplyingTransform:CGAffineTransformMakeTranslation(size.width, size.height)] forKey:kCIInputImageKey];
    
    return filter.outputImage;
}

+ (CVPixelBufferRef)pixelBufferFromCGImage:(CGImageRef)image
{
    CVPixelBufferRef pxbuffer = NULL;
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:
                             [NSNumber numberWithBool:YES], kCVPixelBufferCGImageCompatibilityKey,
                             [NSNumber numberWithBool:YES], kCVPixelBufferCGBitmapContextCompatibilityKey,
                             nil];
    
    size_t width =  CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    size_t bytesPerRow = CGImageGetBytesPerRow(image);
    
    CFDataRef  dataFromImageDataProvider = CGDataProviderCopyData(CGImageGetDataProvider(image));
    GLubyte  *imageData = (GLubyte *)CFDataGetBytePtr(dataFromImageDataProvider);
    
    CVPixelBufferCreateWithBytes(kCFAllocatorDefault,width,height,kCVPixelFormatType_32BGRA,imageData,bytesPerRow,NULL,NULL,(__bridge CFDictionaryRef)options,&pxbuffer);
    
    CFRelease(dataFromImageDataProvider);
    
    return pxbuffer;
}

+ (CGImageRef)createCGImageFromCVPixelBuffer:(CVPixelBufferRef)pixels
{
    
    CVPixelBufferLockBaseAddress(pixels, kCVPixelBufferLock_ReadOnly);
    
    CIImage *ciImage = [CIImage imageWithCVPixelBuffer:pixels];
    CIContext *temporaryContext = [CIContext contextWithOptions:nil];
    CGImageRef videoImage = [temporaryContext createCGImage:ciImage fromRect:CGRectMake(0, 0, CVPixelBufferGetWidth(pixels), CVPixelBufferGetHeight(pixels))];
    
    CVPixelBufferUnlockBaseAddress(pixels, kCVPixelBufferLock_ReadOnly);
    
    return videoImage;
}

@end
