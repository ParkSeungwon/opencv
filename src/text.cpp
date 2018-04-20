#include<iostream>
#include<string>
#include<valarray>
#include"plot.h"
#include"cvmatrix.h"
using namespace std;
using namespace cv;

CVMat t = imread("Lenna.png");
int slider = 1;
void on_mouse(int event, int x, int y, int, void*) {
	t.restore();
	t.text(to_string(x) + ',' + to_string(y), {0, 200}, slider);
	t.show();
}
void on_trackbar(int, void*) {
	t.restore();
	t.noise(slider);
	t.show();
}


int main(int ac, char** av)
{
	t.text("hello this is a long words");
	t.text("next line", {0, 150}, 6, {0, 0, 255}, 16);

	auto x = arange(0, 0.1, 9);
	valarray<float> y = sin(x);
	x = x * 50.0f + 50;
	y = -y * 50.0f + 50;
	t.polyline(x, y, {0,0,0}, 10);
	t.polyline(array<int,3>{2, 300, 40}, array<int,3>{0, 400, 200}, {0, 255, 0}, 3);
	
	rectangle(t, {10,10}, {100,100}, {200,100,0});
	t.show();
	string s;
	for(char c; (c = waitKey(0)) != 'q'; ) {
		t.restore();
		s += c;
		t.text(s, {100, 300}, 2, {255, 0, 0}, 4);
		t.show();
	}
	while(waitKey(10) < 0) {
		t.restore();
		x = x - 1.f;
		t.polyline(x, y);
		t.show();
	}
	for(int i=0,k=-1; waitKey(10) == -1; i+=k) {
		auto wNh = t.text(to_string(i), {200, 200}, 4, {100, 120, 0}, 5);
		t.restore();
		t.text(to_string(i), {t.cols * 2 / 3 - wNh.first, (t.rows + wNh.second) / 2}, 4, {100, 120, 0}, 5);
		t.show();
		if(i == 200 || i == 0) k *= -1;
	}

	setMouseCallback("OpenCV", on_mouse, 0);
	void (*fp)(int, void*) = nullptr;
	createTrackbar("font size", "OpenCV", &slider, 10, on_trackbar);
	waitKey(0);
}
