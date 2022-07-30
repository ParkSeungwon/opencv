#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void hue_bar(int value, void*) {}
	
int main(int ac, char** av)
{
	VideoCapture cap(av[1]);
	if(!cap.isOpened()) {
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(-1);
	}

	Mat frame;
	Rect r1{stoi(av[2]), stoi(av[3]), 70, 70};
	Rect r2{stoi(av[2]) + 70, stoi(av[3]), 70, 70};
	Size S = Size((int) cap.get(CAP_PROP_FRAME_WIDTH),    //Acquire input size
              (int) cap.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter out("out.mp4", static_cast<int>(cap.get(CAP_PROP_FOURCC)), 
				cap.get(CAP_PROP_FPS), S, true);
	while(1) {
		cap >> frame;
		if(frame.empty()) break;
		frame(r1).copyTo(frame(r2));
		out << frame;
		imshow("view", frame);
		waitKey(28);
	}
}

