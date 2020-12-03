#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core.hpp>

#include "features.h"

namespace Model {

class Model {
private:
	cv::Mat m_image;
	cv::Mat m_descriptors;
	std::vector<cv::Point> m_polygon;
	std::vector<cv::KeyPoint> m_keyPoints;
	std::vector<cv::KeyPoint> m_keyConvexHull;
	cv::Ptr<cv::DescriptorMatcher> pMatcher;

//	void m_dumpDebugInfo();
	void m_grahamScan(std::vector<cv::KeyPoint>& vPoints, std::vector<cv::KeyPoint>& vOut);
public:
	Model(const cv::Mat& mImg, const std::vector<cv::Point>& vPolygon, const std::unique_ptr<Features::FeatureDetector>& pSIFT/*, type*/);
	void match(const cv::Mat& mDescriptors, std::vector<cv::DMatch>& dmMatches);
	void draw(const cv::Mat& mFrame, const std::vector<cv::KeyPoint>& vKeyPoints, const std::vector<cv::DMatch>& dmMatches, cv::Mat& mOut); // cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
	void matchAndDraw(const cv::Mat& mFrame, const std::vector<cv::KeyPoint>& vKeyPoints, const cv::Mat& descriptors, cv::Mat& mOut);
};

}

#endif

