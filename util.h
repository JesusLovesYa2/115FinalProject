#ifndef H_UTIL 
#define H_UTIL 

#include "array.h"
#include "list.h"
//#include "bst.h" //not necessary 

#include <string>
#include <chrono>
#include <iostream>

using namespace std;

FIBTYPE fib(int n, Array<FIBTYPE>& cv);//defined in util.cc 
FIBTYPE fib(int n);//defined in util.cc 

template <typename T, typename N>
struct Pair {
	T x;
	N y;

	Pair() {
	}
	Pair(T i, N j) {
		x = i;
		y = j;
	}

	void print() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

template <typename T, typename N>
bool operator==(Pair<T,N>& a, Pair<T,N>& b) {
	return (a.x == b.x && a.y == b.y);
}

template <typename T, typename U, typename V>
struct Tuple {
	T x;
	U y;
	V z;

	Tuple(T a, U b, V c) {
		x = a;
		y = b;
		z = c;
	}

	Tuple<T,U,V>& operator=(Tuple<T,U,V>& t) {
		x = t.x;
		y = t.y;
		z = t.z;
		return *this;
	}
};

template <typename T> 
class Matrix {
	Array<T>* a;//data array 
	Array<int>* vc;//valid cols 
	Array<int>* vr;//valid rows 
	int w;//width, or cols 
	int h;//height, or rows 
	int mc = 0;//historical max columns 
	int mr = 0;//historical max rows 
	T dv;//default value, for adding new rows/cols 
	int ms;//max size, for reallocating the data array 

	public:
	Matrix(int nw, int nh, T v, int nm = 100) {
		w = nw;
		mc = w;
		h = nh;
		mr = h;
		dv = v;
		ms = nm;
		a = new Array<T>(w*h, dv, ms);
		vc = new Array<int>(w,-1);
		vr = new Array<int>(h,-1);
		for (int i = 0; i < w; i++) {
			vc->place(i,i);
		}
		for (int i = 0; i < h; i++) {
			vr->place(i,i);
		}
	}
	~Matrix() {
		delete a;
		delete vc;
		delete vr;
	}

	void test() {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				set(j,i,i*w+j);
			}
		}
	}

	int get_height() const {
		return h;
	}
	int get_width() const {
		return w;
	}

	T get(int x, int y) const {
		if (vc->find(x) == -1 || vr->find(y) == -1) {
			cerr << x << " " << y << endl;
			die("Invalid index for Matrix::get()");
			exit(0);
		}
		return a->get(y*w+x);
	}

	bool set(int x, int y, T v) {
		//cout << "set(" << x << "," << y << ")" << endl;
		if (vc->find(x) == -1 || vr->find(y) == -1) {
			//cout << "set failed (invalid)" << endl;
			return false;
		}
		if (a->get(y*w+x) == v) {
			//cout << "set failed (equal)" << endl;
			return false;
		}
		return a->place(v,y*w+x);
	}

	void iota(int max = 9, int min = 0) {
		a->iota(a->get_size(),max,min);
	}

	void print(bool n = false) {
		if (n) {
			cout << "\\";
			for (int j = 0; j < vc->get_size(); j++) {
				cout << "\t" << vc->get(j);
			}
			cout << endl;
		}
		for (int i = 0; i < vr->get_size(); i++) {
			int y = vr->get(i);
			if (n) cout << y << "\t";
			for (int j = 0; j < vc->get_size(); j++) {
				int x = vc->get(j);
				cout << get(x,y) << "\t";
			}
			cout << endl;
		}
	}

	bool pop_c(int c) {
		//remove a column without moving others 
		return vc->pop_first(c);
	}
	bool pop_r(int r) {
		//remove a row without moving others 
		return vr->pop_first(r);
	}

	int add_c() {
		//add column and return its number (lowest available) 
		for (int i = 0; i < mc; i++) {
			if (vc->find(i) == -1) {
				vc->push_in(i);
				//clear data in this column 
				for (int j = 0; j < vr->get_size(); j++) {
					set(i,vr->get(j),dv);
				}
				return i;
			}
		}
		//if no deleted columns 
		vc->push_in(mc);
		Array<T>* na = a;
		mc++;
		a = new Array<T>(mc*mr,dv,ms);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				a->place(na->get(i*w+j),i*mc+j);
			}
		}
		delete na;
		w = mc;
		//cout << "size=" << a->get_size() << endl;
		return mc -1 ;
	}
	int add_r() {
		//like add_c() but for row 
		//vr->print();
		for (int i = 0; i < mr; i++) {
			if (vr->find(i) == -1) {
				//vr->print();
				vr->push_in(i);
				//vr->print();
				for (int j = 0; j < vc->get_size(); j++) {
					set(vc->get(j),i,dv);
				}
				//vr->print();
				return i;
			}
		}
		for (int i = 0; i < w; i++) {
			a->push_back(dv);
		}
		vr->push_in(mr);
		mr++;
		h = mr;
		//cout << "size=" << a->get_size() << endl;
		return mr-1;
	}

	bool add_c(int c) {
		//don't use this -- just here because I wrote it 
		if (vc->find(c) != -1) return false;
		else if (c < w) {
			vc->push_in(c);
			for (int i = 0; i < vr->get_size(); i++) {
				set(c,vr->get(i),dv);
			}
			return true;
		}
		else {
			Array<T>* na = a;
			a = nullptr;
			a = new Array<T>((c+1)*h,dv,ms);
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					a->place(na->get(i*w+j),i*(c+1)+j);
				}
			}
			delete na;
			vc->push_in(c);
			w = c + 1;
			return true;
		}
	}
	bool add_r(int r) {
		//like above, but with rows instead 
		//don't use this -- just here because I wrote it 
		if (vr->find(r) != -1) return false;
		else if (r < h) {
			vr->push_in(r);
			for (int i = 0; i < vc->get_size(); i++) {
				set(vc->get(i),r,dv);
			}
			return true;
		}
		else {
			while (r >= h) {
				for (int i = 0; i < w; i++) {
					a->push_back(dv);
				}
				h++;
			}
			vr->push_in(r);
			return true;
		}
		return false;
	}
};

Matrix<int> cross(Matrix<int>& M, Matrix<int>& N);//defined in util.cc 

//		TIMER 
class Timer {
	chrono::time_point<chrono::high_resolution_clock> startTime;
	chrono::time_point<chrono::high_resolution_clock> endTime;
	chrono::duration<double> elapsedTime;
	bool on = false;
	
	public:
	Timer();
	//~Timer();

	void start();
	void stop();
	int read();
	bool good();
};

#endif

