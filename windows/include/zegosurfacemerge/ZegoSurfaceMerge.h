#pragma once

#include "ZegoSurfaceMergeDefine.h"
#include "ZegoSurfaceMergeCallback.h"
#include <vector>

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifdef WIN32
#ifdef ZEGO_EXPORTS
#define ZEGO_API __declspec(dllexport)
#else
#define ZEGO_API __declspec(dllimport)
#endif
#else
#define ZEGO_API __attribute__((visibility("default")))
#endif

namespace ZEGO
{
    namespace SurfaceMerge
    {
        /// \brief 初始化视频混合模块,非线程安全，与UnInit配对使用
        /// \note 必须在framework InitSDK前调用
        ZEGO_API void Init();

        /// \brief 反初始化视频混合模块，非线程安全，与Init配对使用
        ZEGO_API void UnInit();
        
        /// \brief 设置回调接口
        /// \param[in] pCallback 回调接口实例
        ZEGO_API void SetMergeCallback(IZegoSurfaceMergeCallback *pCallback);

        /// \brief 设置混合视频的大小
        /// \param[in] surfaceWidth  宽度
        /// \param[in] surfaceHeight 高度
        ZEGO_API void SetSurfaceSize(int surfaceWidth, int surfaceHeight);

        /// \brief 设置混合视频后要渲染到的窗口
        /// \param[in] renderView 渲染窗口
        ZEGO_API void SetRenderView(void *renderView);

        /// \brief 更新视频混合信息
        /// \param[in] itemList  要混合的窗体(摄像头)的相关信息列表
        /// \param[in] itemCount 视频混合输入源个数
        /// \note 混合视频的层级关系由itemList列表的先后顺序决定。
        /// \note 在列表中越靠前，混合视频的层级越前
        ZEGO_API bool UpdateSurface(ZegoCaptureItem *itemList, unsigned int itemCount);

        /// \brief 设置采集数据的帧率
        /// \param[in] nFPS 有效范围5~30，默认为15
        ZEGO_API void SetFPS(int nFPS);

        /// \brief 设置是否显示光标
        /// \param[in] bVisible 是否显示光标
        ZEGO_API void SetCursorVisible(bool bVisible);

        /// \brief 设置是否显示鼠标点击动画
        /// \param[in] bEnabled 是否显示鼠标点击动画
        ZEGO_API void EnableClickAnimation(bool bEnabled);

        /// \brief 同步枚举屏幕列表，包括屏幕名，是否主屏
        /// \param[out] uCount 屏幕数量
        /// \return 屏幕列表首地址，需配对调用FreeScreenList释放
        ZEGO_API ZEGO::SurfaceMerge::ScreenItem* EnumScreenList(unsigned int& uCount);

        /// \brief 同步释放枚举到的屏幕列表
        /// \param[in] pScreenList 枚举到的屏幕列表首地址
        ZEGO_API void FreeScreenList(ZEGO::SurfaceMerge::ScreenItem* pScreenList);

        /// \brief 同步枚举窗口列表，包括窗口标题、窗口对应可执行文件名
        /// \param[out] uCount 窗口数量
        /// \param[in] bIncludeIconic 枚举时是否包括最小化的窗口
        /// \return 窗口列表首地址，需配对调用FreeWindowList释放
        ZEGO_API ZEGO::SurfaceMerge::WindowItem* EnumWindowList(unsigned int& uCount, bool bIncludeIconic);

        /// \brief 同步释放枚举到的窗口列表
        /// \param[in] pWindowList 枚举到的窗口列表首地址
        ZEGO_API void FreeWindowList(ZEGO::SurfaceMerge::WindowItem* pWindowList);

		/// \brief 截取子窗体图像
		/// \param[in] nViewIndex 子窗体图像的索引，与itemList一致
		ZEGO_API bool TakeSubViewSnapShot(int nViewIndex);
    }
}