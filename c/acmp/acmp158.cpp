/* ACMP 158 */

#include <vector>
#include <cstdio>
#include <cassert>
#include <string>

struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	lnum10(short n):a() {
		a.push_back(n);
	}
	std::string to_string() const {
		char buf[11];
		buf[10] = 0;
		snprintf(buf, 10, "%d", a.empty() ? 0 : a.back());
		std::string s(buf);
		for (int i=(int)a.size()-2; i>=0; --i) {
			snprintf(buf, 10, "%09d", a[i]);
			s.append(buf);
		}
		return s;
	}
	void operator*=(unsigned b) {
		assert(b<base);
		int carry = 0;
		for (size_t i=0; i<a.size() || carry; ++i) {
			if (i == a.size())
				a.push_back (0);
			long long cur = carry + a[i] * 1ll * b;
			a[i] = int (cur % base);
			carry = int (cur / base);
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
	}
	// @return *this mod b
	unsigned operator/=(unsigned b) {
		assert(b<base);
		unsigned carry = 0;
		for (int i=(int)a.size()-1; i>=0; --i) {
			long long cur = a[i] + carry * 1ll * base;
			a[i] = int (cur / b);
			carry = int (cur % b);
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
		return carry;
	}
};

#include <iostream>

using namespace std;

/**
 * Binomial coefficient (choose n, k)
 */
lnum10 choose(int n, int k) {
	lnum10 res(1);
	for (unsigned i=n,j=1; j<=k; i--,j++) {
		res *= i;
		res /= j;
	}
	return res;
}

/*
 * solution is based on a trivial problem of placing k cakes in n boxes
 * answer = choose(n+k-1, k)
 * hint: visualize the k cakes and (n-1) walls in the single row
 * the answer is number of places in (n-1)+k cells of k cakes
 */
int main(int argc, char **argv) {
	int x, k;
	cin >> x >> k;
	lnum10 ans = choose(x/5+k, k);
	cout << ans.to_string() << endl;
	return 0;
}
