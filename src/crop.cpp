#include<algorithm>
#include<iostream>
#include"cvmatrix.h"
#include"option.h"
using namespace std;
using namespace cv;

CVMat m;
vector<Point> v;
void on_mouse_event(int event, int x, int y, int flags, void* param ) {
	static vector<Point>::iterator it = v.end();
	if(event == 1) it = find_if(v.begin(), v.end(),//left button down
				[x, y](Point p) {return abs(p.x - x) < 10 && abs(p.y - y) < 10;});
	else if(event == 4) it = v.end();//left button up
	else if(event == 0 && it != v.end()) {//drag
		it->x = x;
		it->y = y;
		m.restore();
		polylines(m, v, true, {255, 0,0}, 3);
		m.show();
	}
}

int main(int ac, char** av)
{
	CMDoption opt{  
		{"image_file", "image file", "image.png"},
		{"output", "output image file", "out.png"}
	};
	if(!opt.args(ac, av)) return 0;

	m = imread(opt.get<const char*>("image_file"));
	m.save();
	v = m.get_points(4);
	m.restore();
	polylines(m, v, true, {255, 0,0}, 3);
	m.show();
	setMouseCallback("OpenCV", on_mouse_event);
	waitKey();
	m.restore();
	m.get_businesscard(v);
	m.show("business card");
	if(waitKey() == 'w') imwrite(opt.get<const char*>("output"), m);
}

