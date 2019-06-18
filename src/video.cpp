#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void hue_bar(int value, void*) {}
	
int main()
{
	VideoCapture cap(0);
	VideoWriter writer;
	if(!cap.isOpened()) {
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(-1);
	}

	int w = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	//cout << cap.get(CV_CAP_PROP_EXPOSURE) << endl;
	cout << cap.get(CV_CAP_PROP_BRIGHTNESS) << endl;

	writer.open("1.avi", CV_FOURCC('D','I','V','4'), 30, Size{w,h});
	if(!writer.isOpened()) {
		cout << "카메라 write error 연결되지 않았습니다." << endl;
		exit(-1);
	}
	Mat frame;
	int c = 0;
	int hue = cap.get(CV_CAP_PROP_HUE);
	namedWindow("camera view");
	createTrackbar( "hue bar","camera view", &hue, 50, hue_bar);
	while(1) {
//		cap.set(CV_CAP_PROP_HUE, hue);
		cap >> frame;
		putText(frame, to_string(hue),{300,200}, 0,1,{255,0,0});
		frame.at<unsigned char>(100,100,2) = 20;
		writer << frame;
		imshow("camera view", frame);
		if(waitKey(30) >= 0) break;
	}
}

