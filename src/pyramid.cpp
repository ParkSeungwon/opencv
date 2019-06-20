#include<opencv.hpp>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	CVMat m = imread("Lenna.png");
	m.gray();
	m.edge();
	m.show();
	waitKey(0);
}

