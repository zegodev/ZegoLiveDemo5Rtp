#include "ZegoVideoFilterFactoryDemo.h"

VideoFilterFactoryGlue::VideoFilterFactoryGlue() {
}

VideoFilterFactoryGlue::~VideoFilterFactoryGlue() {
}

AVE::VideoFilter* VideoFilterFactoryGlue::Create() {
	return new VideoFilterGlue();
}

void VideoFilterFactoryGlue::Destroy(AVE::VideoFilter *vc) {
	if (auto p = dynamic_cast<VideoFilterGlue*>(vc)) {
		delete p;
	}
}