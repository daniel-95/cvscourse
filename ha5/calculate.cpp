#include "mainwindow.h"
#include "mask.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <QFile>

void MainWindow::calculate(std::string fileName, std::string dirName) {
	emit updateProgressBar(0);

	cv::VideoCapture cap(fileName);

	if(!cap.isOpened())
		throw LDBadFileException(fileName);

	int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
	int count = 0;

	cv::Mat mFrame, mGrayed, mEdges, mOut;

	std::string logPath = dirName + "/SIFT.log";
	QFile SIFTLog(logPath.c_str());

	if(!SIFTLog.open(QIODevice::WriteOnly | QIODevice::Text))
		throw LDBadFileException(logPath);

	QTextStream logger(&SIFTLog);

	// SIFT detector setup
	std::vector<cv::KeyPoint> features;
	cv::Ptr<cv::SIFT> detector = cv::SIFT::create();

	while(cap.read(mFrame)) {
		features.clear();
		QCoreApplication::processEvents();

		count++;
		if(count % 10 != 0)
			continue;

		// draw the mask
		Mask::makeMask(mFrame);

		// detect the features and draw them
		size_t numOfFeaturesDetected, numOfFeaturesFiltered;

		detector->detect(mFrame, features);
		numOfFeaturesDetected = features.size();
		numOfFeaturesFiltered = Mask::removeMaskFeatures(features);
		cv::drawKeypoints(mFrame, features, mOut, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		// write to a log: frame number | number of features detected | number of features detected & filtered
		logger << count << "\t" << numOfFeaturesDetected << "\t" << numOfFeaturesFiltered << "\n";

		// write the features over the frame, store it to a file and display it
		std::string maskedFilePath = dirName + "/maskedframe" + std::to_string(count) + ".jpg";
		cv::imshow("masked video", mOut);
		cv::imwrite(maskedFilePath, mOut);
		cv::waitKey(1);

		emit updateProgressBar(static_cast<int>(static_cast<double>(count) / frameCount * 100));
	}

	SIFTLog.close();
	emit updateProgressBar(100);
}

