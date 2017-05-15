#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) return 0;
	CVMat t = imread(av[1]);
	t.show("original");
	t.gray();
	t.filter(GAUSSIAN);
	t.edge(300,700);//300, 700 is good for fuguang
	t.show("canny");
	waitKey(0);
}

