#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) return 0;
	CVMat t = imread(av[1]);
	t.gray();
	t.show("gray");
	t.histo();
	t.fourier();
	t.detect_face();
	t.detect_circle();
	t.restore();
	t.draw_detected_face();
	t.draw_detected_circle();
	t.show("original");
	waitKey(0);
}


