#include "model.h"
#include "features.h"

namespace Model {

static bool isLeftTurn(const cv::KeyPoint& p1, const cv::KeyPoint&p2, const cv::KeyPoint& p3) {
        return (p2.pt.x - p1.pt.x) * (p3.pt.y - p2.pt.y) - (p3.pt.x - p2.pt.x) * (p2.pt.y - p1.pt.y) < 0;
}

Model::Model(const cv::Mat& mImg, const std::vector<cv::Point>& vPolygon, const std::unique_ptr<Features::FeatureDetector>& pSIFT/*, type*/)
	: m_image(mImg), pMatcher(cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED)) {
	// build the convex hull for vPolygon
	// TODO: make m_grahamScan parametrized with the type

	std::vector<cv::KeyPoint> kpPolygon, vHull;

	for(auto p : vPolygon)
		kpPolygon.emplace_back(p, 1.f);

	m_grahamScan(kpPolygon, vHull);

	for(auto p : vHull)
		m_polygon.emplace_back(p.pt.x, p.pt.y);

	// SIFT for inner area
	cv::Mat mMask = cv::Mat::zeros(mImg.cols, mImg.rows, CV_8U);
	cv::fillConvexPoly(mMask, m_polygon, cv::Scalar(1));
	pSIFT->calculateKeyPointsAndDescriptors(mImg, m_keyPoints, mMask, m_descriptors);
}

void Model::m_grahamScan(std::vector<cv::KeyPoint>& vPoints, std::vector<cv::KeyPoint>& vHull) {
	if(vPoints.size() < 3) {
		vHull.clear();
		vHull.insert(vHull.end(), vPoints.begin(), vPoints.end());
		return;
	}

	// searching the element with the smallest y and leftmost one
	auto it = std::min_element(vPoints.begin(), vPoints.end(), [](const cv::KeyPoint& a, const cv::KeyPoint& b) {
		return a.pt.y < b.pt.y || a.pt.y == b.pt.y && a.pt.x < b.pt.x;
	});

	std::swap(*vPoints.begin(), *it);
	cv::KeyPoint first = vPoints[0];

	// sorting by polar angle
	std::sort(vPoints.begin() + 1, vPoints.end(), [first](const cv::KeyPoint& a, const cv::KeyPoint& b) {
		double det = (a.pt.x - first.pt.x) * (b.pt.y - first.pt.y) - (b.pt.x - first.pt.x) * (a.pt.y - first.pt.y);
		double l2a = (a.pt.x - first.pt.x) * (a.pt.x - first.pt.x) + (a.pt.y - first.pt.y) * (a.pt.y - first.pt.y);
		double l2b = (b.pt.x - first.pt.x) * (b.pt.x - first.pt.x) + (b.pt.y - first.pt.y) * (b.pt.y - first.pt.y);

		return det > 0 || det == 0 && l2a > l2b; // longest goes first in order to remove shortest afterwards in std::unique
	});

	// erasing collinear vectors keeping the longest one
	vPoints.erase(std::unique(vPoints.begin() + 1, vPoints.end(), [first](const cv::KeyPoint& a, const cv::KeyPoint& b) {
		return (a.pt.x - first.pt.x) * (b.pt.y - first.pt.y) - (b.pt.x - first.pt.x) * (a.pt.y - first.pt.y) == 0;
	}), vPoints.end());

	// Graham scan, assume that vPoints.size() >= 3
	vHull.push_back(vPoints[0]);
	vHull.push_back(vPoints[1]);
	vHull.push_back(vPoints[2]);

	for(auto it = vPoints.begin() + 3; it != vPoints.end(); ++it) {
		while(isLeftTurn(vHull[vHull.size() - 2], vHull[vHull.size() - 1], *it))
			vHull.pop_back();

		vHull.push_back(*it);
	}
}

void Model::match(const cv::Mat& mDescriptors, std::vector<cv::DMatch>& dmMatches) {
	std::vector<std::vector<cv::DMatch>> vKnnMatches;
	pMatcher->knnMatch(m_descriptors, mDescriptors, vKnnMatches, 2 );

	// copied from opencv examples
	//-- Filter matches using the Lowe's ratio test
	const float ratio_thresh = 0.7f;
	for (size_t i = 0; i < vKnnMatches.size(); i++) {
		if (vKnnMatches[i][0].distance < ratio_thresh * vKnnMatches[i][1].distance) {
			dmMatches.push_back(vKnnMatches[i][0]);
		}
	}
}

void Model::draw(const cv::Mat& mFrame, const std::vector<cv::KeyPoint>& vKeyPoints, const std::vector<cv::DMatch>& dmMatches, cv::Mat& mOut) {
	cv::drawMatches(m_image, m_keyPoints, mFrame, vKeyPoints, dmMatches, mOut, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
}

void Model::matchAndDraw(const cv::Mat& mFrame, const std::vector<cv::KeyPoint>& vKeyPoints, const cv::Mat& mDescriptors, cv::Mat& mOut) {
	std::vector<cv::DMatch> matches;
	match(mDescriptors, matches);
	draw(mFrame, vKeyPoints, matches, mOut);
}

}

