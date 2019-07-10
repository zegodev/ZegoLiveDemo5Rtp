//
//  ZegoLiveRoom.h
//  zegoliveroom
//
//  Copyright © 2017年 Zego. All rights reserved.
//

#ifndef ZegoLiveRoom_h
#define ZegoLiveRoom_h

#include "./LiveRoomDefines.h"
#include "./LiveRoomCallback.h"
#include "./LiveRoomDefines-IM.h"

namespace ZEGO
{
	namespace LIVEROOM
	{
        
        /**
         获取SDK版本号

         @return 版本号
         */
        ZEGO_API const char* GetSDKVersion();
        
        
        /**
         获取SDK版本号2

         @return 版本号2
         */
        ZEGO_API const char* GetSDKVersion2();

        
        /**
         设置日志路径

         @param pszLogDir 日志路径
         @return true 成功；flase 失败；
         @discussion 默认日志大小 5 * 1024 * 1024 字节
         */
        ZEGO_API bool SetLogDir(const char* pszLogDir);
        
        /**
         设置日志路径和大小

         @param pszLogDir 日志路径
         @param lLogFileSize 单个日志文件大小
         @return true 成功；flase 失败；
         @discussion 日志大小取值范围[5M, 100M]
         */
        ZEGO_API bool SetLogDirAndSize(const char* pszLogDir, unsigned long long lLogFileSize = 5 * 1024 * 1024);
        
        
        /**
         上传日志
         */
        ZEGO_API void UploadLog();
        
        
        /**
         设置是否打印控制台信息

         @param bVerbose 控制台信息
         */
        ZEGO_API void SetVerbose(bool bVerbose);
        
        
        /**
         设置是否使用测试环境

         @param bTestEnv 测试环境
         */
        ZEGO_API void SetUseTestEnv(bool bTestEnv);
        
        
        /**
         设置平台信息

         @param pszInfo 平台信息
         */
        ZEGO_API void SetPlatformInfo(const char* pszInfo);

        /**
         设置业务类型

         @param nType 业务类型，取值 0（直播类型）或 2（实时音视频类型）。默认为 0
         @return true 成功，false 失败
         @attention 确保在创建接口对象前调用
         */
        ZEGO_API bool SetBusinessType(int nType);
        
        /**
         是否使用聊天室功能

         @param bChatRoom 是否使用聊天室功能，true 使用，false 不使用。默认为 false
         @return true 成功，false 失败
         @attention zegoliveroom 自带 IM 功能，随 SDK 初始化。如果要额外使用聊天室，需要启用聊天室功能
         */
        ZEGO_API bool SetUseChatRoom(bool bChatRoom);
        
        /**
         设置用户信息

         @param pszUserID 用户唯一 ID
         @param pszUserName 用户名字
         @return true 成功，false 失败
         */
        ZEGO_API bool SetUser(const char* pszUserID, const char* pszUserName);

        /**
         获取用户信息

         @return UserID
         */
        ZEGO_API const char* GetUserID();
        
		/**
		 初始化引擎

		 @param jvm jvm 仅用于 Android
		 @param ctx ctx 仅用于 Android
		 @return true 成功，false 失败
		 */
		ZEGO_API bool InitPlatform(void* jvm = 0, void* ctx = 0);
        
        /**
         初始化 SDK

         @param uiAppID Zego 派发的数字 ID, 各个开发者的唯一标识
         @param pBufAppSignature Zego 派发的签名, 用来校验对应 appID 的合法性
         @param nSignatureSize 签名长度（字节）
         @return true 成功，false 失败
         @note 初始化 SDK 失败可能导致 SDK 功能异常
         */
        ZEGO_API bool InitSDK(unsigned int uiAppID, unsigned char* pBufAppSignature, int nSignatureSize);
        
        /**
         反初始化 SDK

         @return true 成功，false 失败
         */
        ZEGO_API bool UnInitSDK();
        
        /**
         设置直播房间相关信息通知的回调

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetRoomCallback(IRoomCallback* pCB);

        /**
         设置房间配置信息

         @param audienceCreateRoom 观众是否可以创建房间。true 可以，false 不可以。默认 true
         @param userStateUpdate 用户状态（用户进入、退出房间）是否广播。true 广播，false 不广播。默认 false
         @discussion 在登录房间前调用有效，退出房间后失效
         */
        ZEGO_API void SetRoomConfig(bool audienceCreateRoom, bool userStateUpdate);
        
        /**
         设置自定义token信息
         
         @param thirdPartyToken 第三方传入的token
         @discussion 使用此函数验证登录时用户的合法性，登录房间前调用，token的生成规则请联系即构。若不需要验证用户合法性，不需要调用此函数
         @discussion 在登录房间前调用有效，退出房间后失效
         */
        ZEGO_API void SetCustomToken(const char *thirdPartyToken);
        
        
        /**
         设置房间最大在线人数

         @param maxCount 最大人数
         @discussion 在登录房间前调用有效，退出房间后失效
         */
        ZEGO_API void SetRoomMaxUserCount(unsigned int maxCount);
        
        /**
         登录房间

         @param pszRoomID 房间 ID
         @param role 成员角色, 参见 ZegoRoomRole
         @param pszRoomName 房间名称
         @return true 成功，false 失败
         */
        ZEGO_API bool LoginRoom(const char* pszRoomID, int role, const char* pszRoomName = "");

        /**
         退出房间

         @return 成功，false 失败
         @attention 退出登录后，等待 IRoomCallback::OnLogoutRoom 回调
         @note 退出房间会停止所有的推拉流
         */
        ZEGO_API bool LogoutRoom();
        
        /**
         发送自定义信令

         @param memberList 信令发送成员列表
         @param memberCount 成员个数
         @param content 信令内容
         @return 消息 seq
         */
        ZEGO_API int SendCustomCommand(ROOM::ZegoUser *memberList, unsigned int memberCount, const char *content);
        
        /**
         设置直播事件回调

         @param pCB 回调对象指针
         */
        ZEGO_API void SetLiveEventCallback(AV::IZegoLiveEventCallback* pCB);
        
        /**
         设置音频视频设备变化的回调

         @param pCB 回调对象指针
         */
        ZEGO_API void SetDeviceStateCallback(AV::IZegoDeviceStateCallback *pCB);
        
        
        //
        // * device
        //

        /**
         获取音频设备列表

         @param deviceType 设备类型
         @param device_count 设备数量
         @return 音频设备列表
         */
        ZEGO_API AV::DeviceInfo* GetAudioDeviceList(AV::AudioDeviceType deviceType, int& device_count);
        
        /**
         设置选用音频设备

         @param deviceType 设备类型
         @param pszDeviceID 设备 ID
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioDevice(AV::AudioDeviceType deviceType, const char* pszDeviceID);
        
        /**
         获取视频设备列表

         @param device_count 设备数量
         @return 视频设备列表
         */
        ZEGO_API AV::DeviceInfo* GetVideoDeviceList(int& device_count);
        
        /**
         释放设备列表

         @param parrDeviceList 设备列表
         */
        ZEGO_API void FreeDeviceList(AV::DeviceInfo* parrDeviceList);
        
        /**
         设置选用视频设备

         @param pszDeviceID 设备 ID
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoDevice(const char* pszDeviceID, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
#if defined(WIN32) || TARGET_OS_OSX 
        /**
         系统声卡声音采集开关

         @param bEnable true 打开，false 失败
         */
        ZEGO_API void EnableMixSystemPlayout(bool bEnable);
        
        /**
         获取麦克风音量

         @param deviceId 麦克风 deviceId
         @return -1: 获取失败，0~100 麦克风音量
         @note 切换麦克风后需要重新获取麦克风音量
         */
        ZEGO_API int GetMicDeviceVolume(const char *deviceId);
        
        /**
         设置麦克风音量

         @param deviceId 麦克风 deviceId
         @param volume 音量，取值(0,100)
         */
        ZEGO_API void SetMicDeviceVolume(const char *deviceId, int volume);
        
        /**
         获取麦克风是否静音
         
         @param deviceId 麦克风 deviceId
         @return true 静音，false 不静音
         */
        ZEGO_API bool GetMicDeviceMute(const char *deviceId);
        
        /**
         设置麦克风静音
         
         @param deviceId 麦克风 deviceId
         @param mute true 静音，false 不静音
         */
        ZEGO_API void SetMicDeviceMute(const char *deviceId, bool mute);
        
        /**
         获取扬声器音量

         @param deviceId 扬声器 deviceId
         @return -1: 获取失败，0~100 扬声器音量
         @note 切换扬声器后需要重新获取音量
         */
        ZEGO_API int GetSpeakerDeviceVolume(const char *deviceId);
        
        /**
         设置扬声器音量

         @param deviceId 扬声器 deviceId
         @param volume 音量，取值 (0，100)
         */
        ZEGO_API void SetSpeakerDeviceVolume(const char *deviceId, int volume);
        
        /**
         获取 App 中扬声器音量

         @param deviceId 扬声器 deviceId
         @return -1: 获取失败，0~100 扬声器音量
         */
        ZEGO_API int GetSpeakerSimpleVolume(const char *deviceId);
        
        /**
         设置 App 中扬声器音量

         @param deviceId 扬声器 deviceId
         @param volume 音量，取值 (0，100)
         */
        ZEGO_API void SetSpeakerSimpleVolume(const char *deviceId, int volume);

        /**
         获取扬声器是否静音

         @param deviceId 扬声器 deviceId
         @return true 静音，false 不静音
         */
        ZEGO_API bool GetSpeakerDeviceMute(const char *deviceId);
        
        /**
         设置扬声器静音

         @param deviceId 扬声器 deviceId
         @param mute true 静音，false 不静音
         */
        ZEGO_API void SetSpeakerDeviceMute(const char *deviceId, bool mute);
        
        /**
         获取 App 中扬声器是否静音

         @param deviceId 扬声器 deviceId
         @return true 静音，false 不静音
         */
        ZEGO_API bool GetSpeakerSimpleMute(const char *deviceId);
        
        /**
         设置 App 中扬声器静音

         @param deviceId 扬声器 deviceId
         @param mute true 静音，false 不静音
         */
        ZEGO_API void SetSpeakerSimpleMute(const char *deviceId, bool mute);
        
        /**
         获取默认的视频设备
         
         @param deviceId 设备 Id
         @param deviceIdLength deviceId 字符串分配的长度
         @note 如果传入的字符串 buffer 长度小于默认 deviceId 的长度，则 deviceIdLength 返回实际需要的字符串长度
         */
        ZEGO_API void GetDefaultVideoDeviceId(char *deviceId, unsigned int *deviceIdLength);
        
        /**
         获取默认的音频设备

         @param deviceType 音频类型
         @param deviceId 设备 Id
         @param deviceIdLength deviceId 字符串分配的长度
         @note 如果传入的字符串 buffer 长度小于默认 deviceId 的长度，则 deviceIdLength 返回实际需要的字符串长度
         */
        ZEGO_API void GetDefaultAudioDeviceId(AV::AudioDeviceType deviceType, char *deviceId, unsigned int *deviceIdLength);

        /**
         监听设备的音量变化

         @param deviceType 音频类型
         @param deviceId 设备 Id
         @return true 成功，false 失败
         @note 设置后如果有音量变化（包括 app 音量）通过 IZegoDeviceStateCallback::OnAudioVolumeChanged 回调
         */
        ZEGO_API bool SetAudioVolumeNotify(AV::AudioDeviceType deviceType, const char *deviceId);
        
        /**
         停止监听设备的音量变化

         @param deviceType 设备类型
         @param deviceId 设备 Id
         @return true 成功，false 失败
         */
        ZEGO_API bool StopAudioVolumeNotify(AV::AudioDeviceType deviceType, const char *deviceId);

#endif // defined(WIN32) || TARGET_OS_OSX 
        /**
         设置“音视频引擎状态通知”的回调

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAVEngineCallback(IAVEngineCallback* pCB);
        
        /**
         设置配置信息

         @param config config 配置信息
         
         @attention 配置项的写法，例如 "keep_audio_session_active=true", 等号后面值的类型要看下面每一项的定义
         @attention "prefer_play_ultra_source", int value, 确保在 InitSDK 前调用，但开启拉流加速(config为“prefer_play_ultra_source=1”)可在 InitSDK 之后，拉流之前调用
         @attention "keep_audio_session_active", bool value, default: false, must be setting before engine started. if set true, app need to set the session inactive yourself. just be available for iOS
         @attention "enforce_audio_loopback_in_sync", bool value, default: false. enforce audio loopback in synchronous method for iOS
         @attention "audio_session_mix_with_others", bool value, default: true. set AVAudioSessionCategoryOptionMixWithOthers for iOS
         @attention "camera_orientation_mode", string value: auto/hardcode/0/90/180/270. for Android, Windows
         @attention "camera_check_position", bool value, default: false. for Android
         @attention "lower_audio_cap_sample_rate", bool value, default: false. enforce to use lower audio capture sample. for Android
         @attention "alsa_capture_device_name" string value: plughw:[card_id],[device_id], eg: plughw:1,0, default is plug:default. view the device list with arecord. for Linux
         @attention "alsa_playback_device_name" string value: plughw:[card_id],[device_id], eg: plughw:1,0, default is plug:default. view the device list with aplay. for Linux
         @attention "play_nodata_abort", bool value, default: false，设置拉流时没拉到数据是否终止拉流，设置为false表示不终止，设置为true表示终止，拉流之前调用有效
         */
        ZEGO_API void SetConfig(const char *config);
        
#if defined(ANDROID) || TARGET_OS_IPHONE
        /**
         设置是否允许SDK使用麦克风设备
         
         @param enable true 表示允许使用麦克风，false 表示禁止使用麦克风，此时如果SDK在占用麦克风则会立即释放。
         @return bool true 调用成功，false 调用失败。
         @discussion 调用时机为引擎创建后的任意时刻。
         @note 接口由于涉及对设备的操作，极为耗时，不建议随便调用，只在真正需要让出麦克风给其他应用的时候才调用。
         */
        ZEGO_API bool EnableMicDevice(bool enable);
#endif
        
	}
}

#endif
