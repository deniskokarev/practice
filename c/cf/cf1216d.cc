#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1216D problem */
using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	int mna = INT_MAX;
	for (auto &a:aa) {
		cin >> a;
		mna = min(mna, a);
	}
	vector<int> tt;
	for (auto &a:aa)
		if (a > mna)
			tt.push_back(a-mna);
	if (tt.size()>0) {
		int z = tt[0];
		for (int i=1; i<tt.size(); i++)
			z = gcd(z, tt[i]);
		cerr << "z=" << z << endl;
		int64_t mxa = INT_MIN;
		int64_t sm = 0;
		for (auto t:tt) {
			mxa = max(mxa, int64_t(t));
			sm += t;
		}
		int64_t y = (mxa*n - sm)/z;
		cout << y << ' ' << z << endl;
	} else {
		cout << n << ' ' << 0 << endl;
	}
	return 0;
}
