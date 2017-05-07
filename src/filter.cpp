//#include<cxcore.hpp>
#include<highgui.h>
#include<cxcore.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
//	CVMat t = imread("IMG_0315.JPG");
//	t.filter(SHARPEN);
//	t.show("sharpen");
//	t.restore();
//	t.filter(BLUR);
//	putText(t, "Lord Buddha", {100,100}, 0, 0.5, {255,0,0}, 2);
//	t.show("blur");
//
//	Sobel(t,t, CV_32F, 1,0,3);
//	t.show("sobel");
//	t.restore();
//	Sobel(t,t, CV_32F, 0,1,3);
//	t.show("soble2");
//	t.restore();
//	Canny(t,t, 30,100);
//	t.show("canny");
//	t.restore();
//	Laplacian(t,t, 3);
//	t.show("lap");
//	t.restore();
//
//	CVMat t2 = Matrix<float>{{1,2},{2,1}};
//	cout << t2.inv();
//
//	namedWindow("vidcap");
	Mat m;
	VideoCapture v{0};
	if(!v.isOpened()) {
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(-1);
	}
	while(waitKey(0) == -1) {
		v >> m;
		imshow("vidcap", m);
	}
}
