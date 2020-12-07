#include "features.h"

namespace Features {

FeatureDetector::FeatureDetector() {
	// let it be configured using default settings
	detector = cv::SIFT::create();
}

std::vector<cv::KeyPoint> FeatureDetector::calculateKeyPoints(const cv::Mat& image) {
	std::vector<cv::KeyPoint> features;

	detector->detect(image, features);
	return features;
}

}
