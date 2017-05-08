#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	CVMat t = imread("IMG_0315.JPG");
	t.gray();
	t.show("gray");
	CVMat clip = t(Rect{200, 300, 100, 100});
	clip.show("clip");
	clip.normalize();// = clip * (1.0f / sum(clip));
//	clip.show("nor");
	waitKey(0);
}
