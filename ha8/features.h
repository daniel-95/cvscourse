#ifndef __FEATURES_H__
#define __FEATURES_H__

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>

namespace Features {

class FeatureDetector {
private:
	cv::Ptr<cv::SIFT> detector;
public:
	FeatureDetector();
	void calculateKeyPoints(const cv::Mat& image, std::vector<cv::KeyPoint>& vOut);
	void calculateKeyPoints(const cv::Mat& image, std::vector<cv::KeyPoint>& vOut, const cv::Mat& mask);
	void calculateKeyPointsAndDescriptors(const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors);
	void calculateKeyPointsAndDescriptors(const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask, cv::Mat& descriptors);
};

}
#endif
