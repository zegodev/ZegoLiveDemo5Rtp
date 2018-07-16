#include "video_capture.h"
#include "ZegoVideoFilterDemo.h"

class VideoFilterFactoryGlue : public AVE::VideoFilterFactory {
public:
	VideoFilterFactoryGlue();
	virtual ~VideoFilterFactoryGlue();
	virtual AVE::VideoFilter* Create() override;
	virtual void Destroy(AVE::VideoFilter *vf) override;
};
