#include<iostream>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	CVMat t = imread(av[1]);
	t.save();
	t.gray();
	t.filter(GAUSSIAN);
	t.edge();
	t.detect_contours();
	t.restore();
	t.draw_detected_contours(1);
	t.show();
	waitKey(0);
}


