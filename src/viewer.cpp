#include<opencv.hpp>
#include"option.h"
using namespace std;
using namespace cv;

int middle(int a, int b, int c)
{//return middle number
	int k[] = {a, b, c};
	sort(k, k+3);
	return k[1];
}
int main(int ac, char **av) 
{
	CMDoption opt{
		{"image_files", "image files", FileExpansion{}},
		{"width", "showing width", 1366},
		{"height", "showing height", 760},
		{"windowed", "window mode, default full screen", false},
		{"rotate", "view rotated", false},
		{"overlap", "overlap pixel", 100},
		{"resize", "magnify or shrink image", 1.0}
	};
	if(!opt.args(ac, av)) return 0;

	int w = opt.get<int>("width");
	int h = opt.get<int>("height");
	int o = opt.get<int>("overlap");
	namedWindow("viewer", CV_WINDOW_NORMAL);
	if(!opt.get<bool>("windowed"))
		cvSetWindowProperty("viewer", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	Mat m;
	vector<Mat> v;
	if(opt.get<bool>("rotate")) {
		for(const auto &a : opt.get<FileExpansion>("image_files")) 
			v.push_back(imread(a.string()).t());
		if(v.empty()) return -1;
		for(int i=1; i<v.size(); i++) if(v[i].rows != v[0].rows) return i;
		hconcat(v, m);//^ check if concat is possibe or return the index of different width.
		flip(m, m, 1);
		if(double r = opt.get<double>("resize"); r != 1) resize(m, m, {}, r, r);
		for(int start = m.cols - w; start > -w + o; ) {
			start = min(m.cols - w, start);
			Rect r{max(start, 0), 0, min(w, m.cols), m.rows};
			imshow("viewer", m(r));
			if(char c; (c = waitKey()) == 'q') return -1;
			else if(c == 'u') start += w - o;
			else start -= w - o;
		}
	} else {
		for(const auto &a : opt.get<FileExpansion>("image_files")) 
			v.push_back(imread(a.string()));
		if(v.empty()) return -1;
		for(int i=1; i<v.size(); i++) if(v[i].cols != v[0].cols) return i;
		vconcat(v, m);//^ check if concat is possibe or return the index of different width.
		if(double r = opt.get<double>("resize"); r != 1) resize(m, m, {}, r, r);
		for(int start = 0; start < m.rows; ) {
			Rect r{0, middle(0, start, m.rows - h), m.cols, h};
			imshow("viewer", m(r));
			if(char c; (c = waitKey()) == 'q') return -1;
			else if(c == 'u') start -= h - o;
			else start += h - o;
		}
	}
	return 0;
}
