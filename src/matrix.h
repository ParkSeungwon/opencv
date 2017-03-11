#pragma once
#include<iomanip>
#include<vector>
#include<cmath>
#include<string>
#include<cassert>
#include<numeric>
#include<iostream>
#include<array>
#include<cxcore.hpp>
#include"combi.h"
template<typename T> class Matrix;
template<typename T> Matrix<T> LxB(Matrix<T> L, Matrix<T> B) 
{///get x from Lx = B 
	auto h = L.get_height();
	if(L.get_width() != h || B.get_width() != 1 || B.get_height() != h) 
		throw "type mismatch";
	Matrix<T> x{1, h};
	for(int i=1; i<=h; i++) {
		T sum = 0;
		for(int j=1; j<i; j++) sum += L[j][i] * x[1][j];
		x[1][i] = B[1][i] - sum;
	}
	return x;
}

template<typename T> Matrix<T> UxB(Matrix<T> U, Matrix<T> B) 
{///get x from Ux = B
	auto h = U.get_height();
	if(U.get_width() != h || B.get_width() != 1 || B.get_height() != h) 
		throw "type mismatch";
	Matrix<T> x{1, h};
	for(int i=h; i>0; i--) {
		T sum = 0;
		for(int j=h; j>i; j--) sum += x[1][j] * U[j][i];
		x[1][i] = (B[1][i] - sum) / U[i][i];
	}
	return x;
}

template <typename T> class Matrix
{
public:
	Matrix(unsigned short w, unsigned short h) {
		width = w;
		height = h;
		arr = new T[h * w];
		for(int i=0; i<w * h; i++) arr[i] = 0;
	}
	Matrix(std::initializer_list<std::initializer_list<T>> li)
		: Matrix<T>{static_cast<unsigned short>(li.begin()->size()), 
					static_cast<unsigned short>(li.size())} {
		int x = 1, y = 1;
		for(auto& a : li) {
			for(auto& b : a) (*this)[x++][y] = b;
			y++; x = 1;
		}
	}
	Matrix(const cv::Mat& m) : Matrix<T>{m.cols, m.rows} {
		for(int x=1; x<=width; x++) for(int y=1; y<=height; y++) 
			(*this)[x][y] = m.at<T>(y-1, x-1);
	}

	operator cv::Mat() {
		cv::Mat mat {cv::Mat_<T>{height, width}};
		for(int x=1; x<=width; x++) for(int y=1; y<=height; y++) 
			mat.at<T>(y-1, x-1) = (*this)[x][y];
		return mat;
	}

	T* operator[](int x) const {
		assert(x > 0);
		return arr + (x -1) * height - 1;
	}
	T* operator[](int x) {
		assert(x > 0);
		return arr + (x -1) * height - 1;
	}
	T* data() {return arr;}
	Matrix(std::vector<std::vector<T>> v) : Matrix(v[0].size(), v.size()) {
		for(int x=0; x<width; x++) for(int y=0; y<height; y++) 
			arr[x * height + y] = v[y][x];
	}
	Matrix(const Matrix<T>& r) : Matrix(r.width, r.height) {
		for(int i=0; i<width * height; i++) arr[i] = r.arr[i];
	}
	Matrix(Matrix<T>&& r) {
		arr = r.arr;
		width = r.width;
		height = r.height;
		r.arr = nullptr;
	}
	virtual ~Matrix() {if(arr) delete [] arr;}
	Matrix<T> operator+(const Matrix<T>& r) const {
		if(width != r.width || height != r.height) throw "Matrix size not match";
		Matrix<T> m(width, height);
		for(int i=0; i<width*height; i++) m.arr[i] = arr[i] + r.arr[i];
		return m;
	}
	Matrix<T> operator-(const Matrix<T>& r) const {
		if(width != r.width || height != r.height) throw "Matrix size not match";
		Matrix<T> m(width, height);
		for(int i=0; i<width*height; i++) m.arr[i] = arr[i] - r.arr[i];
		return m;
	}
	Matrix<T> operator*(const Matrix<T>& r) const {
		if(width != r.height) throw "Matrix size not match";
		Matrix<T> m(r.width, height);
		for(int x = 1; x <= r.width; x++) for(int y = 1; y <= height; y++) {
			auto v = row(y);
			m[x][y] = std::inner_product(v.begin(), v.end(), r.column(x), (T)0.0);
		}
		return m;
	}
	Matrix<T>& operator=(const Matrix<T>& r) {
		if(width != r.width || height != r.height) throw "Matrix size not match";
		for(int i=0; i<width*height; i++) arr[i] = r.arr[i];
		return *this;
	}
	Matrix<T>& operator*=(const Matrix<T>& r) {
		*this = *this * r;
		return *this;
	}
	Matrix<T> operator*(const T& r) const {return r * *this;}
	bool operator==(const Matrix<T>& r) const;
	friend Matrix<T> operator*(const T l, const Matrix<T>& r) {
		Matrix<T> m(r.width, r.height);
		for(int y=0; y<r.height; y++) {
			for(int x=0; x<r.width; x++) {
				m.arr[y*r.width+x] = l * r.arr[y*r.width+x];
			}
		}
		return m;
	}
	Matrix<T> inverse() {
		auto a = LU_decompose();
		auto P = a[0], L = a[1], U = a[2];
		Matrix<T> I{width, height};
		for(int i=1; i<=height; i++) {
			Matrix B{1, height};//divide E into column pieces
			B[1][i] = 1;
			auto Ux = LxB(L, P * B);//Ax = B <==> PAx = PB <==> LUx = PB
			auto x = UxB(U, Ux);
			for(int j=1; j<=height; j++) I[i][j] = x[1][j];
		}
		return I;
	}

	Matrix<T> E() {
		if(width != height) throw "must be square matrix!";
		for(int x = 1; x <= width; x++) for(int y = 1; y <= height; y++) {
			if(x == y) (*this)[x][y] = 1;
			else (*this)[x][y] = 0;
		}
		return *this;
	}
	Matrix<T> gltranslate(T x, T y, T z) {
		if(width != 4 || height != 4) throw "should be 4x4";
		E();
		(*this)[4][1] = x;
		(*this)[4][2] = y;
		(*this)[4][3] = z;
		return *this;
	}
	Matrix<T> glrotateZ(T th) {
		if(width != 4 || height != 4) throw "should be 4x4";
		E();
		(*this)[1][1] = cos(th);
		(*this)[2][1] = -sin(th);
		(*this)[1][2] = sin(th);
		(*this)[2][2] = cos(th);
		return *this;
	}
	Matrix<T> glrotateX(T th) {
		if(width != 4 || height != 4) throw "should be 4x4";
		E();
		(*this)[2][2] = cos(th);
		(*this)[3][2] = -sin(th);
		(*this)[2][3] = sin(th);
		(*this)[3][3] = cos(th);
		return *this;
	}
	Matrix<T> glrotateY(T th) {
		if(width != 4 || height != 4) throw "should be 4x4";
		E();
		(*this)[1][1] = cos(th);
		(*this)[3][1] = -sin(th);
		(*this)[1][3] = sin(th);
		(*this)[3][3] = cos(th);
		return *this;
	}
	Matrix<T> glscale(T x, T y, T z) {
		if(width != 4 || height != 4) throw "should be 4x4";
		E();
		(*this)[1][1] = x;
		(*this)[2][2] = y;
		(*this)[3][3] = z;
		return *this;
	}
	auto LU_decompose() {
		if(width != height) throw "should be square";
		nPr npr{width, width};
		while(npr.next()) {
			Matrix<T> P{width, width};//조합으로 순열 매트릭스 생성.
			for(int j=1,i=0; j<=height; j++) P[npr[i++]][j] = 1;
			auto m = P * (*this);
			m = LU_decompose(m);
			if(!m[1][1]) continue;
			else {
				Matrix<T> L{width, height};
				Matrix<T> U{width, height};
				for(int x=1; x<=width; x++) 
					for(int y=1; y<=width; y++)
						if(x<y) L[x][y] = m[x][y];
						else U[x][y] = m[x][y]; 
				for(int x=1; x<=width; x++) L[x][x] = 1;
				return std::array<Matrix<T>, 3>{P, L, U};
			}
		}
	}

	Matrix<T> One() const;
	Matrix<T> surround(T wall = 0) const;
	template<typename T2>
	friend std::ostream& operator<<(std::ostream& o, const Matrix<T2>& r);
	unsigned short get_width() const {return width;}
	unsigned short get_height() const {return height;}
	
protected:
	T* arr;
	unsigned short width, height;

private:
	std::vector<T> row(int y) const{
		std::vector<T> v;
		T* p = arr + y - 1;
		for(int i=0; i<width; i++, p += height) v.push_back(*p);
		return v;
	}
	T* column(int x) const{
		return arr + (x - 1) * height;
	}
	Matrix<T> LU_decompose(Matrix<T> m) {
		int w = m.width;
		int h = m.height;
		if(!m[1][1]) return Matrix<T>{w,h};
		if(width == 1) return m;
		for(int y=2; y<=h; y++) m[1][y] /= m[1][1];// c /= a11
		for(int x=2; x<=w; x++) for(int y=2; y<=h; y++) 
			m[x][y] -= m[x][1] * m[1][y];// A' -= ch
		Matrix<T> mm{w-1, w-1};
		for(int x=1; x<w; x++) for(int y=1; y<w; y++) mm[x][y] = m[x+1][y+1];
		mm = LU_decompose(mm);// A' part recursive
		if(!mm[1][1]) return Matrix<T>{w,h};//if a11 == 0 -> change P, redo
		for(int x=1; x<w; x++) for(int y=1; y<w; y++) m[x+1][y+1] = mm[x][y];
		return m;
	}
};

template <typename T> std::ostream& operator<<(std::ostream& o, const Matrix<T>& r){
	int w = r.get_width(), h = r.get_height();
	int gap[w+1] {0,};
	for(int y=1; y<=h; y++) for(int x=1; x<=w; x++) {
		std::stringstream ss;
		ss << r[x][y];
		int sz = ss.str().length();
		if(gap[x] < sz) gap[x] = sz;
	}
	o << "\u23a1" << ' ';
	for(int x=1; x<=w; x++) o << std::setw(gap[x]) << r[x][1] << ' ';
	o << "\u23a4" << std::endl;
	for(int y=2; y<h; y++) {
	o << "\u23a2" << ' ';
		for(int x=1; x<=w; x++) o << std::setw(gap[x]) << r[x][y] << ' ';
		o << "\u23a5" << std::endl;
	}
	o << "\u23a3" << ' ';
	for(int x=1; x<=w; x++) o << std::setw(gap[x]) << r[x][h] << ' ';
	o << "\u23a6" << std::endl;
	return o;
}
