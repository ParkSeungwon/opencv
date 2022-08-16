#include <string>
#include <vector>
#include<bits/stdc++.h>
#include<iostream>
#include "qrcodegen.hpp"
#include"cvmatrix.h"
#include"option.h"
#include<opencv2/objdetect.hpp>

using namespace qrcodegen;
using namespace std;

static std::string toSvgString(const QrCode &qr, int border) {
	if (border < 0)
		throw std::domain_error("Border must be non-negative");
	if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
		throw std::overflow_error("Border too large");
	
	std::ostringstream sb;
	sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
	sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
	sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
	sb << "\t<path d=\"";
	for (int y = 0; y < qr.getSize(); y++) {
		for (int x = 0; x < qr.getSize(); x++) {
			if (qr.getModule(x, y)) {
				if (x != 0 || y != 0)
					sb << " ";
				sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
			}
		}
	}
	sb << "\" fill=\"#000000\"/>\n";
	sb << "</svg>\n";
	return sb.str();
}

// Simple operation
int main(int ac, char** av) {	
	CMDoption co{
		{"input", "input image file", "in.png"},
		{"output", "output image file", "out.png"},
		{"encode", "insert hidden qr code", false}
	};
	if(!co.args(ac, av)) return 0;

	QrCode qr0 = QrCode::encodeText("Hello, world!", QrCode::Ecc::HIGH);
	CVMat mat{qr0, 8, 4};
	mat.show();

	CVMat m = cv::imread(co.get<const char*>("input"));
	m.gray();
	m.fourier();
	if(!co.get<bool>("encode")) {
		auto m2 = m.get_plane0();
		cv::imshow("qr code decoded", m2);
		m2.convertTo(m2, CV_8UC1, 255);
		cv::imwrite(co.get<const char*>("output"), m2);
		cv::waitKey(0);
		return 0;
	}
	m.fourier_add_qr(mat);
	m.inv_fourier();
	m.show("inv");
	if(co.get<bool>("encode")) cv::imwrite(co.get<const char*>("output"), m);

	cv::Mat pts, rectified, tmp;
	m.convertTo(tmp, CV_8UC1, 255);
	cv::QRCodeDetector qrd;

	//qrd.detectAndDecode(tmp, pts, rectified);
	cv::waitKey(0);
}
