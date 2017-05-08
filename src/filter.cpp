#include<iostream>
#include"cvmatrix.h"
#include"blender-32x32.xpm"
using namespace std;
using namespace cv;

int main()
{
	CVMat t = imread("IMG_0315.JPG");
	t.show("original");
	t.save();
//	t.filter(SOBELX);
//	t.show("sobelX");
//	t.restore();
//	t.show("o2");
//	t.filter(SOBELY);
//	t.show("sobelY");
//	t.restore();
//	t.show("o");
//	putText(t, "Lord Buddha", {100,100}, 0, 0.5, {255,0,0}, 2);
//	t.show("sobel");
//	t.restore();

//	Sobel(t,t, CV_32F, 1,0,3);
//	t.show("sobel");
//	t.restore();
//	Sobel(t,t, CV_32F, 0,1,3);
//	t.show("soble2");
//	t.restore();
//	Canny(t,t, 30,100);
//	t.show("canny");
//	t.restore();
	t.noise(10);
	t.show("noise");
//	t.restore();
//	t.filter(getGaussianKernel(9, 3, CV_32F));//aperture odd, sigma
//	t.show("gaussian blur");
	t.median(5);
	t.show("median");
	t.restore();
	t.show("0");

	CVMat t2 = Matrix<float>{{1,2},{2,1}};
	cout << t2.inv();

	VideoCapture cap{0};
	while(waitKey(30) == -1) {
		cap >> t;
		t.filter(SHARPEN);
		flip(t,t,1);
		t.show("vidcap");
	}

	t.xpm(xpm);
	t.gray();
	t.show("bl");
	waitKey(0);
}
