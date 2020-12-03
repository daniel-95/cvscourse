#include "features.h"

namespace Features {

FeatureDetector::FeatureDetector() {
	// let it be configured using default settings
	detector = cv::SIFT::create();
}

void FeatureDetector::calculateKeyPoints(const cv::Mat& image, std::vector<cv::KeyPoint>& features) {
	detector->detect(image, features);
}

void FeatureDetector::calculateKeyPoints(const cv::Mat& image, std::vector<cv::KeyPoint>& features, const cv::Mat& mask) {
	detector->detect(image, features, mask);
}

void FeatureDetector::calculateKeyPointsAndDescriptors(const cv::Mat& image, std::vector<cv::KeyPoint>& features, cv::Mat& descriptors) {
	detector->detectAndCompute(image, cv::noArray(), features, descriptors);
}

void FeatureDetector::calculateKeyPointsAndDescriptors(const cv::Mat& image, std::vector<cv::KeyPoint>& features, const cv::Mat& mask, cv::Mat& descriptors) {
	detector->detectAndCompute(image, mask, features, descriptors);
}


}
