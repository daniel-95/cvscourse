#include "mainwindow.h"
#include "mask.h"
#include "features.h"
#include "track.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <string>
#include <vector>
#include <iostream>

void MainWindow::calculate(std::string fileName, std::string dirName, int nFrames, int nWinSize) {
	emit updateProgressBar(0);

	cv::VideoCapture cap(fileName);

	if(!cap.isOpened())
		throw LDBadFileException(fileName);

	int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
	size_t count = 0, pathsCount = 0;
	cv::Mat mFrame, mOut;

	// Mask setup
	auto pMask = std::make_unique<Mask::Mask>();

	// SIFT detector setup
	auto pSIFT = std::make_unique<Features::FeatureDetector>();

	// feature tracker setup, NFRAMES = 5, winSize = 11
	auto pTracker = std::make_unique<Track::FeatureTracker>(nFrames, nWinSize);

	while(cap.read(mFrame)) {
		QCoreApplication::processEvents();

		// draw the mask
		pMask->makeMask(mFrame);

		// handle the first frame
		if(pTracker->empty()) {
			// detect keypoints using SIFT
			std::vector<cv::KeyPoint> keypoints = pSIFT->calculateKeyPoints(mFrame);
			std::vector<cv::Point2f> vfKeypoints;

			for(auto p : keypoints)
				vfKeypoints.emplace_back(p.pt.x, p.pt.y);

			// init the tracker with it
			pTracker->init(vfKeypoints, mFrame);
			continue;
		}

		// if there are NFRAMES steps
		if(pTracker->ready()) {
			pathsCount++;
			// drawing paths
			auto steps = pTracker->getSteps();

			mOut = mFrame.clone();

			if(steps.size() > 0) {
				for(int j = 0; j < steps[0].size(); j++) {
					for(int i = 1; i < steps.size(); i++) {
						// yellow 1-pixel-wide line
						cv::line(mOut, steps[i-1][j], steps[i][j], cv::Scalar(0, 255, 255), 1);
					}

					// yellow circle with the radius of 5 pixels and 1-pixel-wide border on the final path point
					cv::circle(mOut, steps.back()[j], 5, cv::Scalar(0, 255, 255), 1);
				}
			}

			// drop the frame to a disk and show it
			if(1) {
				std::string maskedFilePath = dirName + "/frame_with_path" + std::to_string(count) + ".jpg";
				cv::imwrite(maskedFilePath, mOut);
			}

			cv::imshow("tracked paths", mOut);
			cv::waitKey(1);


			// initialize next path search
			std::vector<cv::KeyPoint> keypoints = pSIFT->calculateKeyPoints(mFrame);
			std::vector<cv::Point2f> vfKeypoints;

			for(auto p : keypoints)
				vfKeypoints.emplace_back(p.pt.x, p.pt.y);

			pTracker->init(vfKeypoints, mFrame);
		} else {
			pTracker->makeStep(mFrame);
		}

		count++;
		emit updateProgressBar(static_cast<int>(static_cast<double>(count) / frameCount * 100));
	}

	emit updateProgressBar(100);
}

