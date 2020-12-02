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
	std::vector<cv::KeyPoint> calculateKeyPoints(const cv::Mat& image);
};

}
#endif
