#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <mutex>
#include <condition_variable>

/* https://leetcode.com/problems/print-zero-even-odd/ */
using namespace std;

class ZeroEvenOdd {
	enum {
		STATE_Z,
		STATE_O,
		STATE_E
	};
	static constexpr int FA_SZ = 4;
	const static int fa[FA_SZ]; // finite automata states
	int n;
	mutex mx;
	condition_variable cv;
	volatile int epoch;
public:
	ZeroEvenOdd(int n):n(n),mx(),cv(),epoch(0) {
	}
	void zero(function<void(int)> printNumber) {
		for (int i=0; i<n; i++) {
			unique_lock<mutex> lock(mx);
			while (fa[epoch % FA_SZ] != STATE_Z)
				cv.wait(lock);
			printNumber(0);
			epoch++;
			cv.notify_all();
		}
	}
	void odd(function<void(int)> printNumber) {
		for (int i=0; 2*i+1<=n; i++) {
			unique_lock<mutex> lock(mx);
			while (fa[epoch % FA_SZ] != STATE_O)
				cv.wait(lock);
			printNumber(2*i+1);
			epoch++;
			cv.notify_all();
		}
	}
	void even(function<void(int)> printNumber) {
		for (int i=0; 2*i+2<=n; i++) {
			unique_lock<mutex> lock(mx);
			while (fa[epoch % FA_SZ] != STATE_E)
				cv.wait(lock);
			printNumber(2*i+2);
			epoch++;
			cv.notify_all();
		}
	}
};

const int ZeroEvenOdd::fa[ZeroEvenOdd::FA_SZ] = {
	ZeroEvenOdd::STATE_Z,
	ZeroEvenOdd::STATE_O,
	ZeroEvenOdd::STATE_Z,
	ZeroEvenOdd::STATE_E
};

void printNumber(int x) {
	cout << x << ' ';
}

int main(int argc, char **argv) {
	ZeroEvenOdd barrier(10);
	thread zt([&barrier](){barrier.zero(printNumber);});
	thread ot([&barrier](){barrier.odd(printNumber);});
	thread et([&barrier](){barrier.even(printNumber);});
	zt.join();
	ot.join();
	et.join();
	cout << "\n";
	return 0;
}
