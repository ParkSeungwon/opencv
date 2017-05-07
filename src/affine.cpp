#include<highgui.h>
#include<cv.hpp>
#include"matrix.h"
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("IMG_0315.JPG");
	Mat tmp_img, rot_img, scale_img, trans_img;
	Point2f pt1[3] = {{0,0}, {300,0},{0,300}};
	Point2f pt2[3] = {{10,50},{220,20},{80,290}};
	int cy = image.rows / 2;
	int cx = image.cols / 2;
	Point2f center = Point2f(image.rows/2, image.cols/2);
	
	Matrix<float> af{4,4};
	af = af.gltranslate(cx, cy, 0) * af.glrotateZ(M_PI/3) * 
		af.gltranslate(-cx, -cy, 0);
	cout << af;
	//af.glscale(0.9,0.7,1);
	Matrix<float> affi{3,2};
	for(int i=1; i<=2; i++) for(int j=1; j<=2; j++) affi[i][j] = af[i][j];//2 dim
	affi[3][1] = af[4][1];//translate 4->3 앞으로 당긴다.x 평행변환
	affi[3][2] = af[4][2];
	
	Mat affine_mat = affi;//getAffineTransform(pt1, pt2);
	cout << affine_mat << endl;

	float angle = 300;
	float scale = 0.9;
	Mat rot_mat = getRotationMatrix2D(center, angle, scale);
	cout << rot_mat;
//	rot_mat.at<double>(0,2) += -50;
//	rot_mat.at<double>(1,2) += 30;

	warpAffine(image, tmp_img, affine_mat, image.size());
	warpAffine(image, rot_img, rot_mat, rot_img.size());

	imshow("original 영상", image);
	imshow("affine trans", tmp_img);
	imshow("rotation trans", rot_img);
	waitKey(0);
}

