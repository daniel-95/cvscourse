#include "mask.h"

namespace Mask {

void makeMask(cv::Mat& image) {
	for(auto r : mask)
		cv::rectangle(image, r, cv::Scalar(0, 0, 0), cv::FILLED);
}

size_t removeMaskFeatures(std::vector<cv::KeyPoint>& features) {
	size_t oldSize = features.size();

	for(auto it = features.begin(); it != features.end(); ++it) {
		for(auto r : mask) {
			// if the feature is within one of the mask regions
			if(r.x <= it->pt.x && r.x + r.width >= it->pt.x && r.y <= it->pt.y && r.y + r.height >= it->pt.y) {
				it = features.erase(it);
				--it;
			}
		}
	}

	return oldSize - features.size();
}

}
