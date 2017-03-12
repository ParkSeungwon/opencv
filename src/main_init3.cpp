#include<iostream>
#include<cxcore.hpp>
#include<highgui.h>
#include"data/blender-32x32.xpm"
#include"data/logo.xpm"
#include"matrix.h"
using namespace cv;
using namespace std;
int value;
array<Matrix<unsigned char>, 4> read_xpm(const char** xpm);
void onMouse(int event, int x, int y, int flags, void* param) {
	switch(event) {
	case CV_EVENT_LBUTTONDOWN: 
		cout << "mouse left button at " << x << ',' <<y << endl; break;
	case CV_EVENT_RBUTTONDOWN: cout << "mouse right button" << endl; break;
	case CV_EVENT_MBUTTONDOWN: cout << "mouse middle button" << endl; break;
	case CV_EVENT_LBUTTONUP: cout << "mouse left button up" << endl; break;
	case CV_EVENT_MBUTTONUP: cout << "mouse middle up" << endl; break;
	case CV_EVENT_RBUTTONUP: cout << "mouse right up" << endl; break;
	}
}
Mat merge1, merge2;
void onTrackbar(int, void*);
int main()
{
	Matrix<int> m{{1,2,3},{4,5,6},{7,8,9}};
	Mat mat = m;
	cout << mat << endl;

	Mat mat2 = Mat::ones(10,5,CV_32S);
	Matrix<int> mm{mat2};
	cout << mm << endl;
	vector<Mat> v1, v2;
	for(auto& a : read_xpm(logo_xpm)) v1.push_back(a); 
	for(auto& a : read_xpm(xpm)) v2.push_back(a); 

	merge(v1, merge1);
	line(merge1, {50,50}, {100,10}, {0,0,255}, 8);
	putText(merge1, "Test tes", {100,100},0,0.5,{0,255,0}, 2);
	ellipse(merge1, {100,100}, Size{50,30},70,0,360,{255,0,0},-1);
	Rect rect{200,100,100,50};
	auto a = merge1(rect);
	putText(a, "Text", {0, 30},0,1,{0,255,255},8);
	imshow("관심", a);
	imshow("logo", merge1);
	createTrackbar("track event", "logo",&value, 255, onTrackbar);
	imwrite("lll.jpg", merge1);
	merge(v2, merge2);
	imshow("blender", merge2);
	cout << merge2.channels() << "channels" << merge2.depth() << "depth";
	setMouseCallback("logo", onMouse, 0);

//	Mat image = imread("IMG_0315.JPG");
	//Mat image2 = imread("src/blender-32x32.xpm");

//	namedWindow("가마쿠라 대불");
//	imshow("가마쿠라대불", image);
	//imshow("test", mat);
	waitKey(0);
}
void onTrackbar(int value, void*) {
	Mat tmp = merge1 + value - 127;
	imshow("logo", tmp);
}

