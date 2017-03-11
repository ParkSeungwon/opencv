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
	vector<Mat> v1, v2;
	for(auto& a : read_xpm(logo_xpm)) v1.push_back(a); 
	for(auto& a : read_xpm(xpm)) v2.push_back(a); 

	Mat merge1, merge2;
	merge(v1, merge1);
	line(merge1, {50,50}, {100,10}, {0,0,255}, 8);
	putText(merge1, "Test tes", {100,100},0,0.5,{0,255,0}, 2);
	imshow("logo", merge1);
	imwrite("lll.jpg", merge1);
	merge(v2, merge2);
	imshow("blender", merge2);
	cout << merge2.channels() << "channels" << merge2.depth() << "depth";

//	Mat image = imread("IMG_0315.JPG");
	//Mat image2 = imread("src/blender-32x32.xpm");

//	namedWindow("가마쿠라 대불");
//	imshow("가마쿠라대불", image);
	//imshow("test", mat);
	waitKey(0);
}
