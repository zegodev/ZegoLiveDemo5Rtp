//
//  zego-api-external-video-render.h
//

#ifndef zego_api_extrnal_video_render_h
#define zego_api_extrnal_video_render_h
#include "video_format.h"
#include "zego-api-defines.h"

namespace ZEGO
{
    namespace EXTERNAL_RENDER
    {
        class IZegoExternalRenderCallback2
        {
        public:
        
            /**
             视频帧数据回调
             
             @param pData 视频数据起始地址，windows 平台上回调数据格式为 RGBA32
             @param dataLen 视频数据长度
             @param pszStreamID 流 ID
             @param width 视频宽度
             @param height 视频高度
             @param strides 每个平面一行字节数（RGBA 只需考虑 strides[0]）
             */
            virtual void OnVideoDataCallback(const unsigned char *pData, int dataLen, const char* pszStreamID, int width, int height, int strides[4]) {};
            
            /**
             视频帧数据回调2
             @param pData 视频数据起始地址
             @param dataLen 视频数据长度起始地址
             @param pszStreamID 流 ID
             @param width 视频帧宽度
             @param height 视频帧高度
             @param strides 视频帧每个平面一行字节数
             @param pixel_format 视频帧数据格式
             */
            virtual void OnVideoDataCallback2(const unsigned char **pData, int* dataLen, const char* pszStreamID, int width, int height, int strides[4], AVE::VideoPixelFormat pixelFormat) {}
            
            virtual ~IZegoExternalRenderCallback2() {}
        };
        
        extern ZEGOAVKIT_API const char* kZegoVideoDataMainPublishingStream;
        
        extern ZEGOAVKIT_API const char* kZegoVideoDataAuxPublishingStream;
        
        ZEGOAVKIT_API bool SetExternalRenderCallback(IZegoExternalRenderCallback2* callback);
       
		/**
		设置是否使用外部视频渲染

		@param externalRender true 开启，false 不开启，默认为不开启
		@param type 外部渲染类型，详见类型 VideoExternalRenderType
		@note 在InitSDK之前调用。
		*/
        ZEGOAVKIT_API bool EnableExternalRender(bool externalRender, AV::VideoExternalRenderType type);
        
        /**
         设置当VideoExternalRenderType为DECODE_RENDER时，是否开启外部视频渲染（拉流）
         
         @param pszStreamID 播放流ID
         @param bEnable true 开启， false 不开启，默认为不开启
         @note 只要当VideoExternalRenderType设置为DECODE_RENDER，该接口才有效
         */
        ZEGOAVKIT_API bool EnableVideoRender(bool bEnable, const char *pszStreamID);
        
		/**
		设置当VideoExternalRenderType为DECODE_RENDER时，是否开启外部视频渲染（拉流）

		@param nPlayChannel 播放通道
		@param bEnable true 开启， false 不开启，默认为不开启
		@note 只要当VideoExternalRenderType设置为DECODE_RENDER，该接口才有效
        @note 在初始化SDK之后调用有效
		*/
		ZEGOAVKIT_API bool EnableVideoRender(bool bEnable, int nPlayChannel);

		/**
		设置当VideoExternalRenderType为DECODE_RENDER时，是否开启外部视频渲染（推流预览）

		@param bEnable true 开启， false 不开启，默认为不开启
		@param nPublishChannel 推流通道，默认为主通道
		@note 只要当VideoExternalRenderType设置为DECODE_RENDER，该接口才有效
        @note 在初始化SDK之后调用有效
		*/
		ZEGOAVKIT_API bool EnableVideoPreview(bool bEnable, AV::PublishChannelIndex nPublishChannel = AV::PUBLISH_CHN_MAIN);
    }
}

#endif /* zego_api_extrnal_video_render_h */
