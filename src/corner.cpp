#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) return 0;
	CVMat t = imread(av[1]);
	t.gray();
	t.corner();
	t.restore();
	t.draw_detected_corner(0.01);
	t.show("corner");
	waitKey(0);
}

