#include<algorithm>
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
	t.show("original");
	t.save();
	t.gray();
	t.filter(GAUSSIAN);
	t.edge();
	t.show();
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(t, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	t.restore();
	namedWindow("corner", WINDOW_NORMAL);
	auto it = max_element(contours.begin(), contours.end(),
			[](const vector<Point> &a, const vector<Point> &b) {
				return a.size() < b.size();
			}
		);
	Point2f xy[4] = {{1000,1000}, {0, 1000}, {1000, 0}, {0,0}};
	for(auto &[x, y] : *it) {
		if(x + y < xy[0].x + xy[0].y) xy[0] = {x, y};
		if(x - y > xy[1].x - xy[1].y) xy[1] = {x, y};
		if(y - x > xy[2].y - xy[2].x) xy[2] = {x, y};
		if(x + y > xy[3].x + xy[3].y) xy[3] = {x, y};
	}
	for(auto &[x, y] : xy) cout << x << ' ' << y << endl;
//	for(auto a : contours) {
//		for(auto b : a) circle(t, b, 5, {0,0,255}, 2, 8, 0);
//		t.show("corner");
//		resizeWindow("corner", 600, 400);
//	}
	t.get_business_card(xy);
	t.show("final");
	waitKey(0);
}

