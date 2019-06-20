#include<iostream>
#include"option.h"
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	CMDoption co{
		{"file", "picture file", "Lenna.png"},
	};
	if(!co.args(ac, av)) return 0;
	CVMat t = imread(co.get<const char*>("file"));
	t.save();
	t.gray();
	t.edge();
	t.show();
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(t, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	t.restore();
	for(auto a : contours) for(auto b : a) {
		circle(t, b, 5, {0,0,255}, 2, 8, 0);
		t.show("corner");
		waitKey(1);
	}
	waitKey(0);
}

