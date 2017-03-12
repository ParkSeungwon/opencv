#include<highgui.h>
#include<cv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("IMG_0315.JPG");
	Mat mdilate, merode, mclose, mopen;

	Sobel(image, merode, CV_32F, 1,0,3);
	Sobel(image, mdilate, CV_32F, 0,1,3);
	Canny(image, mopen, 30,100);
	Laplacian(image, mclose, 3);
	mclose.convertTo(mclose, CV_8U, 1,0);

	imshow("원본영상", image);
	imshow("vertical sobel", merode);
	imshow("ho sobel", mdilate);
	imshow("canny", mopen);
	imshow("laplacian", mclose);
	waitKey(0);
}
