#include "mainwindow.h"
#include "mask.h"
#include "features.h"
#include "model.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

void MainWindow::calculate(std::string videoFileName, std::string dirName, std::string modelFileName, std::string modelMetaDataFile) {
	emit updateProgressBar(0);

	// open video file
 	cv::VideoCapture cap(videoFileName);

	if(!cap.isOpened())
		throw LDBadFileException(videoFileName);

	int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);

	// read model
	cv::Mat mModel = cv::imread(modelFileName, cv::IMREAD_COLOR);

	// read model metadata (polygon coordiantes)
	std::ifstream modelMetaFile;
	modelMetaFile.open(modelMetaDataFile);

	std::vector<cv::Point> polygon;
	double x, y;

	if(!modelMetaFile.is_open())
		throw LDBadFileException(modelMetaDataFile);

	while(modelMetaFile >> x >> y)
		polygon.emplace_back(x, y);

	modelMetaFile.close();

	int count = -1;
	cv::Mat mFrame, mOut;

	// Mask setup
	auto pMask = std::make_unique<Mask::Mask>();

	// SIFT detector setup
	auto pSIFT = std::make_unique<Features::FeatureDetector>();

	// Model setup
	auto model = Model::Model(mModel, polygon, pSIFT);

	while(cap.read(mFrame)) {
		QCoreApplication::processEvents();
		count++;

		if(count % 10 != 0)
			continue;

		// draw the mask
		pMask->makeMask(mFrame);

		// calculate SIFT
		std::vector<cv::KeyPoint> vKeyPoints;
		cv::Mat mDescriptors;
		pSIFT->calculateKeyPointsAndDescriptors(mFrame, vKeyPoints, mDescriptors);

		// match the model and draw the matches
		model.matchAndDraw(mFrame, vKeyPoints, mDescriptors, mOut);

		// log
		std::string maskedFilePath = dirName + "/match" + std::to_string(count) + ".jpg";
		cv::imwrite(maskedFilePath, mOut);
		cv::imshow("matched model", mOut);

		emit updateProgressBar(static_cast<int>(static_cast<double>(count) / frameCount * 100));
	}

	emit updateProgressBar(100);
}

