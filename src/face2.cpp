#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) {
		CVMat t{Mat()};
		VideoCapture cap{0};
		while(waitKey(30) != 'q') {
			cap >> t;
			t.gray();
			t.detect_face();
			t.draw_detected_face();
			t.show("face");
		}
	} else {
		CVMat t = imread(av[1]);
		t.gray();
		t.detect_face();
		t.restore();
		t.draw_detected_face();
		t.show("face");
		waitKey(0);
	}
}


