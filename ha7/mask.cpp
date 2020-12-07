#include "mask.h"

namespace Mask {

void Mask::makeMask(cv::Mat& image) {
	for(auto r : m_mask)
		cv::rectangle(image, r, cv::Scalar(0, 0, 0), cv::FILLED);
}

size_t Mask::removeMaskFeatures(std::vector<cv::KeyPoint>& features) {
	size_t oldSize = features.size();

	auto eraseIt = std::remove_if(features.begin(), features.end(), [this] (const cv::KeyPoint& f) {
		for(auto r : m_mask)
			if(r.x <= f.pt.x
			&& r.x + r.width >= f.pt.x
			&& r.y <= f.pt.y
			&& r.y + r.height >= f.pt.y)
				return true;

		return false;
	});

	features.erase(eraseIt, features.end());

	return oldSize - features.size();
}

}
