#include <opencv2/opencv.hpp>

// One (and only one) of your C++ files must define CVUI_IMPLEMENTATION
// before the inclusion of cvui.h to ensure its implementaiton is compiled.
#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "CVUI Hello World!"

int main(int argc, const char *argv[])
{
	// Create a frame where components will be rendered to.
	cv::Mat frame = cv::Mat(200, 500, CV_8UC3);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WINDOW_NAME);

	while (true) {
		// Fill the frame with a nice color
		frame = cv::Scalar(49, 52, 49);

		// Render UI components to the frame
		cvui::text(frame, 110, 80, "Hello, world!");
		cvui::text(frame, 110, 120, "cvui is awesome!");

		// Update cvui stuff and show everything on the screen
		cvui::imshow(WINDOW_NAME, frame);

		int x, y, w, h;
		//cv::getWindowImageRect(WINDOW_NAME, x, y, w, h);
		if (char c = cv::waitKey(20); c == 'q') break;
		else if(c == 'd') cv::moveWindow(WINDOW_NAME, 300, 300);
	}

	return 0;
}
