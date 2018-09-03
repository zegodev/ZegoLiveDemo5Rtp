#include "ZegoVideoFilterDemo.h"
#include <QDebug>

VideoFilterGlue::VideoFilterGlue() : width_(0), height_(0), stride_(0)
{

}

VideoFilterGlue::~VideoFilterGlue()
{
	//delete m_pThread;
}

void VideoFilterGlue::AllocateAndStart(Client* client) {
	client_ = client;
	m_oPendingCount = 0;
	m_nWritePtr = 0;
	m_nReadPtr = 0;
	m_bExit = false;

	//LPDWORD tid = 0;
	//m_hVideoTimer = CreateThread(0, 0, &VideoFilterGlue::thread_proc, this, 0, tid);

	m_pThread = new QThread;
	m_pTimer = new QTimer;
	
	m_pTimer->moveToThread(m_pThread);
	
	m_pTimer->setInterval(10);
	connect(m_pThread, SIGNAL(started()), m_pTimer, SLOT(start()));
	connect(m_pThread, SIGNAL(finished()), m_pTimer, SLOT(stop()));

	connect(m_pTimer, &QTimer::timeout, this, &VideoFilterGlue::OnVideoTimer, Qt::DirectConnection);

	m_pThread->start();
}

void VideoFilterGlue::StopAndDeAllocate() {
	m_bExit = true;
	/*if (m_pTimer) {
		m_pTimer->moveToThread(m_pThread);
		connect(m_pThread, &QThread::finished, this, &VideoFilterGlue::TimerStop, Qt::DirectConnection);
		
		m_pThread->quit();
		m_pThread->wait();
		//WaitForSingleObject(m_hVideoTimer, INFINITE);
		//CloseHandle(m_hVideoTimer);
		//m_hVideoTimer = NULL;
    }*/
	
	//WaitForSingleObject(m_hVideoTimer, INFINITE);
	//CloseHandle(m_hVideoTimer);
	//m_hVideoTimer = NULL;

	if (m_pThread->isRunning())
	{
		m_pThread->quit();
		m_pThread->wait();
	}

	delete m_pThread;
	m_pThread = nullptr;

	delete m_pTimer;
	m_pTimer = nullptr;

	client_->Destroy();
	client_ = NULL;
}

int VideoFilterGlue::DequeueInputBuffer(int width, int height, int stride) {

	if (m_oPendingCount >= MAX_FRAME) {
		return -1;
	}
	return m_nWritePtr;
}

void* VideoFilterGlue::GetInputBuffer(int index) {

	return m_aBuffers[m_nWritePtr].frame;
}

void VideoFilterGlue::QueueInputBuffer(int index, int width, int height, int stride, unsigned long long timestamp_100n) {

	if (m_nWritePtr != index) {
		return;
	}

	m_aBuffers[index].width = width;
	m_aBuffers[index].height = height;
	m_aBuffers[index].timestamp_100n = timestamp_100n;

	m_nWritePtr = (m_nWritePtr + 1) % MAX_FRAME;

	m_pMutex.lock();
	if (m_oPendingCount >= 0)
		m_oPendingCount++;
	m_pMutex.unlock();
	//InterlockedIncrement(&m_oPendingCount);
	
}

/*DWORD WINAPI VideoFilterGlue::thread_proc(PVOID pParam)
{
	VideoFilterGlue *pThis = (VideoFilterGlue *)pParam;
	pThis->OnVideoTimer();
	return 0;
}*/

void VideoFilterGlue::TimerStart()
{
	m_pTimer->start();
}

void VideoFilterGlue::TimerStop()
{
	m_pTimer->stop();
	m_pTimer->deleteLater();
}

void VideoFilterGlue::Sleep(int msec)
{
	
}

void VideoFilterGlue::OnVideoTimer() {
	while (!m_bExit) {
		while (m_oPendingCount > 0) {
			VideoBufferPool* pool = (VideoBufferPool*)client_->GetInterface();

			int index = pool->DequeueInputBuffer(m_aBuffers[m_nReadPtr].width, m_aBuffers[m_nReadPtr].height, m_aBuffers[m_nReadPtr].width * 4);

			if (index >= 0) {
				unsigned char* src = m_aBuffers[m_nReadPtr].frame;
				unsigned char* dst = (unsigned char*)pool->GetInputBuffer(index);

				for (int i = 0; i < m_aBuffers[m_nReadPtr].height; i++) {
					for (int j = 0; j < m_aBuffers[m_nReadPtr].width; j++, src += 4, dst += 4) {
						int grey = (*src * 38 + *(src + 1) * 75 + *(src + 2) * 15) >> 7;
						*dst = grey;
						*(dst + 1) = grey;
						*(dst + 2) = grey;
					}
				}

				pool->QueueInputBuffer(index, m_aBuffers[m_nReadPtr].width, m_aBuffers[m_nReadPtr].height, m_aBuffers[m_nReadPtr].width * 4, m_aBuffers[m_nReadPtr].timestamp_100n);

				m_nReadPtr = (m_nReadPtr + 1) % MAX_FRAME;
				m_pMutex.lock();
				if (m_oPendingCount > 0)
					m_oPendingCount--;
				m_pMutex.unlock();
				//InterlockedDecrement(&m_oPendingCount);
			}
			else {
				break;
			}
		}
		//Sleep(m_nVideoTickPeriod);
		
	}
	
	return;
}