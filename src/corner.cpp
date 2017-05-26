#include<iostream>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	CVMat t = imread("ho2.jpg");
	t.gray();
	t.feature<ORB>();
	t.restore();
	t.draw_feature();
	t.show("corner");
	CVMat t2 = imread("homography2.jpg");
	t2.gray();
	t2.feature<ORB>();
	t2.restore();
	t2.draw_feature();
	t2.show("t2");
	
	auto matches = t.match(t2, 0.5);
	
	waitKey(0);
}

