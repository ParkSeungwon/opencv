#include<algorithm>
#include<iostream>
#include<regex>
#include"option.h"
#include"cvmatrix.h"
#include"server.h"
#include<opencv2/text/ocr.hpp>
#define NDEBUG
using namespace std;
using namespace cv;

string find_continuous_digits(string s, int cont, int yield=2) 
{//yield 1 or 2 non digit
	string r, y;
	bool record = false;
	for(char c : s) {
		if(isdigit(c)) {
			r += (r == "" ? "" : y) + c;
			y = "";
		} else y += c;
		if(y.size() >= yield) {
			if(r.size() > cont) return r;
			y = "";
			r = "";
		}
	}
	return r.size() > cont ? r : "";
}

array<string, 3> get_tel(string &s)
{//return mobile, tel, fax and remove that string from s
	array<string, 3> r, tmp;
	for(int k=0,j=0; j<3; j++) {
		string tel = find_continuous_digits(s, 10, 2);
		if(tel == "") break;
		int pos = s.find(tel);
		for(int i=1; i<=7; i++) {
			bool dft = false;
			switch(toupper(s[pos - i])) {
				case 'M': r[0] = tel; break;
				case 'T': r[1] = tel; break;
				case 'F': r[2] = tel; break;
				default: dft = true;
			}
			if(!dft) {//remove tel part
				s.erase(pos - i, i + tel.size());
				break;
			} else if(i == 7) {
				tmp[k++] = tel;//if no MFT found
				s.erase(pos, tel.size());
			}
		}
	}
	for(int k=0,i=0; i<3; i++) if(r[i] == "") r[i] = tmp[k++];
	return r;
}

string get_addr(vector<string> &v)
{
	auto it = std::max_element(v.cbegin(), v.cend(), [](string a, string b) {
			return a.size() < b.size();});
	string r = *it;
	v.erase(it);
	return r;
}

string get_name(vector<string> &v)
{
	auto it = min_element(v.cbegin(), v.cend(), [](string a, string b) {
			return a.size() < b.size(); });
	string r = *it;
	v.erase(it);
	return r;
}

float wordvec(string kor, string eng, string s)
{//calculate word similarity according to language Korean or English => categorize s
	for(char &c : s) if(ispunct(c)) c = ' ';
	int english = count_if(s.begin(), s.end(), [](char c) { return isalpha(c) != 0;});
	int korean = count_if(s.begin(), s.end(), [](char c) { return isprint(c) == 0;});
	stringstream ss1; ss1 << s;
	string to_send;
	while(ss1 >> s) to_send += s + ' ' + (english < korean ? kor : eng) + ' ';
	float sum = 0;
	if(!to_send.empty()) {
		Client cl{"localhost", 3003};//connect to gensim server
		cl.send(to_send);
		cout << "sending : " << to_send << endl;
		stringstream ss;
		ss << *cl.recv();
		for(float f; ss >> f;) sum += f;
	}
	return sum;
}

string get_with_wordvec(string kor, string eng, vector<string> &v)
{
	auto it = max_element(v.begin(), v.end(), [kor, eng](string a, string b) { return 
			wordvec(kor, eng, a) < wordvec(kor, eng, b); });
	string r = *it;
	v.erase(it);
	return r;
}

int main(int ac, char** av)
{
	CMDoption co{
		{"file", "picture file", "Lenna.png"},
	};
	if(!co.args(ac, av)) return 0;
	CVMat t = imread(co.get<const char*>("file"));
	auto v = t.get_points(4);
	vector<float> x, y;
	for(int i=0; i<v.size(); i++) {
		x.push_back(v[i].x);
		y.push_back(v[i].y);
	}

	t.save();
	t.polyline(x, y, {255, 0, 0});
	t.show("original");
	t.restore();
	t.get_businesscard(v);
	t.show("final");
	
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
	waitKey(0);
}
//P(C1 | information, system) 
//		= k * P(information | C1) * P(system | C1) * P(C1)
//	for(int i=0; i<vr.size(); i++) {
//		imshow(vs[i] + to_string(vf[i]), t(vr[i]));
//		cout << vr[i] <<' '<< vf[i] <<' '<< vs[i] << endl;
//	}
