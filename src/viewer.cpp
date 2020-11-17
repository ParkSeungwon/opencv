#include<opencv.hpp>
#include"option.h"
using namespace std;
using namespace cv;

int main(int ac, char **av) 
{
	CMDoption opt{
		{"image_files", "image files", FileExpansion{}},
		{"width", "showing width", 2500},
		{"height", "showing height", 1500},
		{"fullscreen", "full screen, default window mode", false},
		{"rotate", "view rotated", false},
		{"overlap", "overlap pixel", 100},
		{"resize", "magnify or shrink image", 1.0}
	};
	if(!opt.args(ac, av)) return 0;

	int w = opt.get<int>("width");
	int h = opt.get<int>("height");
	int o = opt.get<int>("overlap");
	if(opt.get<bool>("fullscreen"))
		setWindowProperty("viewer", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	Mat m;
	vector<Mat> v;
	for(const auto &a : opt.get<FileExpansion>("image_files")) 
		v.push_back(imread(a.string()));
	if(v.empty()) return -1;
	for(int i=1; i<v.size(); i++) if(v[i].cols != v[0].cols) return i;
	vconcat(v, m);//^ check if concat is possibe or return the index of different width.
	if(opt.get<bool>("rotate")) {
		m = m.t();
		flip(m, m, 1);
	}
	if(double r = opt.get<double>("resize"); r != 1) resize(m, m, {}, r, r);
	if(opt.get<bool>("rotate")) {
		for(int start = m.cols - w; start > -w + o; start=min(m.cols-w, start)) {
			Rect r{max(start, 0), 0, min(w, m.cols), m.rows};
			imshow("viewer", m(r));
			if(char c; (c = waitKey()) == 'q') return -1;
			else if(c == 'u') start += w - o;
			else start -= w - o;
		}
	} else {
		for(int start = 0; start < m.rows; start = max(0, start)) {
			Rect r{0, min(start, m.rows - h), m.cols, min(h, m.rows)};
			imshow("viewer", m(r));
			if(char c; (c = waitKey()) == 'q') return -1;
			else if(c == 'u') start -= h - o;
			else start += h - o;
		}
	}
	return 0;
}
