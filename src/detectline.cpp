#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

CVMat t;
int thres = 70, cont = 100, hop = 10, scale = 10;
void callback(int, void*) {
	t.restore();
	t.gray();
	t.filter(GAUSSIAN);
	t.edge();
	t.detect_line(thres, cont, hop);
	t.restore();
	t.draw_detected_line();
	t.scale(scale * 0.1, scale * 0.1);
	t.show("line");
}
int main(int ac, char** av)
{
	if(ac < 2) return 0;
	t = imread(av[1]);
	t.save();
	t.gray();
	t.filter(GAUSSIAN);
	t.edge();
	t.show("edge");
	t.detect_line(70, 100, 10);
	t.restore();
	t.draw_detected_line();
	t.show("line");
	createTrackbar("hop", "line", &hop, 100, callback);
	createTrackbar("thres", "line", &thres, 300, callback);
	createTrackbar("cont", "line", &cont, 300, callback);
	createTrackbar("scale", "line", &scale, 10, callback);
	waitKey(0);
}//48 88 130

