#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

CVMat m;
int canny=200, center=100, minr=0, maxr=0;

static void on_trackbar(int, void*) {
	m.gray();
	m.detect_circle(canny, center, minr, maxr);//150, 20, 20, 200);
	m.restore();
	m.draw_detected_circle({0, 255, 0});
	m.show("Circle");
}

int main()
{
	m = imread("/home/zeta/MEGA/Project/wood/source.jpeg");
	m.scale(0.3, 0.3);
	m.show("Circle");
	waitKey();
	m.gray();
	m.edge();
//	m.save();
//	void detect_circle(int canny_threshold=200, int center_threshold=100,//gray->circ 
//			int min_radius=0, int max_radius=0);//gradient를 보므로 edge로 하면 안됨.
//	createTrackbar("canny", "Circle", &canny, 400, on_trackbar);
//	createTrackbar("center", "Circle", &center, 200, on_trackbar);
//	createTrackbar("minr", "Circle", &minr, 100, on_trackbar);
//	createTrackbar("maxr", "Circle", &maxr, 300, on_trackbar);
//	on_trackbar(0, nullptr);
//	waitKey(0);
//	m.restore();
//	m.draw_detected_circle({0, 255, 0});
	m.show("Circle");
	waitKey(0);
}
