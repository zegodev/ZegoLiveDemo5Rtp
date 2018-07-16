//
//  SampleHandler.m
//  GameLive
//
//  Created by summery on 28/12/2017.
//  Copyright © 2017 ZEGO. All rights reserved.
//

#import "SampleHandler.h"
#import "ZegoAVKitManager.h"

@implementation SampleHandler

- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo {
    // User has requested to start the broadcast. Setup info from the UI extension can be supplied but optional.
    NSString *liveTitle = (NSString *)setupInfo[@"title"];
    CGFloat videoWidth = [(NSNumber *)setupInfo[@"width"] floatValue] != 0 ? [(NSNumber *)setupInfo[@"width"] floatValue] : [[UIScreen mainScreen] bounds].size.width;
    CGFloat videoHeight = [(NSNumber *)setupInfo[@"height"] floatValue] != 0 ? [(NSNumber *)setupInfo[@"height"] floatValue] : [[UIScreen mainScreen] bounds].size.height;
    
    NSLog(@"[LiveDemo5-GameLive] videoSize in setupInfo: %@", NSStringFromCGSize(CGSizeMake(videoWidth, videoHeight)));
    
    [[ZegoAVKitManager sharedInstance] startLiveWithTitle:liveTitle videoSize:CGSizeMake(videoWidth * 2, videoHeight * 2)];
}

- (void)broadcastPaused {
    // User has requested to pause the broadcast. Samples will stop being delivered.
}

- (void)broadcastResumed {
    // User has requested to resume the broadcast. Samples delivery will resume.
}

- (void)broadcastFinished {
    // User has requested to finish the broadcast.
    NSLog(@"[LiveDemo5-GameLive] stop live");
    [[ZegoAVKitManager sharedInstance] stopLive];
}

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType {
    
    switch (sampleBufferType) {
        case RPSampleBufferTypeVideo:
            // Handle audio sample buffer
            [[ZegoAVKitManager sharedInstance] handleVideoInputSampleBuffer:sampleBuffer];
            break;
        case RPSampleBufferTypeAudioApp:
            // Handle audio sample buffer for app audio
            [[ZegoAVKitManager sharedInstance] handleAudioInputSampleBuffer:sampleBuffer withType:RPSampleBufferTypeAudioApp];
            break;
        case RPSampleBufferTypeAudioMic:
            [[ZegoAVKitManager sharedInstance] handleAudioInputSampleBuffer:sampleBuffer withType:RPSampleBufferTypeAudioMic];
            // Handle audio sample buffer for mic audio
            break;
            
        default:
            break;
    }
}

@end
