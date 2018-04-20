#include<iostream>
#include<algorithm>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main()
{
	CVMat t{imread("AB.jpg")};
	t.gray();
	t.filter(SOBELX);
	t.show("corner");
	int to_cut[t.cols] = {};
	cout << t.cols << 'x' << t.rows << endl;
	for(int i=0; i<t.cols; i++) for(int j=0; j<t.rows; j++) 
		to_cut[i] += t.at<unsigned char>(j, i);
	int* idx = max_element(to_cut, to_cut + t.cols);
	int line = idx - to_cut;
	t.restore();
	CVMat a = t(Rect{0,0,line,t.rows});
	CVMat b = t(Rect{line, 0, t.cols-line, t.rows});
	a.show("a");
	b.show("b");
	imwrite("a.jpg", a);
	imwrite("b.jpg", b);
	waitKey(0);
}

