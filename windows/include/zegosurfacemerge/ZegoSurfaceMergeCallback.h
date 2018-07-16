#pragma once

#include "video_capture.h"

namespace ZEGO
{
    namespace SurfaceMerge
    {
        class IZegoSurfaceMergeCallback
        {
        public:
            /// \brief 视频数据混合后的数据结果
            /// \param surfaceMergeData 视频数据
            /// \param datalength       视频数据长度
            /// \param frameFormat      视频数据格式，具体见video_capture头文件定义
            /// \prarm reference_time   采集到该帧的时间戳
            /// \param reference_time_scale  采集时间戳单位，毫秒10^3，微妙10^6，纳秒10^9
            virtual void OnSurfaceMergeResult(
                unsigned char *surfaceMergeData,
                int datalength,
                const AVE::VideoCaptureFormat& frameFormat, 
                unsigned long long reference_time,
                unsigned int reference_time_scale) {}

			/// \brief 视频数据混合前的单个图像数据结果
			/// \param pImageData               视频数据
			/// \param datalength               视频数据长度
			/// \param width,height,xPos,yPos   图像位置
			/// \param frameFormat              视频数据格式，具体见video_capture头文件定义
			/// \prarm reference_time           采集到该帧的时间戳
			/// \param reference_time_scale     采集时间戳单位，毫秒10^3，微妙10^6，纳秒10^9
			virtual void OnSubViewTakeSnapShot(
				unsigned char *pImageData,
				int datalength,
				int width, int height, int xPos, int yPos,
				const AVE::VideoCaptureFormat& frameFormat,
				unsigned long long reference_time,
				unsigned int reference_time_scale) {}

            /// \breif 窗体数据采集错误
            /// \param nErrorCode 错误码见CaptureError定义
            virtual void OnWindowCaptureError(int nErrorCode) {}

            /// \breif 摄像头数据采集错误
            /// \param deviceId     摄像头设备ID
            /// \param reason       错误原因
            virtual void OnCameraCaptureError(const char *deviceId, const char* reason) {}
        };
    }
}