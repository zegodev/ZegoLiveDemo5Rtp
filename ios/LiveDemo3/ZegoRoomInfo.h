//
//  ZegoRoomInfo.h
//  LiveDemo3
//
//  Created by Strong on 16/6/23.
//  Copyright © 2016年 ZEGO. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZegoRoomInfo : NSObject

@property (nonatomic, copy) NSString *roomID;
@property (nonatomic, copy) NSString *anchorID;
@property (nonatomic, copy) NSString *anchorName;
@property (nonatomic, copy) NSString *roomName;
@property (nonatomic, strong) NSMutableArray *streamInfo;   // stream_id 列表

@end
