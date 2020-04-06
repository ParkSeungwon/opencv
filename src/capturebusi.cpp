#include<algorithm>
#include<iostream>
#include"cvmatrix.h"
using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	VideoCapture cap(0);
	if(!cap.isOpened()) {
		cout << "카메라가 연결되지 않았습니다." << endl;
		exit(-1);
	}
	CVMat frame;
	while(1) {
		cap >> frame;
		frame.save();
		frame.gray();
		frame.edge();
		frame.detect_line(130, 100, 100);
		
		frame.restore();
		frame.get_rect();
		frame.show();

//		auto v = frame.get_points(4);
//		vector<float> x, y;
//		for(int i=0; i<v.size(); i++) {
//			x.push_back(v[i].x);
//			y.push_back(v[i].y);
//		}
//		frame.polyline(x, y, {255, 0,0});
//		frame.show();
		if(waitKey(100) == 'q') break;
	}
}
//	CVMat t = imread(co.get<const char*>("file"));
//	auto v = t.get_points(4);
//	vector<float> x, y;
//	for(int i=0; i<v.size(); i++) {
//		x.push_back(v[i].x);
//		y.push_back(v[i].y);
//	}
//
//	t.save();
//	t.polyline(x, y, {255, 0, 0});
//	t.show("original");
//	t.restore();
//	t.get_businesscard(v);
//	t.show("final");
//	
//	auto a = cv::text::OCRTesseract::create(NULL, "eng+kor");
//	string s, email;
//	vector<Rect> vr; vector<string> vs; vector<float> vf;
//	a->run(t, s, &vr, &vs, &vf);
//
//	if(smatch sm; regex_search(s, sm, regex{R"(\S+@\S+\.\S+)"})) {
//		email = sm[0].str();
//		s = sm.prefix().str() + sm.suffix().str();
//	}
//
//	auto tel = get_tel(s);
//	cout << tel[0] << endl << tel[1] << endl << tel[2] << endl;
//
//	vs.clear();
//	stringstream ss; ss << s;
//	while(getline(ss, s)) if(s != "") vs.push_back(s);
//	string addr = get_with_wordvec("주소", "address", vs);
//	string job = get_with_wordvec("직책", "job", vs);
//	string company = get_with_wordvec("직장", "company", vs);
//	cout << email << endl << job << endl << addr << endl << company << endl;
//	waitKey(0);
//}
//P(C1 | information, system) 
//		= k * P(information | C1) * P(system | C1) * P(C1)
//	for(int i=0; i<vr.size(); i++) {
//		imshow(vs[i] + to_string(vf[i]), t(vr[i]));
//		cout << vr[i] <<' '<< vf[i] <<' '<< vs[i] << endl;
//	}

