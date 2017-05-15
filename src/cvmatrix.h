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
	void show(std::string title="OpenCV");
	void restore();
	void save();
	void xpm(const char** xpm_content);
	void gray();
	void noise(int scale);//normal distrubution noise
	void median(int ksize);//median is good for salt&pepper noise
	void normalize(float a, float b);
	void diffx();//after normalize to float
	void diffy();
	void edge(int lowthreshold=30, int thresXratio=100);//Canny
	void corner(float k = 0.04, int block = 3, int aperture = 3);
	void draw_detected_corner(float thres = 0.01);
	void detect_line(int threshold=180, int continuous=50, int hop=10);//edge->Hough
	void detect_circle(int canny_threshold=200, int center_threshold=100,//gray->circ 
			int min_radius=0, int max_radius=0);//gradient를 보므로 edge로 하면 안됨.
	void detect_face();//gray->face
	void draw_detected_line(cv::Scalar color = {0,0,255});
	void draw_detected_circle(cv::Scalar color = {0,0,255});
	void draw_detected_face();
	void fourier(std::string window = "Fourier");//after gray
	cv::MatND histo(std::string windwo = "Histogram");//after gray
	
protected:
	cv::Mat save_, harris_;
	std::vector<Mat> bgr_;
	std::vector<cv::Vec4i> lines_;
	std::vector<cv::Vec3f> circles_;
	std::vector<cv::Rect> faces_;

private:
	void template_init();
};


static cv::Mat BLUR = Matrix<float>{{1,1,1},{1,1,1},{1,1,1}} * (1.0f / 9);
static cv::Mat GAUSSIAN = Matrix<float>{{1,2,1},{2,4,2},{1,2,1}} * (1.0f / 16);
static cv::Mat SHARPEN = Matrix<float>{{0,-1,0},{-1,5,-1},{0,-1,0}};
//static cv::Mat GAUS = cv::getGaussianKernel(9, 0.5, CV_32F);
static cv::Mat SOBELX = Matrix<float>{{-1,0,1},{-2,0,2},{-1,0,1}};
static cv::Mat SOBELY = Matrix<float>{{-1,-2,-1},{0,0,0},{1,2,1}};
