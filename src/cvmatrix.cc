#include"cvmatrix.h"
#include<highgui.h>
using namespace std;

CVMat::CVMat(const cv::Mat& r) : cv::Mat(r)
{
	save_ = r;
}

template<typename T> CVMat::CVMat(const Matrix<T>& r) 
{
	int w = r.get_width();
	int h = r.get_height();
	cv::Mat_<T> m{h, w};
	for(int x=1; x<=w; x++) for(int y=1; y<=h; y++) 
		m.at<T>(y-1, x-1) = r[x][y];
	cv::Mat::operator=(m);
}

CVMat::operator cv::Mat() 
{
	Mat r;
	r = *this;
	return r;
}

void CVMat::restore()
{
	cv::Mat::operator=(save_);
}

void CVMat::filter(const Mat& ft)
{
	filter2D(*this, *this, depth(), ft);
}

void CVMat::show(std::string title)
{
	imshow(title, *this);
}

void CVMat::template_init()
{
	CVMat c{Matrix<float>{2,2}};
	CVMat d{Matrix<double>{2,2}};
	CVMat e{Matrix<int>{2,2}};
}
