#include<cxcore.hpp>
#include<highgui.h>
#include<iostream>
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	VideoCapture vid(0);
	VideoWriter wr;
	int w = vid.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
	wr.open("wr.avi", CV_FOURCC('D','I','V','4'), 30, Size{w,h});
	Mat frame;
	namedWindow("other");
	while(waitKey(10) == -1) {//wait for 10ms, no input during 10ms then return -1
		vid >> frame;
		wr << frame;
		imshow("video", frame);
	}
}

