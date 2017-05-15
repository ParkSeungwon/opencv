#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) return 0;
	CVMat t = imread(av[1]);
	t.gray();
	t.filter(GAUSSIAN);
	t.detect_circle();
	t.edge();
	t.detect_line();
	t.show("edge");
	t.restore();
	t.draw_detected_line();
	t.draw_detected_circle();
	t.show("line");
	waitKey(0);
}

