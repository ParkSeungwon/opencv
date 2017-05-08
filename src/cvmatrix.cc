#include"cvmatrix.h"
#include<random>
#include<cassert>
using namespace std;

CVMat::CVMat(const cv::Mat& r) : cv::Mat{r} 
{
	save_ = clone();
	split(*this, bgr_);
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

void CVMat::noise(int scale)
{///gaussian noise 
	normal_distribution<float> nd;
	random_device rd;
	for(int i=0; i<rows*cols*channels(); i++) *(data+i) += scale * nd(rd);
}

cv::Mat_<float> CVMat::normalize()
{
//	assert(channels() == 1 && depth() == CV_8UC1);
	cv::Mat_<float> m;
	cv::normalize(*this, m, 0, 1, cv::NORM_MINMAX, CV_8UC1);
//	cv::Mat_<float> m{rows, cols};
//	int sum = 0;
//	for(int i=0; i<rows*cols; i++) {
//		sum += *(data + i);
//		*((float*)m.data+i) = (float)*(data+i) / 255 - 0.5;
//	}
	return m;
}

array<Matrix<unsigned char>, 4> read_xpm(const char** xpm);
void CVMat::xpm(const char** x) 
{
	auto m = read_xpm(x);
	vector<Mat> v(m.begin(), m.end());
	merge(v, *this);
}

void CVMat::restore()
{
	save_.copyTo(*this);
}

void CVMat::save()
{
	copyTo(save_);
}

void CVMat::filter(const Mat& ft)
{
	filter2D(*this, *this, depth(), ft);
}

void CVMat::show(std::string title)
{
	imshow(title, *this);
}

void CVMat::median(int k) 
{
	medianBlur(*this, *this, k);
}

void CVMat::gray()
{
	cvtColor(*this, *this, CV_BGR2GRAY);
}

void CVMat::template_init()
{
	CVMat c{Matrix<float>{2,2}};
	CVMat d{Matrix<double>{2,2}};
	CVMat e{Matrix<int>{2,2}};
	CVMat f{Matrix<unsigned char>{2,2}};
}
