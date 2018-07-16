#pragma once

#include "video_capture.h"
#include "stdlib.h"
#include <windows.h>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <QDateTime>

//#include "ZegoVideoFilterWorkThread.h"

class VideoFilterGlue : public QObject, public AVE::VideoFilter, public AVE::VideoBufferPool{
	Q_OBJECT
public:
	VideoFilterGlue();
	virtual ~VideoFilterGlue();
	virtual void AllocateAndStart(Client* client) override;
	virtual void StopAndDeAllocate() override;
	virtual int DequeueInputBuffer(int width, int height, int stride) override;
	virtual void* GetInputBuffer(int index) override;
	virtual void QueueInputBuffer(int index, int width, int height, int stride, unsigned long long timestamp_100n) override;

	AVE::VideoBufferType SupportBufferType() {
		return AVE::BUFFER_TYPE_MEM;
	}

	void* GetInterface() {
		return (AVE::VideoBufferPool*)this;
	}

protected:
	void TimerStart();
	void TimerStop();
	void OnVideoTimer();
	void Sleep(int msec);
	static DWORD WINAPI thread_proc(PVOID pParam);

private:
	Client *client_;
	int width_;
	int height_;
	int stride_;

	HANDLE m_hVideoTimer = NULL;
	QTimer *m_pTimer;
	QThread *m_pThread;
	QMutex m_pMutex;
	//ZegoVideoFilterWorkThread *m_pThread;
	bool m_bExit = false;
	int m_nVideoTickPeriod = 10; // ms

	const static int MAX_FRAME = 3;
	const static int MAX_SIZE = 1920 * 1088 * 4 + 8; // iOS max cap size

	volatile long m_oPendingCount;

	struct {
		unsigned char frame[MAX_SIZE];
		int width;
		int height;
		unsigned long long timestamp_100n;
	} m_aBuffers[MAX_FRAME];

	int m_nReadPtr = 0;
	int m_nWritePtr = 0;
};