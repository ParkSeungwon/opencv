#include<opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat m = (Mat_<float>(3,3) << 1,2,3,1,2,3,1,2,2);
	cout << m;
	Matx<float, 3, 3> m2 { 1,2,3,1,2,2,32,1,1};
	cout << m2;
	cout << m * Mat{m2} << endl;
}

