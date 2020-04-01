#include<numeric>
#include<freetype.hpp>
#include<opencv.hpp>
#include"cvmatrix.h"
#include"option.h"
using namespace std;
using namespace cv;
using namespace cv::freetype;


int main(int ac, char **av)
{
	CMDoption opt{
		{"image_file", "image file", "image.png"},
		{"text", "banner text", "TEST"},
		{"font_height", "font size", 80},
		{"thickness", "line thickness, default fill", -1},
		{"rgb", "rgb value, default complementary color, ie. fe56d2", "compl"},
		{"x", "text org", 100},
		{"y", "text org", 100},
		{"output", "output filename", ""},
		{"truetype", "truetype font filename", 
			"/usr/share/fonts/truetype/nanum/NanumGothicBold.ttf"}
	};
	if(!opt.args(ac, av)) return 0;

	CVMat mat = imread(opt.get<const char*>("image_file")), hsv[3];
	mat.save();
	cvtColor(mat, mat, COLOR_BGR2HSV);
	mat.show();
	split(mat, hsv);
	unsigned sum[3];
	for(int i=0; i<3; i++) {
		sum[i] = std::accumulate(hsv[0].begin<uchar>(), hsv[0].end<uchar>(), 0);
		sum[i] /= mat.rows * mat.cols;
	}
	sum[0] += 90;
	sum[0] %= 180;

	Ptr<FreeType2> ft2 = createFreeType2();
	ft2->loadFontData(opt.get<const char*>("truetype"), 0);
	string text = opt.get<const char*>("text");
	string rgbs = opt.get<const char*>("rgb");
	int rgb = rgbs == "compl" ? -1 : stoi(rgbs, nullptr, 16);
	int thickness = opt.get<int>("thickness");
	int height = opt.get<int>("font_height");
	int x = opt.get<int>("x");
	int y = opt.get<int>("y");

	if(rgb == -1) ft2->putText(mat, text, {x, y}, height, {sum[0], sum[1], sum[2]},
			thickness, 4, true);
	cvtColor(mat, mat, COLOR_HSV2BGR);
	if(rgb != -1) ft2->putText(mat, text, {x, y}, height, 
			{rgb % 0x100, (rgb / 0x100) % 0x100, rgb / 0x10000}, thickness, 4, true);
	mat.show();
	if(string s = opt.get<const char*>("output"); s != "") imwrite(s, mat);
	waitKey();
}
