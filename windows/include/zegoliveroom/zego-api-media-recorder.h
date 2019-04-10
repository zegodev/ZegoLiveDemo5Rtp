#ifndef zego_api_media_recorder_h
#define zego_api_media_recorder_h

#include <zego-api-defines.h>

namespace ZEGO
{
    namespace MEDIA_RECORDER
    {
     
        /** 媒体录制类型 */
        enum ZegoMediaRecordType
        {
            ZEGO_MEDIA_RECORD_NONE = 0,  /**< 不录制任何数据 */
            ZEGO_MEDIA_RECORD_AUDIO,     /**< 只录制音频 */
            ZEGO_MEDIA_RECORD_VIDEO,     /**< 只录制视频 */
            ZEGO_MEDIA_RECORD_BOTH       /**< 同时录制音频、视频 */
        };
        
        /** 媒体录制通道 */
        enum ZegoMediaRecordChannelIndex
        {
            ZEGO_MEDIA_RECORD_CHN_MAIN = 0,    /**< 第一路媒体录制通道 */
            ZEGO_MEDIA_RECORD_CHN_AUX          /**< 第二路媒体录制通道 */
        };
        
        /** 媒体录制格式 */
        enum ZegoMediaRecordFormat
        {
            ZEGO_MEDIA_RECORD_FLV = 1,       /**< FLV格式 */
            ZEGO_MEDIA_RECORD_MP4 = 2        /**< MP4格式 */
        };
        
        class IZegoMediaRecordCallback
        {
        public:
            /**
             媒体录制回调
             
             @param errCode: 错误码， 0: 成功，1：存储路径太长，2：初始化 avcontext 失败，3：打开文件失败，4：写文件失败
             @param channelIndex 录制通道
             @param storagePath 录制文件存储路径
             */
            virtual void OnMediaRecord(int errCode, ZegoMediaRecordChannelIndex channelIndex, const char* storagePath) = 0;
            
            /**
             录制信息更新回调
             
             @param channelIndex 录制通道
             @param storagePath 录制文件存储路径
             @param duration 录制时长，单位毫秒
             @param fileSize 文件大小，单位字节
             */
            virtual void OnRecordStatusUpdate(const ZegoMediaRecordChannelIndex channelIndex, const char* storagePath, const unsigned int duration, const unsigned int fileSize) {}
            
            virtual ~ IZegoMediaRecordCallback() {}
        };
        
        /**
         设置录制回调
         
         @param delegate 媒体录制回调
         @discussion StartRecord后才有回调
         */
        ZEGOAVKIT_API bool SetZegoMediaRecordCallback(IZegoMediaRecordCallback* pCB);
        
        /**
         开始录制
         
         @param channelIndex 录制通道
         @param recordType 录制类型
         @param storagePath 录制文件存储路径
         @param enableStatusCallback 是否开启录制状态回调，true: 表示会以指定的 interval 间隔回调 {@link IZegoMediaRecordCallback#OnRecordStatusUpdate}。false: 表示不回调
         @param interval 录制信息更新频率，单位毫秒，有效范围：1000-10000，默认值3000
         @param isFragment 录制文件是否分片，MP4格式才有效
         @param return true 调用成功，false 调用失败
         @discussion 必须在init sdk之后调用
         @discussion 要监听录制文件的状态，需要实现{@link IZegoMediaRecordCallback::OnRecordStatusUpdate}。
         */
        ZEGOAVKIT_API bool StartRecord(ZegoMediaRecordChannelIndex channelIndex, ZegoMediaRecordType recordType, const char* storagePath, const bool enableStatusCallback = false, const int interval = 3000, ZegoMediaRecordFormat recordFormat = ZegoMediaRecordFormat::ZEGO_MEDIA_RECORD_FLV, bool isFragment = false);
        
        /**
         停止录制
         
         @param channelIndex 录制通道
         */
        ZEGOAVKIT_API void StopRecord(ZegoMediaRecordChannelIndex channelIndex);
    }
}

#endif
