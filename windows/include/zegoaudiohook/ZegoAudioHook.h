#pragma once

#define ZEGO_API  __declspec(dllexport)

//此接口实现Hook音乐软件，从音乐软件中获取当前播放的音频数据 功能
//如果需要把获取的音频数据通过即构SDK混音推流，需要调用即构SDK的EnableAux(true)
//在即构SDK的回调OnAuxCallback中调用GetAUXData获取音频数据后，传递给AuxCallback

namespace ZEGO
{
	namespace AUDIOHOOK
	{
		/*
		初始化音频Hook模块

		@discussion 接口没有保证线程安全，
					需要调用方确保在同一线程调用
					InitAuidoHook/UnInitAudioHook,
					StartAudioHook,
					StartAudioRecord/StopAudioRecord

					只支持Hook 32位音乐软件
		*/
		ZEGO_API void InitAuidoHook();

		/*
		反初始化音频Hook模块
		*/
		ZEGO_API void UnInitAudioHook();

		/*
		启动音频Hook

		@param pszAppFilePath    Hook的目标进程路径，如kugo的安装路径
		@param pszInjectDllPath  注入的ZegoMusicAudio.dll的路径

		@discussion 如果目标进程已经存在，Hook会失败
		*/
		ZEGO_API bool StartAudioHook(const char *pszAppFilePath, const char *pszInjectDllPath);

		/*
		开始获取音频数据
		*/
		ZEGO_API bool StartAudioRecord();

		/*
		停止获取音频数据
		*/
		ZEGO_API void StopAudioRecord();
		
		/*
		获取音频数据

		@param pData		数据存储地址
		@param pDataLen		数据长度地址
		@param pSampleRate  数据采样率地址
		@param pNumChannels 声道地址

		@discussion 配合即构SDK使用时，调用SDK的EnableAux(true)接口，在OnAuxCallback中调用此函数获取音频数据
		*/
		ZEGO_API void GetAUXData(unsigned char *pData, int *pDataLen, int *pSampleRate, int *pNumChannels);
	}
}