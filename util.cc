#include "util.h"

Timer::Timer() {
	startTime = chrono::high_resolution_clock::now();
	endTime = chrono::high_resolution_clock::now();
	on = false;
}

void Timer::start() {
	startTime = chrono::high_resolution_clock::now();
	on = true;
}

void Timer::stop() {
	if (on) {
		endTime = chrono::high_resolution_clock::now();
		on = false;
		elapsedTime = endTime - startTime;
		if (startTime > endTime) die("Error: Timer start after end.");
	}
}

int Timer::read() {
	chrono::duration<int,micro> r = chrono::duration_cast<chrono::microseconds>(elapsedTime);
	if (r.count() < 0) die("Error: Negative time interval.");
	return r.count();
}

bool Timer::good() {
	return on;
}

FIBTYPE fib(int n, Array<FIBTYPE>& cv) {
	FIBTYPE r = cv.get(n);
	if (r == 0) {
		if (n == 0) r = 0;
		else if (n == 1) r = 1;
		else r = fib(n-1,cv) + fib(n-2,cv);
	}
	cv.place(r,n);
	return r;
}

FIBTYPE fib(int n) {
	//cout << n << endl;
	FIBTYPE r;
	if (n == 0) r = 0;
	else if (n == 1) r = 1;
	else r = fib(n-1) + fib(n-2);
	return r;
}


Matrix<int> cross(Matrix<int>& M, Matrix<int>& N) {
	//cross product 
	if (M.get_width() != N.get_height()) die("Invalid Matrix sizes for multiply.");
	int m = M.get_height();
	int p = N.get_width();
	int n = M.get_width();
	Matrix<int> R(p,m,0);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < p; j++) {
			int t = 0;
			for (int k = 0; k < n; k++) {
				//cout << i << " " << j << " " << k << endl;
				t += M.get(k,i) * N.get(j,k);
			}
			R.set(j,i,t);
		}
	}
	return R;
}


