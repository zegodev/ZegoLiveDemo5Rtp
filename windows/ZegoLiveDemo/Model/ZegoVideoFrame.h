#pragma once

#include <QSharedPointer>
#include <QImage>
#include <mutex>
#include <functional>
#include "video_capture.h"
#include <QDebug>
#include "ZegoLiveDemo.h"
#include <memory>

class QZegoVideoFrame
{
public:
	QZegoVideoFrame(QImage& frame, AVE::VideoCaptureFormat format)
    {
        frame_ = frame.copy();  // * retain image data
        format_ = format;
    }

    QZegoVideoFrame(const unsigned char* data, int len, AVE::VideoCaptureFormat format)
        : data_len_(len), format_(format)
    {
        
		data_ = new unsigned char[len];
        memcpy(data_, data, len);
          
        frame_ = QImage(data_, format_.width, format_.height, format_.strides[0], QImage::Format_RGB32);
    }

	~QZegoVideoFrame() 
    {
        if (data_) {
			delete[] data_;
			data_ = nullptr;
        }        
    }

    const unsigned char* getData()
    {
        if (data_) {
            return data_;
        } else {
            return frame_.constBits();
        }
    }

	const QImage& getCurrentFrame()
    {   
        return frame_;
    }

	const AVE::VideoCaptureFormat &getCurrentFormat()
    {
        return format_;
    }

	int frameLength()
    {
        return format_.strides[0] * format_.height;
    }

private:
	QImage frame_;

    unsigned char* data_ = nullptr;
    int data_len_ = 0;
	AVE::VideoCaptureFormat format_;
};

//using VideoFrame = QSharedPointer < QZegoVideoFrame >;
using VideoFrame = std::shared_ptr< QZegoVideoFrame >;
using OnVideoFrameDelegate = std::function<void(VideoFrame)>;
