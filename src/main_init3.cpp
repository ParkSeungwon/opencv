#include<iostream>
#include<cxcore.hpp>
#include<highgui.h>
#include"data/blender-32x32.xpm"
#include"data/logo.xpm"
#include"matrix.h"
using namespace cv;
using namespace std;

array<Matrix<unsigned char>, 4> read_xpm(const char** xpm);
int main()
{
	Matrix<int> m{{1,2,3},{4,5,6},{7,8,9}};
	Mat mat = m;
	cout << mat << endl;

	Mat mat2 = Mat::ones(10,5,CV_32S);
	Matrix<int> mm{mat2};
	cout << mm << endl;
	vector<Mat> v;
	for(auto& a : read_xpm(logo_xpm)) v.push_back(a); 

	Mat merge1;
	merge(v, merge1);
	imshow("rr", merge1);

	Mat image = imread("IMG_0315.JPG");
	//Mat image2 = imread("src/blender-32x32.xpm");

//	namedWindow("가마쿠라 대불");
	imshow("가마쿠라대불", image);
	//imshow("test", mat);
	waitKey(0);
}
