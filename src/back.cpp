#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("1.mkv");
	CVMat m{Mat()}, m2{Mat()};
	while(waitKey(30) < 0) {
		cap >> m;
		m.show("orig");
		m2 = m.background();
		m2.show("back");
	}
}
