//#include<cxcore.hpp>
#include<highgui.h>
#include"matrix.h"
#include<cv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("IMG_0315.JPG");
	cout << image.channels() << endl;
	Mat kernel_shapen = Matrix<int>{{0,-1,0},{-1,5,-1},{0,-1,0}};
	Mat kernel_blur = Matrix<float>{{1,1,1},{1,1,1},{1,1,1}}/9.0f;
	Mat kernel_gaus = getGaussianKernel(9, 0.5, CV_32F);
	{Matrix<float> m{kernel_gaus}; cout << m << endl;}
	Mat dst_shapen, dst_blur, dst_gaus;

	filter2D(image, dst_shapen, image.depth(), kernel_shapen);
	filter2D(image, dst_blur, image.depth(), kernel_blur);
	filter2D(image, dst_gaus, image.depth(), kernel_gaus);

	imshow("원본영상", image);
	imshow("blur", dst_blur);
	imshow("gaussian", dst_gaus);
	imshow("shapen", dst_shapen);
	waitKey(0);
}
