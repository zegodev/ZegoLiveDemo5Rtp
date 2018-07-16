
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "ZegoAVDevice.h"

QVector< deviceConfig > GetAudioDevicesWithOSX()
{
	NSArray *deviceList = [AVCaptureDevice devicesWithMediaType: AVMediaTypeAudio];

	NSLog(@"osx audio devices count is %d", deviceList.count);
    
    QVector<deviceConfig> devices;
    for(AVCaptureDevice *device in deviceList)
    {
        deviceConfig currentDevice;
        NSString *nsDeviceID = [device uniqueID];
        NSString *nsDeviceName = [device localizedName];
        
        currentDevice.deviceId = QString::fromStdString([nsDeviceID cStringUsingEncoding:[NSString defaultCStringEncoding]]);
        currentDevice.deviceName = QString::fromStdString([nsDeviceName cStringUsingEncoding:[NSString defaultCStringEncoding]]);
        
        devices.push_back(currentDevice);
    }
    
    return devices;
}

QVector< deviceConfig > GetVideoDevicesWithOSX()
{
	NSArray *deviceList = [AVCaptureDevice devicesWithMediaType: AVMediaTypeVideo];

	NSLog(@"osx video devices count is %d", deviceList.count);
    
    QVector<deviceConfig> devices;
    for(AVCaptureDevice *device in deviceList)
    {
        deviceConfig currentDevice;
        NSString *nsDeviceID = [device uniqueID];
        NSString *nsDeviceName = [device localizedName];
        
        currentDevice.deviceId = QString::fromStdString([nsDeviceID cStringUsingEncoding:[NSString defaultCStringEncoding]]);
        currentDevice.deviceName = QString::fromStdString([nsDeviceName cStringUsingEncoding:[NSString defaultCStringEncoding]]);
        
        devices.push_back(currentDevice);
    }
    
    return devices;
}
