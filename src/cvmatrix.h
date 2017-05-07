#pragma once
#include"matrix.h"
#include<string>
//#include<cv.hpp>
#include<cxcore.hpp>
#include<highgui.h>

class CVMat : public cv::Mat
{
public:
	CVMat(const cv::Mat& r);
	template<typename T> CVMat(const Matrix<T>& r);
	operator cv::Mat();
	void filter(const Mat& m);
	void show(std::string title);
	void restore();
	
protected:
	cv::Mat save_;

private:
	void template_init();
};


static cv::Mat BLUR = Matrix<float>{{1,1,1},{1,1,1},{1,1,1}} * (1.0f / 9);
static cv::Mat SHARPEN = Matrix<float>{{0,-1,0},{-1,5,-1},{0,-1,0}};
//static cv::Mat GAUS = cv::getGaussianKernel(9, 0.5, CV_32F);
