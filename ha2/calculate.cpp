#include "mainwindow.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <QFile>

void MainWindow::calculate(std::string fileName, std::string dirName, double rho, double theta, int threshold) {
    emit updateProgressBar(0);

    cv::VideoCapture cap(fileName);
    
    if(!cap.isOpened())
        throw LDBadFileException(fileName);

    int frameCount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    int count = 0;

    cv::Mat mFrame, mGrayed, mEdges, mLined;

    std::string logPath = dirName + "/hough_" + std::to_string(rho) + "_" + std::to_string(theta) + ".log";
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
        cv::Canny(mGrayed, mEdges, 50, 150, 3);

        // save edges to file
        std::string filePath = dirName + "/frame" + std::to_string(count) + ".jpg";
        cv::imwrite(filePath, mEdges);

        // apply Hough transform to the edges
        std::vector<cv::Vec2f> houghLines;
        cv::HoughLines(mEdges, houghLines, rho, theta*CV_PI/180, threshold);
        
        // write to a log: frameNumber | numOfLines | rho | theta
        logger << count << "\t" << houghLines.size() << "\t" << rho << "\t" << theta << "\n";

        // imshow the lines over the source (coloured image)
        mLined = mFrame.clone();

        for(auto line : houghLines) {
            float r = line[0], t = line[1];
            double a = cos(t), b = sin(t);
            double x0 = a*r, y0 = b*r;

            cv::Point p1, p2;
            p1.x = cvRound(x0 + 2000*(-b));
            p1.y = cvRound(y0 + 2000*a);
            p2.x = cvRound(x0 - 2000*(-b));
            p2.y = cvRound(y0 - 2000*a);

            cv::line(mLined, p1, p2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
        }

        // write lines over the source to a file
        std::string linedFilePath = dirName + "/linedframe" + std::to_string(count) + ".jpg";
        cv::imshow("lined video", mLined);
        cv::imwrite(linedFilePath, mLined);
        cv::waitKey(1);

        emit updateProgressBar(static_cast<int>(static_cast<double>(count) / frameCount * 100));
    }

    emit updateProgressBar(100);
}

