#pragma once
#include"matrix.h"
#include<string>
#include<cv.hpp>
#include<highgui.h>

class CVMat : public cv::Mat
{
public:
	CVMat(const cv::Mat& r);
	template<typename T> CVMat(const Matrix<T>& r);
	operator cv::Mat();
	void filter(const Mat& m);//apply kernel
	void show(std::string title);
	void restore();
	void save();
	void xpm(const char** xpm_content);
	void gray();
	void noise(int scale);//normal distrubution noise
	void median(int ksize);//median is good for salt&pepper noise
	
protected:
	cv::Mat save_;

private:
	void template_init();
};


static cv::Mat BLUR = Matrix<float>{{1,1,1},{1,1,1},{1,1,1}} * (1.0f / 9);
static cv::Mat GAUSSIAN = Matrix<float>{{1,2,1},{2,4,2},{1,2,1}} * (1.0f / 16);
static cv::Mat SHARPEN = Matrix<float>{{0,-1,0},{-1,5,-1},{0,-1,0}};
static cv::Mat GAUS = cv::getGaussianKernel(9, 0.5, CV_32F);
static cv::Mat SOBELX = Matrix<float>{{-1,0,1},{-2,0,2},{-1,0,1}};
static cv::Mat SOBELY = Matrix<float>{{-1,-2,-1},{0,0,0},{1,2,1}};
