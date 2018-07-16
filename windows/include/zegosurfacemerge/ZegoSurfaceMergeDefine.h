#pragma once

namespace ZEGO
{
    namespace SurfaceMerge
    {
        struct ZegoRect
        {
            int xPos;
            int yPos;
            int width;
            int height;
        };

        enum CaptureError
        {
            Unexpected = 1,
            TargetUnspecified = 2,		// 采集目标未指定
            TargetInvalid = 3, 			// 采集目标失效，比如显示器被拔掉、窗口被关闭
            CaptureFunctionFailed = 4,
        };

        struct ScreenItem
        {
            char szName[32];
            bool bPrimary;
        };

        struct WindowItem
        {
            void* winId;
            char szTitle[256];
            char szExe[256];
        };

        enum CaptureType
        {
            Camera = 1,                      //摄像头
            Window = 2,                      //窗体
            Screen = 3,                      //屏幕
            ScreenRect = 4                   //屏幕区域
        };

        struct ZegoCaptureItem
        {
            CaptureType captureType;         //采集源类型

            union
            {
                char deviceId[256];          //摄像头设备ID
                void *hWnd;                  //窗体句柄
                char screenName[256];        //屏幕名称
                ZegoRect screenRect;         //屏幕区域
            } captureSource;
           
            ZegoRect position;               //混合视频位置
        };
    }
}
