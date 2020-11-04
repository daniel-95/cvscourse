#include <iostream>
#include <filesystem>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>

using namespace cv;

int main() {
	cv::VideoCapture car("20191119_1241_Cam_1_03_00.mp4");
	cv::Mat frame;

	if(!car.isOpened()) {
		std::cerr << "Couldn't open the file" << std::endl;
		return -1;
	}

	try {
		std::filesystem::create_directory("frames");
	} catch(std::exception& e) {
		std::cerr << e.what();
		return -1;
	}


	size_t count = 0;
	while(car.read(frame)) {
		cv::imshow("display", frame);

		if(count < 50) {
			cv::imwrite(std::string("./frames/frame") + std::to_string(count) + ".jpg", frame);
			count++;
		}

		cv::waitKey(1);
	}

	return 0;
}

