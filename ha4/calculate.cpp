#include "mainwindow.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <QFile>

void MainWindow::calculate(std::string fileName, std::string dirName, double rho, double theta, int threshold, int canny1st, int canny2nd) {
    emit updateProgressBar(0);

    cv::VideoCapture cap(fileName);
    
    if(!cap.isOpened())
        throw LDBadFileException(fileName);

    int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    int count = 0;

    cv::Mat mFrame, mGrayed, mEdges, mLined;

    std::string logPath = dirName + "/houghp_" + std::to_string(rho) + "_" + std::to_string(theta) + "_" + std::to_string(threshold) + ".log";
    QFile houghLog(logPath.c_str());

    if(!houghLog.open(QIODevice::WriteOnly | QIODevice::Text))
        throw LDBadFileException(logPath);

    QTextStream logger(&houghLog);

    while(cap.read(mFrame)) {
        count++;
        if(count % 10 != 0)
            continue;

        cv::cvtColor(mFrame, mGrayed, cv::COLOR_RGB2GRAY);

        // predefined parameters according to the home assignment
        cv::Canny(mGrayed, mEdges, canny1st, canny2nd, 3);

        // save edges to file
        std::string filePath = dirName + "/frame" + std::to_string(count) + ".jpg";
        cv::imwrite(filePath, mEdges);

        // apply Hough transform to the edges
        std::vector<cv::Vec4i> houghLines;
        cv::HoughLinesP(mEdges, houghLines, rho, theta*CV_PI/180, threshold, 25, 10); // distance is 25, max gap between the points to be counted is 10
        
        // write to a log: frameNumber | numOfLines | rho | theta
        logger << count << "\t" << houghLines.size() << "\t" << rho << "\t" << theta << "\t" << threshold << "\n";

        // imshow the lines over the source (coloured image)
        mLined = mFrame.clone();

        for(auto line : houghLines) {
            cv::line(mLined, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        }

        // write lines over the source to a file
        std::string linedFilePath = dirName + "/linedframeP" + std::to_string(count) + ".jpg";
        cv::imshow("lined video", mLined);
        cv::imwrite(linedFilePath, mLined);
        cv::waitKey(1);

        emit updateProgressBar(static_cast<int>(static_cast<double>(count) / frameCount * 100));
    }

    emit updateProgressBar(100);
}

