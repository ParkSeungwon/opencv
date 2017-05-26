#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	if(ac < 2) {
		cout << av[0] << " [file to show]"; 
		return 0;
	}
	CVMat t = imread(av[1]);
	t.gray();
	t.edge(90,200);
	t.show("edge");
	waitKey(0);
}


