#include<iostream>
#include"cvmatrix.h"
#define NDEBUG
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 3) {
		cout << av[0] << " [file1] [file2]" << endl;
		return 0;
	}
	CVMat t = imread(av[1]);
	t.gray();
	t.feature<BRISK>();
	t.restore();
//	t.draw_feature();
	t.show("corner");
	CVMat t2 = imread(av[2]);
	t2.gray();
	t2.feature<BRISK>();
	t2.restore();
//	t2.draw_feature();
	t2.show("t2");
	
	auto matches = t.match(t2, 0.5);
	
	waitKey(0);
}

