#include<algorithm>
#include<iostream>
#include<regex>
#include"option.h"
#include"cvmatrix.h"
#include<opencv2/text/ocr.hpp>
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
//	t.save();
//	t.gray();
//	t.filter(GAUSSIAN);
//	t.edge();
//	t.show();
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierachy;
//	findContours(t, contours, hierachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//	t.restore();
//	namedWindow("corner", WINDOW_NORMAL);
//	auto it = max_element(contours.begin(), contours.end(),
//			[](const vector<Point> &a, const vector<Point> &b) {
//				return a.size() < b.size();
//			}
//		);
//	Point2f xy[4] = {{9000,9000}, {0, 1000}, {1000, 0}, {0,0}};
//	for(auto &[x, y] : *it) {
//		if(x + y < xy[0].x + xy[0].y) xy[0] = {x, y};
//		if(x - y > xy[1].x - xy[1].y) xy[1] = {x, y};
//		if(y - x > xy[2].y - xy[2].x) xy[2] = {x, y};
//		if(x + y > xy[3].x + xy[3].y) xy[3] = {x, y};
//	}
//	for(auto &[x, y] : xy) cout << x << ' ' << y << endl;
//	for(auto a : contours) {
//		for(auto b : a) circle(t, b, 5, {0,0,255}, 2, 8, 0);
//		t.show("corner");
//		resizeWindow("corner", 600, 400);
//	}

	auto v = t.get_points(4);
	vector<float> x, y;
	Point2f xy[4] = {{9000,9000}, {0, 1000}, {1000, 0}, {0,0}};
	for(auto &[x, y] : v) {
		if(x + y < xy[0].x + xy[0].y) xy[0] = {x, y};
		if(x - y > xy[1].x - xy[1].y) xy[1] = {x, y};
		if(y - x > xy[2].y - xy[2].x) xy[2] = {x, y};
		if(x + y > xy[3].x + xy[3].y) xy[3] = {x, y};
	}
	for(int i=0; i<v.size(); i++) {
		x.push_back(v[i].x);
		y.push_back(v[i].y);
	}

	t.save();
	t.polyline(x, y, {255, 0, 0});
	t.show("original");
	t.restore();
	const int width = 630, height = 360;
	Point2f dst[4] = {{0,0}, {width-1, 0}, {0,height-1}, {width-1, height-1}};
	t.transform4(xy, dst, {width, height});//{420, 240});
	t.show("final");
	
	auto a = cv::text::OCRTesseract::create(NULL, "eng+kor");
	string s;
	vector<Rect> vr; vector<string> vs; vector<float> vf;
	a->run(t, s, &vr, &vs, &vf);
	stringstream ss; ss << s;
	while(getline(ss, s)) if(s != "") vs.push_back(s);
	smatch m;
	regex e{R"(\S+@\S+\.\S?)"};
	for(auto a : vs) {
		cout << a << ':';
		if(regex_match(a, m, e)) cout << "ok";
		cout << endl;
	}

//
//	for(int i=0; i<vr.size(); i++) {
//		imshow(vs[i] + to_string(vf[i]), t(vr[i]));
//		cout << vr[i] <<' '<< vf[i] <<' '<< vs[i] << endl;
//	}
	waitKey(0);
}
//P(C1 | information, system) 
//		= k * P(information | C1) * P(system | C1) * P(C1)
