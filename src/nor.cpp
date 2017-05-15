#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	CVMat t = imread("1.png");
	t.gray();
	t.edge();
	t.detect_line();
	t.show("edge");
	t.restore();
	t.draw_detected_line();
	t.show("line");
	CVMat clip = t(Rect{250, 150, 100, 100});
	clip.show("clip");

	t.normalize(0,1);
	t.save();
	t.diffx();
	t.normalize(0,1);
	t.show("diffx");
	t.restore();
	t.diffy();
	t.normalize(0,1);
	t.show("diffy");
	
	clip.normalize(-0.5,0.5);// = clip * (1.0f / sum(clip));
	t.filter(clip);
	t.normalize(-6,1);
	t.show("search");
//	clip.show("nor");
	waitKey(0);
}
