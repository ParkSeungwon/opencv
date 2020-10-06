#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void hue_bar(int value, void*) {}
	
int main()
{
	VideoCapture cap("IMG_0874.mp4");
	if(!cap.isOpened()) {
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(-1);
	}

	Mat frame;
	while(1) {
		cap >> frame;
		if(frame.empty()) break;
		imshow("view", frame);
		waitKey(28);
	}
}

