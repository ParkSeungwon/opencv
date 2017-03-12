#include<cxcore.hpp>
#include<highgui.h>
#include<iostream>
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	VideoCapture cap(av[1]);
	Mat frame;
	int total_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int frame_rate = cap.get(CV_CAP_PROP_FPS);
	while(total_frame--) {
		cap >> frame;
		imshow("video", frame);
		if(waitKey(frame_rate) >= 0) break;
	}
}

