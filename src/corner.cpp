#include<iostream>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;
CVMat t;
int thres;
void callback(int, void*) {
	t.restore();
	t.draw_detected_corner(thres * 0.001);
	t.show("corner");
}

int main(int ac, char** av)
{
	t = imread("card2.jpg");
	t.scale(0.3,0.3);
	t.save();
	t.gray();
	t.filter(GAUSSIAN);
	t.edge();
	t.corner();
	t.restore();
	t.show("corner");
	createTrackbar("threshold", "corner", &thres, 200, callback);
	waitKey(0);
}

