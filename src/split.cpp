#include<iostream>
#include<cxcore.hpp>
#include<highgui.h>
#include<cassert>
#include"matrix.h"
using namespace cv;
using namespace std;

int main(int ac, char** av)
{
	Mat image;
	if(ac > 1) image = imread(av[1]); 
	else image = imread("IMG_0315.JPG");
	imshow("c", image);
	cout << image.depth() << endl;
	int ch = image.channels();
	cout << ch << +image.at<Vec3b>(30,40)[1] << endl;
	vector<Mat> rgb;
	split(image, rgb);
	Mat& r = rgb[2];
	Mat& g = rgb[1];
	Mat& b = rgb[0];
	Matrix<unsigned char> mr{r};
	Matrix<unsigned char> mg{g};
	Matrix<unsigned char> mb{b};
	Matrix<unsigned char> m{r};
	for(int i=0; i<mr.get_width(); i++) for(int j=0; j<mr.get_height(); j++) 
		m[i+1][j+1] = (mr[i+1][j+1] + mg[i+1][j+1] + mb[i+1][j+1]) / 3;
	r = m; //b=m; g=m;
	Mat fin;
	merge(rgb, fin);
	imshow("v", r);
	waitKey(0);
}
