#include<set>
#include<array>
#include<iostream>
#include"option.h"
#include"cvmatrix.h"
#include<opencv2/text/ocr.hpp>
#define NDEBUG
using namespace std;
using namespace cv;

//depth : CV_8U, CV_8S, CV_16U, CV_16S, CV_32S, CV_32F, CV_64F
int main(int ac, char** av) {
	CVMat m = imread("fullscr.png"), tmpl = imread("templ.png"), result;
	
	//find template position
	m.save();
	matchTemplate(m, tmpl, result, CV_TM_SQDIFF);//use reload icon as template
	double min, max; Point minpos, maxpos;
	minMaxLoc(result, &min, &max, &minpos, &maxpos);
//	cout << minpos << endl;

	//find contours
	m.gray();
	m.filter(GAUSSIAN);
	m.edge();
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	vector<double> distance_normal;
	findContours(m, contours, hierachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//find the contour next to template
	for(const auto &a : contours) {
		double sum = 0;
		for(const auto &b : a) sum += norm(b - (minpos - Point{60, 0}));
		distance_normal.push_back(sum / a.size());
	}
	auto it = min_element(distance_normal.begin(), distance_normal.end());

	//find four corners
	Point2f xy[4] = {{9000,9000}, {0, 1000}, {1000, 0}, {0,0}};
	for(const auto &[x, y] : contours[it - distance_normal.begin()]) {
		if(x + y < xy[0].x + xy[0].y) xy[0] = {x, y};
		if(x - y > xy[1].x - xy[1].y) xy[1] = {x, y};
		if(y - x > xy[2].y - xy[2].x) xy[2] = {x, y};
		if(x + y > xy[3].x + xy[3].y) xy[3] = {x, y};
	}

	//extract captcha
	m.restore();
	m = m(Rect{xy[0], xy[3]});

//	cout << m.type() << ' ' << m.depth() << ' ' << m.channels() << endl;
//	cout << CV_8UC3 << ' ' << CV_8U << endl;
	//character threshold and revert
	m.gray();
	for(int x=0; x<m.cols; x++) for(int y=0; y<m.rows; y++) {
		auto &a = m.at<unsigned char>(y, x);
		if(a < 200) a = 255;
		else a = 0;
	}

	//ocr apply
	auto a = cv::text::OCRTesseract::create(NULL, "eng");
	string s;
	vector<Rect> vr; vector<string> vs; vector<float> vf;
	a->run(m, s, &vr, &vs, &vf);
	cout << s;
//	for(int i=0; i<vr.size(); i++) {
//		imshow(vs[i] + to_string(vf[i]), m(vr[i]));
//		cout << vr[i] <<' '<< vf[i] <<' '<< vs[i] << endl;
//	}
}
