#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
/* https://leetcode.com/contest/weekly-contest-155/problems/ugly-number-iii/ */
using namespace std;

/*
 * BEWARE!!! leetcode uses C++17 with std::gcd() anc std::lcm()
 */
class Solution {
	/**
	 * GCD(a, b) - greatest common divisor
	 */
	static uint64_t gcd(uint64_t a, uint64_t b) {
		while (b > 0) {
			uint64_t temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}
	/**
	 * LCM(a, b) - least common multiple
	 */
	static uint64_t lcm(uint64_t a, uint64_t b) {
		return a * (b / gcd(a, b));
	}
public:
	static int nthUglyNumber(int n, int a, int b, int c) {
		uint64_t lab = lcm(a,b);
		uint64_t lac = lcm(a,c);
		uint64_t lbc = lcm(b,c);
		uint64_t labc = lcm(lab, lbc);
		uint64_t f=1,t=ULLONG_MAX;
		while (f<t) {
			uint64_t m = f+(t-f)/2;
			uint64_t cnt = m/a+m/b+m/c-m/lab-m/lac-m/lbc+m/labc;
			//cerr << "m=" << m << " cnt=" << cnt << endl;
			if (cnt < uint64_t(n))
				f = m+1;
			else
				t = m;
		}
		return f;
	}
};

int main(int argc, char **argv) {
	cout << Solution::nthUglyNumber(3, 2, 3, 5) << endl;
	cout << Solution::nthUglyNumber(4, 2, 3, 4) << endl;
	cout << Solution::nthUglyNumber(5, 2, 11, 13) << endl;
	cout << Solution::nthUglyNumber(1000000000, 2, 217983653, 336916467) << endl;
	return 0;
}
