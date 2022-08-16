#include"option.h"
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char **av)
{
	CMDoption co{
		{"input", "input image file", "in.png"},
		{"output", "output image file", "out.png"},
		{"C", "remove C component of image", false},
		{"M", "remove M component of image", false},
		{"Y", "remove Y component of image", false},
		{"K", "remove K component of image", false}
	};
	if(!co.args(ac, av)) return 0;

	if(strcmp(co.get<const char*>("input"), "null") == 0) {
		cout << "input output file must be specified\nrun with --help\n"; 
		return 0;
	}

	Mat img = imread(co.get<const char*>("input"));
	vector<Mat> channels;
	split(img, channels);
	for(int j=0; j<img.rows; j++) for(int i=0; i<img.cols; i++) {
		double b = channels[0].at<uchar>(j,i) / 255., g = channels[1].at<uchar>(j,i) / 255.,
					 r = channels[2].at<uchar>(j,i) / 255., k = 1-max(max(b, g), r), c, m, y;
		if(k == 1) c = m = y = 0;
		else c = (1-r-k)/(1-k), m = (1-g-k)/(1-k), y = (1-b-k)/(1-k);
		if(co.get<bool>("C")) c = 0;
		if(co.get<bool>("M")) m = 0;
		if(co.get<bool>("Y")) y = 0;
		if(co.get<bool>("K")) k = 0;
		channels[2].at<unsigned char>(j,i) = static_cast<unsigned char>(255 * (1-c) * (1-k));
		channels[1].at<unsigned char>(j,i) = static_cast<unsigned char>(255 * (1-m) * (1-k));
		channels[0].at<unsigned char>(j,i) = static_cast<unsigned char>(255 * (1-y) * (1-k));
	}
	merge(channels, img);
	imwrite(co.get<const char*>("output"), img);
}
