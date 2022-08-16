#include<iostream>
#include"option.h"
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	CMDoption co{
		{"input", "input image file", "cap3.jpg"},
		{"area", "minimal area", 0},
		{"thickness", "line thickness", 1},
		{"max points", "max points of contour", 10}
	};
	if(!co.args(ac, av)) return 0;
	CVMat t = imread(co.get<const char*>("input"));
	t.save();
	t.gray();
	//t.detect_circle();
	t.filter(GAUSSIAN);
	t.edge();
	t.detect_contours();
	t.restore();
	//t.draw_detected_circle();
	t.draw_detected_contours(co.get<int>("area"), co.get<int>("max points"), co.get<int>("thickness"));
	t.show();
	waitKey(0);
}


