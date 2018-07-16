
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "ZegoCGImageToQImage.h"

QImage * CGImageToQImage(void *pImage)
{
    CGImageRef cgImage =  (CGImageRef)pImage;
    
    CFDataRef pixelData= CGDataProviderCopyData(CGImageGetDataProvider(cgImage));
    unsigned char * ucBuffer = (unsigned char *)CFDataGetBytePtr(pixelData);
    
    size_t width = CGImageGetWidth(cgImage);
    size_t height = CGImageGetHeight(cgImage);
    QImage *qImage = new QImage(ucBuffer ,width, height, QImage::Format_ARGB32);
    *qImage = qImage->rgbSwapped();
    return qImage;
    
}
