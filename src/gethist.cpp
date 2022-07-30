#include<iostream>
#include"cvmatrix.h"
#include "qrcodegen.hpp"
using namespace std;
using namespace cv;
using namespace qrcodegen;

int main(int ac, char** av)
{
	if(ac < 2) return 0;
	QrCode qr0 = QrCode::encodeText("Hello, world!", QrCode::Ecc::HIGH);
	CVMat mat{qr0, 8, 4};
	CVMat t = imread(av[1]);
	t.show("original");
	t.gray();
	t.show("gray");
	t.histo();
	t.fourier();
	t.info();
	t.fourier_add_qr(mat);
	mat.show("qrcode");
	t.inv_fourier();
	waitKey(0);
}


