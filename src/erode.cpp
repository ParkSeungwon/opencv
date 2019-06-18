#include<opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("IMG_0315.JPG");
	Mat mdilate, merode, mclose, mopen;

	erode(image, merode, Mat());
	dilate(image, mdilate, Mat());
	morphologyEx(image, mopen, MORPH_OPEN, Mat());
	morphologyEx(image, mclose, MORPH_CLOSE, Mat());

	imshow("원본영상", image);
	imshow("erode", merode);
	imshow("dilate", mdilate);
	imshow("open", mopen);
	imshow("close", mclose);
	waitKey(0);
}
