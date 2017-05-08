#include"cvmatrix.h"
#include<random>
using namespace std;

CVMat::CVMat(const cv::Mat& r) : cv::Mat(r)
{
	//save();
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
{
	normal_distribution<float> nd;
	random_device rd;
	int c = channels();
	int d = depth();
	for(int y=0; y<rows; y++) for(int x=0; x<cols; x++) for(int i=0; i<c; i++) {
		float noise = scale * nd(rd);
		switch(d) {
			case CV_8U: 
				at<cv::Vec3b>(y, x)[i] += noise; break;
			case CV_8S: at<char>(y, x, i) += noise; break;
			case CV_16U: at<unsigned short>(y, x, i) += noise; break;
			case CV_16S: at<short>(y, x, i) += noise; break;
			case CV_32S: at<int>(y, x, i) += noise; break;
			case CV_32F: at<float>(y, x, i) += noise; break;
			case CV_64F: at<double>(y, x, i) += noise; break;
		}
	}
}

array<Matrix<unsigned char>, 4> read_xpm(const char** xpm);
void CVMat::xpm(const char** x) 
{
	auto m = read_xpm(x);
	vector<Mat> v(m.begin(), m.end());
	merge(v, *this);
}

void CVMat::save()
{
	save_ = *this;
}

void CVMat::restore()
{
	cout << save_.rows << 'X' << save_.cols << endl;
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
