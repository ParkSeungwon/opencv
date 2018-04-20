#include<iostream>
#include<fstream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	CVMat mat = imread("homography2.jpg");
	CVMat back = imread("homography2.jpg");
	back.scale(.3, .3);
	mat.scale(0.3, 0.3);
	mat.show("camera");
	back.background();
	back = mat;
	back.background().show("back");
	waitKey(0);
}
