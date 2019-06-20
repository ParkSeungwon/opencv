#include<iostream>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	Mat A = (Mat_<float>{3,3} << 107, 148, 1, 362, 143, 1, 81, 295, 1);//, 382, 289, 1);
	Mat B = (Mat_<float>{3,3} << 0, 0, 419, 0, 0, 239, 419, 239, 8);
	Mat M = A.inv() * B;
	cout << A << B << M;
	CVMat t = imread("card.jpg");
	t.show();
//	t.rotate(40);
	Point2f pt[4] = {{107, 148}, {362, 143}, {81,295}, {382,289}};
	Point2f dst[4] = {{0,0}, {419, 0}, {0, 239}, {419, 239}};
//	auto m = getPerspectiveTransform(dst, pt);
	t.get_business_card(pt);
//	perspectiveTransform(t, t, m);
//	cout << m << endl;
//	t.get_business_card(pt);
	t.show("business card");
	waitKey(0);
}


