//
//  LiveRoom-Player.h
//  zegoliveroom
//
//  Created by Randy Qiu on 2017/1/23.
//
//

#ifndef LiveRoom_Player_h
#define LiveRoom_Player_h

#include "./LiveRoomDefines.h"
#include "./LiveRoomCallback-Player.h"
#include "./LiveRoomDefines-Player.h"

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         获取 SDK 支持的最大同时播放流数

         @return 最大支持播放流数
         */
        ZEGO_API int GetMaxPlayChannelCount();
        
        /**
         设置直播观众相关信息通知的回调

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetLivePlayerCallback(ILivePlayerCallback* pCB);
        
        /**
         播放多媒体流

         @param pszStreamID 流 ID
         @param pView 用来渲染播放视频的视图
         @param pszParams 拉流参数
         @return true 成功，false 失败
         @attetion 播放直播流调用此 API
         @note 播放成功后，等待 ILivePlayerCallback::OnPlayStateUpdate 回调
         */
        ZEGO_API bool StartPlayingStream(const char* pszStreamID, void* pView, const char* pszParams = 0);
        
        /**
         播放多媒体流

         @param pszStreamID 流 ID
         @param pView 用来渲染播放视频的视图
         @param info 多媒体流附加信息
         @return 成功，false 失败
         @note 播放成功后，等待 ILivePlayerCallback::OnPlayStateUpdate 回调
         */
        ZEGO_API bool StartPlayingStream2(const char* pszStreamID, void* pView, ZegoStreamExtraPlayInfo* info);

        /**
         更新播放视图
         
         @param pView 播放视图
         @param pszStreamID 流 ID
         @return true 成功，false 失败
         @attention 调用 StartPlayingStream 播放流成功以后，如果要切换流播放 View 或者停止显示流画面，调用该 API 变更
         */
        ZEGO_API bool UpdatePlayView(void* pView, const char* pszStreamID);
        
        /**
         停止播放流

         @param pszStreamID 流 ID
         @return true 成功，false 失败
         */
        ZEGO_API bool StopPlayingStream(const char* pszStreamID);
        
        /**
         申请连麦

         @return 请求 seq，正值为有效，等待 ILivePlayerCallback::OnJoinLiveResponse 回调，回调带回的 seq 与此函数返回值一致
         @note 主播会收到 ILivePublisherCallback::OnJoinLiveRequest 回调
         */
        ZEGO_API int RequestJoinLive();
        
        /**
         回应连麦邀请

         @param seq 回应的邀请 seq
         @param rspResult 回应，0 表示同意
         @return true 成功，false 失败
         @attention 一般在 ILivePlayerCallback::OnInviteJoinLiveRequest 中收到邀请后，调用此 API 回应
         */
        ZEGO_API bool RespondInviteJoinLiveReq(int seq, int rspResult);
        
        
        // * player config
        
        /**
         硬件解码

         @param bRequired true 打开，false 关闭。默认 false
         @return true 成功，false 失败
         @attention 如果要打开，需要在拉流前设置
         @note 打开硬编硬解开关需后台可控，避免碰到版本升级或者硬件升级时出现硬编硬解失败的问题
         */
        ZEGO_API bool RequireHardwareDecoder(bool bRequired);
        
        
        /**
            获取audio route type
         
         @return audio route type
         */
        ZEGO_API int GetAudioRouteType();
        
        /**
         （声音输出）静音开关

         @param bEnable true 不静音，false 静音。默认 true
         @return true 成功，false 失败
         @attention 设置为关闭后，默认扬声器和耳机均无声音输出
         */
        ZEGO_API bool EnableSpeaker(bool bEnable);

        /**
         默认扬声器开关

         @param bOn true 打开，false 关闭。默认 true
         @return true 成功，false 失败
         @attention 设置为关闭后，扬声器无声音，耳机仍有声音输出
         @attention 在推流之前设置,且当前的 SetAudioDeviceMoce 设置为 ZEGO_AUDIO_DEVICE_MODE_COMMUNICATION 时有效
         */
        ZEGO_API bool setBuiltInSpeakerOn(bool bOn);
        
        /**
         设置播放音量

         @param volume 音量取值范围为(0, 100)，数值越大，音量越大。默认 100
         @param pszStreamID 流ID, nullptr表示统一设置所有拉流的播放音量
         @attention 直播时通过此 API 软件调整音量
         */
        ZEGO_API bool SetPlayVolume(int volume, const char* pszStreamID = 0);
        
        /**
         获取当前播放视频的音量

         @param pszStreamID 播放流 ID
         @return 视频的音量值
         @attention 直播时通过此 API 获取当前音量。
         */
        ZEGO_API float GetSoundLevel(const char* pszStreamID);
        
        /**
         设置观看直播的 View 的模式

         @param mode 模式
         @param pszStreamID 播放流 ID
         @return true 成功，false 失败
         @attention 一般在流播放、流新增、全屏切换等其他流尺寸可能变化的场合时调用
         */
        ZEGO_API bool SetViewMode(ZegoVideoViewMode mode, const char* pszStreamID);
        
        /**
         对观看直播视图进行截图

         @param pszStreamID 流 ID
         @return true 成功，false 失败
         @attention 截图成功后，通过回调 ILivePlayerCallback::OnSnapshot 返回结果
         */
        ZEGO_API bool TakeSnapshot(const char* pszStreamID);
        
        
        // * advanced config
        
        /**
         拉流是否接收音频数据
         
         @param pszStreamID 播放流 ID
         @param bActive true 接收，false 不接收
         @return 0 成功，否则失败
         @attention 仅拉 UDP 流有效，必须在拉流后调用才有效
         */
        ZEGO_API int ActivateAudioPlayStream(const char* pszStreamID, bool bActive);
        
        /**
         拉流是否接收视频数据
         
         @param pszStreamID 播放流 ID
         @param bActive true 接收，false 不接收
         @param videoLayer 视频分层类型
         @return 0 成功，否则失败
         @attention 仅拉 UDP 流有效，必须在拉流后调用才有效
         */
        ZEGO_API int ActivateVideoPlayStream(const char* pszStreamID, bool bActive, AV::VideoStreamLayer videoLayer = AV::VideoStreamLayer_Auto);
        
        /**
         设置播放渲染朝向

         @param nRotation 逆时针旋转角度(0/90/180/270)。默认 0
         @param pszStreamID 播放流 ID
         @return true 成功，false 失败
         @attention 一般用于全屏切换、旋转设备时调用，调整播放方向
         */
        ZEGO_API bool SetViewRotation(int nRotation, const char* pszStreamID);
        
        /**
         设置拉流质量监控周期

         @param timeInMS 时间周期，单位为毫秒，取值范围为(500, 60000)。默认为 3000
         @return true 成功，false 失败
         */
        ZEGO_API bool SetPlayQualityMonitorCycle(unsigned int timeInMS);
        
        // * external video render
        
        /**
         设置是否使用外部视频渲染

         @param bEnable true 开启，false 不开启
         @param nType 0 表示使用 OnVideoDataCallback 回调接口，1 表示使用 OnVideoDataCallback2 回调接口，这两个接口都定义在 IZegoVideoRenderCallback 中。
         */
        ZEGO_API void EnableExternalRender(bool bEnable, int nType = 0);
        
        
        /**
         设置外部渲染回调

         @param pCB 回调实现实例
         */
        ZEGO_API void SetExternalRenderCallback(IZegoVideoRenderCallback* pCB);
        
        
        // * audio record
        
        /**
         音频录制回调开关

         @param uMask 启用音频源选择，参考 ZegoAVAPIAudioRecordMask
         @param nSampleRate 采样率 8000, 16000, 22050, 24000, 32000, 44100, 48000
         @param nChannels 声道数 1(单声道) 或 2(双声道)
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableSelectedAudioRecord(unsigned int uMask, int nSampleRate = 44100, int nChannels = 1);
        
        /**
         设置音频录制回调

         @param pCB 回调实现实例
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioRecordCallback(AV::IZegoAudioRecordCallback* pCB);
        
        /**
         音频录制回调开关

         @param bEnable true 开启，false 不开启
         @param nSampleRate 采样率
         @return true 成功，false 失败
         @warning 已废弃，请使用 EnableSelectedAudioRecord
         */
        ZEGO_API bool EnableAudioRecord(bool bEnable, int nSampleRate = 44100);
        
        /**
         设置回调, 接收媒体次要信息
         
         @param pCB 回调函数指针
         */
        ZEGO_API void SetMediaSideCallback(OnMediaSideCallback* pCB);
    }
}

#endif /* LiveRoom_Player_h */
