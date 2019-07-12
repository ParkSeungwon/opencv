#include<opencv.hpp>
#include"option.h"
using namespace std;
using namespace cv;

int main(int ac, char **av) 
{
	CMDoption opt{
		{"image_files", "image files", FileExpansion{}},
		{"width", "showing width", 1366},
	//	{"height", "showing height", 760},
		{"windowed", "window mode, default full screen", false},
		{"overlap", "overlap pixel", 100}
	};
	if(!opt.args(ac, av)) return 0;

	int w = opt.get<int>("width");
//	int h = opt.get<int>("height");
	int o = opt.get<int>("overlap");
	namedWindow("viewer", CV_WINDOW_NORMAL);
	if(!opt.get<bool>("windowed"))
		cvSetWindowProperty("viewer", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	Mat m;
	vector<Mat> v;
	for(const auto &a : opt.get<FileExpansion>("image_files")) 
		v.push_back(imread(a.string()).t());
	if(v.empty()) return -1;
	for(int i=1; i<v.size(); i++) if(v[i].rows != v[0].rows) return i;
	hconcat(v, m);//^ check if concat is possibe, return the index of different width
	flip(m, m, 1);
	for(int start = m.cols - w; start > -w + o; ) {
		start = min(m.cols - w, start);
		Rect r{max(start, 0), 0, min(w, m.cols), m.rows};
		imshow("viewer", m(r));
		if(char c; (c = waitKey()) == 'q') return -1;
		else if(c == 'u') start += w - o;
		else start -= w - o;
	}
	return 0;
}
