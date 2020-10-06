#include<opencv.hpp>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	namedWindow("OpenCV", WINDOW_GUI_EXPANDED);
	CVMat m = imread("Lenna.png");
	m.gray();
	m.edge();
	m.show();
	waitKey(0);
}

