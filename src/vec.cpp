#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;
int main() {
	vector<Point2f> vPoints(20);
	for (size_t i = 0; i < vPoints.size(); ++i)
		vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
	cout << "A vector of 2D Points = " << vPoints << endl << endl;
}
