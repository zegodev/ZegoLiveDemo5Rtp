//
//  LiveRoom-Publisher.h
//  zegoliveroom
//
//  Created by Randy Qiu on 2017/1/23.
//
//

#ifndef LiveRoom_Publisher_h
#define LiveRoom_Publisher_h

#include "./LiveRoomDefines-Publisher.h"
#include "./LiveRoomCallback-Publisher.h"

namespace AVE
{
    class VideoCaptureFactory;
    class MediaCaptureFactory;
    class VideoFilterFactory;
    struct AudioFrame;
    struct ExtPrepSet;
    typedef void (*OnPrepCallback)(const AVE::AudioFrame& inFrame, AVE::AudioFrame& outFrame);
}

namespace ZEGO
{
    namespace LIVEROOM
    {
        /**
         设置直播主播相关信息通知的回调

         @param pCB 回调对象指针
         @return true 成功，false 失败
         */
        ZEGO_API bool SetLivePublisherCallback(ILivePublisherCallback* pCB);
        
        /**
         设置本地预览视图

         @param pView 用于渲染本地预览视频的视图
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool SetPreviewView(void* pView, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         启动本地预览
         
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 启动本地预览前，要调用 LIVEROOM::SetPreviewView 设置本地预览视图
         */
        ZEGO_API bool StartPreview(AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         结束本地预览
         
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 建议停止推流，或本地预览结束后，调用该 API 停止本地预览
         */
        ZEGO_API bool StopPreview(AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置或更新推流的附加信息

         @param pszStreamExtraInfo 流附加信息
         @param idx 推流 channel Index. 默认为主Channel
         @return 更新流附加信息成功后，同一房间内的其他人会收到 OnStreamExtraInfoUpdated 通知
         */
        ZEGO_API bool SetPublishStreamExtraInfo(const char *pszStreamExtraInfo, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         自定义转推目的地

         @param pszCustomPublishTarget 目的 rmtp 推流地址
         @param idx 推流 channel Index. 默认为主Channel
         */
        ZEGO_API void SetCustomPublishTarget(const char *pszCustomPublishTarget, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         开始直播

         @param pszTitle 直播名称
         @param pszStreamID 流 ID
         @param flag 直播属性，参考 ZegoPublishFlag
         @param pszParams 推流参数
         @return true 成功，false 失败
         @attention 推流成功后，等待 ILivePublisherCallback::OnPublishStateUpdate 回调
         */
        ZEGO_API bool StartPublishing(const char* pszTitle, const char* pszStreamID, int flag, const char* pszParams = 0);
        
        /**
         开始直播
         
         @param pszTitle 直播名称
         @param pszStreamID 流 ID
         @param flag 直播属性，参考 ZegoPublishFlag
         @param pszParams 推流参数
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流成功后，等待 ILivePublisherCallback::OnPublishStateUpdate 回调
         @attention 调用此接口SetMixStreamConfig无效，混流需要调用MixStream
         */
        ZEGO_API bool StartPublishing2(const char* pszTitle, const char* pszStreamID, int flag, const char* pszParams = 0, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         停止直播

         @param flag 保留字段
         @param pszMsg 自定义信息，server 对接流结束回调包含此字段内容
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool StopPublishing(int flag = 0, const char* pszMsg = 0, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         回应连麦申请

         @param seq 收到的连麦申请 seq (通过 ILivePublisherCallback::OnJoinLiveRequest 收到申请)
         @param rspResult 回应，0 表示同意
         @return true 成功，false 失败
         @note 申请者会收到 OnJoinLiveResponse 回调
         */
        ZEGO_API bool RespondJoinLiveReq(int seq, int rspResult);
        
        /**
         邀请连麦

         @param pszUserID 准备邀请的用户 ID
         @return 请求 seq，正值为成功，其他为失败
         @attention 邀请成功后，等待 ILivePublisherCallback::OnInviteJoinLiveResponse 回调
         @note 被邀请的用户会收到 OnInviteJoinLiveRequest 回调
         */
        ZEGO_API int InviteJoinLive(const char* pszUserID);

        /**
         结束连麦

         @param pszUserID 指定结束连麦的用户 ID
         @return 请求seq，正值为有效，等待 ILivePublisherCallback::OnEndJoinLive 回调
         */
        ZEGO_API int EndJoinLive(const char* pszUserID);

        /**
         设置混流数据配置

         @warning Deprecated，请使用 ZEGO::MIXSTREAM::ZegoStreamMixer::mixStream
         
         @param pszMixStreamID 混流 ID
         @param nMixVideoWidth 混流后视频的宽
         @param nMixVideoHeight 混流后视频的高
         @return true 成功，false 失败
         */
        ZEGO_API bool SetMixStreamConfig(const char* pszMixStreamID, int nMixVideoWidth, int nMixVideoHeight);
        
        /**
         更新混流配置

         @warning Deprecated，请使用 ZEGO::MIXSTREAM::ZegoStreamMixer::mixStream
         
         @param pConfigList 输入流配置数组首元素指针
         @param size 输入流个数
         @return true 成功，false 失败
         */
        ZEGO_API bool UpdateMixInputStreams(AV::ZegoMixStreamConfig* pConfigList, int size);
        
        /**
         开始混流
         
         @warning Deprecated，请使用 ZEGO::MIXSTREAM::ZegoStreamMixer::mixStream
         
         @param config 混流配置
         @param seq 请求序号，回调会带回此 seq
         @return true 成功，等待回调，false 失败
         @note 每次需要更新混流配置时，都可以调用此接口；如果需要多次调用，可以通过传入不同的 seq 区分回调
         */
        ZEGO_API bool MixStream(const AV::ZegoCompleteMixStreamConfig& config, int seq);
        
        /**
         硬件编码开关

         @param bRequired true 开启，false 关闭。默认 false
         @return true 成功，false 失败
         @attention 如果要打开，需要在推流前设置
         @note 打开硬编硬解开关需后台可控，避免碰到版本升级或者硬件升级时出现硬编硬解失败的问题
         */
        ZEGO_API bool RequireHardwareEncoder(bool bRequired);
        
        /**
         设置视频码率

         @param nBitrate 码率，单位为bps
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoBitrate(int nBitrate, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);

        /**
         设置视频帧率

         @param nFps 帧率
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoFPS(int nFps, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置视频编码输出分辨率

         @param nWidth 宽
         @param nHeight 高
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoEncodeResolution(int nWidth, int nHeight, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置视频采集分辨率

         @param nWidth 宽
         @param nHeight 高
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoCaptureResolution(int nWidth, int nHeight, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         主播开启美颜功能

         @param nFeature 美颜特性。默认无美颜
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API bool EnableBeautifying(int nFeature, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置美颜磨皮的采样步长

         @param step 采样步长，取值范围[1,16]。默认 4.0
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置。设置时需确保对应美颜特性开启
         */
        ZEGO_API bool SetPolishStep(float step, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置美颜采样颜色阈值

         @param factor 采样颜色阈值，取值范围[0,16]。默认 4.0
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置。设置时需确保对应美颜特性开启
         */
        ZEGO_API bool SetPolishFactor(float factor, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置美颜美白的亮度修正参数

         @param factor 亮度修正参数，取值范围[0,1]，值越大亮度越暗。默认 0.5
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置。设置时需确保对应美颜特性开启
         */
        ZEGO_API bool SetWhitenFactor(float factor, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置锐化参数

         @param factor 锐化参数，取值范围[0,2]，值越大锐化越强。默认 0.2
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置。设置时需确保对应美颜特性开启
         */
        ZEGO_API bool SetSharpenFactor(float factor, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置滤镜

         @param nIndex 滤镜索引。默认不使用滤镜
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API bool SetFilter(int nIndex, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置本地预览视频视图的模式

         @param mode 模式
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流开始前调用本 API 进行参数配置
         */
        ZEGO_API bool SetPreviewViewMode(ZegoVideoViewMode mode, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         是否启用预览镜像
         
         @param bEnable true 启用，false 不启用。默认 true
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @note 默认启用预览镜像
         */
        ZEGO_API bool EnablePreviewMirror(bool bEnable, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         是否启用预览和推流镜像
         
         @param mode 镜像模式
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @note 默认启用预览镜像，不启用推流镜像
         */
        ZEGO_API bool SetVideoMirrorMode(AV::ZegoVideoMirrorMode mode, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置预览渲染朝向

         @param nRotation 旋转角度(0/90/180/270)。默认 0
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API bool SetPreviewRotation(int nRotation, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         开启麦克风

         @param bEnable true 打开，false 关闭。默认 true
         @return true 成功，false 失败
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API bool EnableMic(bool bEnable);
        
        /**
         设置音频码率

         @param bitrate 码率
         @return true 成功，false 失败
         */
        ZEGO_API bool SetAudioBitrate(int bitrate);
        
        /**
         设置音频设备模式

         @param mode 模式
         @attention 确保在 Init 前调用
         */
        ZEGO_API void SetAudioDeviceMode(AV::ZegoAVAPIAudioDeviceMode mode);
        
        /**
         音频采集自动增益开关

         @param bEnable true 开启，false 关闭
         @return true 成功，false 失败
         @discussion 建议在推流前调用设置
         */
        ZEGO_API bool EnableAGC(bool bEnable);

        /**
         回声消除开关

         @param bEnable true 开启，false 关闭
         @return true 成功，false 失败
         @discussion 建议在推流前调用设置
         */
        ZEGO_API bool EnableAEC(bool bEnable);
        
        /**
         开启摄像头

         @param bEnable true 开启，false 关闭。默认 true
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableCamera(bool bEnable, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);

        /**
         截预览图
         
         @param idx 推流 channel Index. 默认为主Channel
         @return true 成功，通过回调返回结果，false 失败
         */
        ZEGO_API bool TakeSnapshotPreview(AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         开启采集监听

         @param bEnable true 打开，false 关闭。默认 false
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableLoopback(bool bEnable);
        
        /**
         设置监听音量

         @param volume 音量大小，取值（0, 100）。默认 100
         @attention 推流时可调用本 API 进行参数配置
         */
        ZEGO_API void SetLoopbackVolume(int volume);
        
        /**
         设置采集音量
         
         @param volume 音量大小，取值（0, 100）。默认 100
         @attention SDK初始化成功后调用
         */
        ZEGO_API void SetCaptureVolume(int volume);
        
        /**
         混音开关

         @param bEnable true 启用混音输入，false 关闭混音输入。默认 false
         @return true 成功，false 失败
         */
        ZEGO_API bool EnableAux(bool bEnable);
        
        /**
         混音静音开关

         @param bMute true: aux 输入播放静音，false: 不静音。默认 false
         @return true 成功，false 失败
         */
        ZEGO_API bool MuteAux(bool bMute);
        
        /**
         获取当前采集的音量

         @return 当前采集音量大小
         */
        ZEGO_API float GetCaptureSoundLevel();
        
        /**
         设置水印的图片路径

         @param filePath 图片路径
         @param idx 推流 channel Index. 默认为主Channel
         @attention 推流开始前调用本 API 进行参数配置
         */
        ZEGO_API void SetWaterMarkImagePath(const char *filePath, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置水印在采集视频中的位置

         @param left 左上角坐标的第一个元素
         @param top 左上角坐标的第二个元素，即左上角坐标为 (left, top)
         @param right 右下角坐标的第一个元素
         @param bottom 右下角坐标的第二个元素，即右下角坐标为 (right, bottom)
         @param idx 推流 channel Index. 默认为主Channel
         @note 左上角为坐标系原点，区域不能超过编码分辨率设置的大小
         */
        ZEGO_API void SetPublishWaterMarkRect(int left, int top, int right, int bottom, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);

        /**
         设置水印在预览视频中的位置

         @param left 左上角坐标的第一个元素
         @param top 左上角坐标的第二个元素，即左上角坐标为 (left, top)
         @param right 右下角坐标的第一个元素
         @param bottom 右下角坐标的第二个元素，即右下角坐标为 (right, bottom)
         @param idx 推流 channel Index. 默认为主Channel
         @note 左上角为坐标系原点，区域不能超过 preview 的大小
         */
        ZEGO_API void SetPreviewWaterMarkRect(int left, int top, int right, int bottom, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置外部采集模块

         @param factory 工厂对象
         @param idx 推流 channel Index. 默认为主Channel
         @note 必须在 InitSDK 前调用，并且不能置空
         */
        ZEGO_API void SetVideoCaptureFactory(AVE::VideoCaptureFactory* factory, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置选用分层编码
         @param codecId 设备 ID
         @return true 成功，false 失败
         */
        ZEGO_API bool SetVideoCodecId(AV::ZegoVideoCodecAvc codecId, AV::PublishChannelIndex nChannel = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置外部滤镜模块

         @param factory 工厂对象
         @param idx 推流 channel Index. 默认为主Channel
         @note 必须在 InitSDK 前调用，并且不能置空
         */
        ZEGO_API void SetVideoFilterFactory(AVE::VideoFilterFactory* factory, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         设置音频前处理函数

         @param prep 前处理函数指针
         */
        ZEGO_API void SetAudioPrep(void(*prep)(const short* inData, int inSamples, int sampleRate, short *outData));
        
        /**
         设置音频前处理函数

         @param prep 前处理函数指针
         @param set 预处理的采样率等参数设置
         */
        ZEGO_API void SetAudioPrep2(AVE::OnPrepCallback prep, const AVE::ExtPrepSet& set);
        
        /**
         设置编码器码率控制策略

         @param strategy 策略配置，参考 ZegoVideoEncoderRateControlStrategy
         @param encoderCRF 当策略为恒定质量（ZEGO_RC_VBR/ZEGO_RC_CRF）有效，取值范围 [0~51]，越小质量越好，建议取值范围 [18, 28]
         @param idx 推流 channel Index. 默认为主Channel
         */
        ZEGO_API void SetVideoEncoderRateControlConfig(int strategy, int encoderCRF, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         发送媒体次要信息开关

         @param bStart true 开启, false 关闭
         @param bOnlyAudioPublish true 纯音频直播，不传输视频数据, false 音视频直播，传输视频数据
         @param idx 推流 channel Index. 默认为主Channel
         @attention onlyAudioPublish 开关在 start 开关开启时才生效
         */
        ZEGO_API void SetMediaSideFlags(bool bStart, bool bOnlyAudioPublish, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        /**
         发送媒体次要信息

         @param inData 媒体次要信息数据
         @param dataLen 数据长度
         @param bPacket 是否外部已经打包好包头，true 已打包, false 未打包
         @param idx 推流 channel Index. 默认为主Channel
         */
        ZEGO_API void SendMediaSideInfo(const unsigned char *inData, int dataLen, bool bPacket, AV::PublishChannelIndex idx = AV::PUBLISH_CHN_MAIN);
        
        
        /**
         帧顺序检测开关
         
         @param bEnalbe true 检测帧顺序，不支持B帧； false 不检测帧顺序，支持B帧，可能出现短暂花屏
         */
        ZEGO_API void EnableCheckPoc(bool bEnable);
        
        /**
         设置视频采集缩放时机
         
         @param mode 视频采集缩放时机，请参考 AV::ZegoCapturePipelineScaleMode 定义。默认为 ZegoCapturePipelinePreScale
         @discussion 初始化 SDK 后，StartPreview 前调用。StartPreview 之后设置不会立即生效，而是在下次摄像头启动预览时生效。
         */
        ZEGO_API void SetCapturePipelineScaleMode(AV::ZegoCapturePipelineScaleMode mode);
        
        /**
         设置延迟模式

         @param mode 延迟模式，默认 ZEGO_LATENCY_MODE_NORMAL
         @attention 确保在推流前调用
         */
        ZEGO_API void SetLatencyMode(AV::ZegoAVAPILatencyMode mode);
        
        /**
         设置推流音频声道数
         
         @param count 声道数，1 或 2，默认为 1（单声道）
         @attention 必须在推流前设置
         @note SetLatencyMode 设置为 ZEGO_LATENCY_MODE_NORMAL 或 ZEGO_LATENCY_MODE_NORMAL2 才能设置双声道，在移动端双声道通常需要配合音频前处理才能体现效果。
         */
        ZEGO_API void SetAudioChannelCount(int count);
        
        /**
         设置混音音量

         @param volume 0~100，默认为 50
         */
        ZEGO_API void SetAuxVolume(int volume);
        
        /**
         是否开启离散音频包发送

         @param bEnable true 开启，此时关闭麦克风后，不会发送静音包；false 关闭，此时关闭麦克风后会发送静音包
         @attention 确保在推流前调用，只有纯 UDP 方案才可以调用此接口
         */
        ZEGO_API void EnableDTX(bool bEnable);
        
        /**
         是否开启流量控制

         @param properites 流量控制属性 (帧率，分辨率），参考 ZegoTrafficControlProperty 定义。默认 ZEGO_TRAFFIC_CONTROL_ADAPTIVE_FPS
         @param bEnable true 开启，false 关闭。默认开启
         @attention bEnable设置为false时，properties参数无效
         @attention 确保在推流前调用，在纯 UDP 方案才可以调用此接口
         */
        ZEGO_API void EnableTrafficControl(int properites, bool bEnable);
        
        /**
        音频采集噪声抑制开关
         
        @param bEnalbe true 开启，false 关闭
        @return true 调用成功，false 调用失败
         */
        ZEGO_API bool EnableNoiseSuppress(bool bEnable);
        
        /**
         设置推流质量监控周期
         
         @param timeInMS 时间周期，单位为毫秒，取值范围为(500, 60000)。默认为 3000
         @return true 成功，false 失败
         @attention 必须在推流前调用才能生效。该设置会影响 ILivePublisherCallback::OnPublishQualityUpdate 的回调频率
         */
        ZEGO_API bool SetPublishQualityMonitorCycle(unsigned int timeInMS);
    }
}
#endif /* LiveRoom_Publisher_h */
