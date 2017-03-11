#include<sstream>
#include<map>
#include"matrix.h"
using namespace std;

array<unsigned char, 4> change(const char* p)
{
	unsigned char c[6];
	if(*p == '#') {
		for(int i=0; i<6; i++) {
			if(p[i+1] <= '9') c[i] = p[i+1] - '0';
			else c[i] = p[i+1] - 'A' + 10;
		}
		for(int i=0; i<6; i+=2) c[i] = c[i] * 16 + c[i+1];
		return {c[0], c[2], c[4], 0xff};
	} else return {0,0,0,0};
}

array<Matrix<unsigned char>, 4> read_xpm(const char** xpm) {
	stringstream ss;
	ss << xpm[0];
	size_t w, h, color, ch;//ch = expressing character per color
	ss >> w >> h >> color >> ch;

	map<string, array<unsigned char, 4>> color_map;
	for(int i=0; i<color; i++) 
		color_map[string(xpm[i+1], ch)] = change(xpm[i+1] + ch + 3);

	Matrix<unsigned char> r{w,h}, g{w,h}, b{w,h}, a{w,h};

	for(int y=0; y<h; y++) for(int x=0; x<w; x++) {
		r[x+1][y+1] = color_map[string(xpm[color+1+y] + x*ch, ch)][0];
		g[x+1][y+1] = color_map[string(xpm[color+1+y] + x*ch, ch)][1];
		b[x+1][y+1] = color_map[string(xpm[color+1+y] + x*ch, ch)][2];
		a[x+1][y+1] = color_map[string(xpm[color+1+y] + x*ch, ch)][3];
	}
	return {r,g,b,a};
}

