#include<iostream>
#include"cvmatrix.h"
#include"blender-32x32.xpm"
using namespace std;
using namespace cv;

int main()
{
	CVMat t = imread("IMG_0315.JPG");
	t.show("original");
	t.filter(SOBELX);
	t.show("sobelX");
	t.restore();
	t.filter(GAUSSIAN);
	t.show("gaussian");
	t.restore();
	t.filter(SOBELY);
	t.show("sobelY");
	t.restore();
	putText(t, "Lord Buddha", {100,100}, 0, 0.5, {255,0,0}, 2);

	Canny(t,t, 30,100);
	t.show("canny");
	t.restore();
	t.noise(10);
	t.show("noise");
	t.median(5);
	t.show("median");
	t.restore();
	t.gray();
	cout << t.channels() << endl;
	t.show("gray");
	t.filter(SOBELX);
	t.show("filgr");
	t.restore();

	CVMat t2 = Matrix<float>{{1,2},{2,1}};
	cout << t2.inv();

	VideoCapture cap{0};
	while(waitKey(30) == -1) {
		cap >> t;
		t.filter(SHARPEN);
		Canny(t, t, 90, 180);
//		flip(t,t,1);
		t.show("vidcap");
	}

	t.xpm(xpm);
	t.show("bl");
	waitKey(0);
}
