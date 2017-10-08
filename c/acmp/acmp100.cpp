/* ACMP 100 */

/* long arithmetic from http://e-maxx.ru/algo/big_integer */
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
	void operator+=(const lnum10 &b) {
		int carry = 0;
		for (size_t i=0; i<std::max(a.size(),b.a.size()) || carry; ++i) {
			if (i == a.size())
				a.push_back (0);
			a[i] += carry + (i < b.a.size() ? b.a[i] : 0);
			carry = a[i] >= base;
			if (carry)  a[i] -= base;
		}
	}
	void sub(int pa, const lnum10 &b) {
		assert(a.size()-pa>=b.a.size());
		int carry = 0;
		for (size_t i=0; i<b.a.size() || carry; ++i) {
			a[i+pa] -= carry + (i < b.a.size() ? b.a[i] : 0);
			carry = a[i+pa] < 0;
			if (carry)  a[i+pa] += base;
		}
		while (a.size() > pa+1 && a.back() == 0)
			a.pop_back();
	}
	void operator-=(const lnum10 &b) {
		sub(0, b);
	}
	void operator*=(const lnum10 &b) {
		VEC c(a.size()+b.a.size());
		for (size_t i=0; i<a.size(); ++i) {
			for (int j=0, carry=0; j<(int)b.a.size() || carry; ++j) {
				long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.a.size() ? b.a[j] : 0) + carry;
				c[i+j] = int (cur % base);
				carry = int (cur / base);
			}
		}
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();
		a = c;
	}
};

#include <iostream>
#include <cassert>

using namespace std;

/*
 * f[n,s] - number of digit permutations of
 * n - length of the half
 * s - sum of digits in that half
 * f[n,s] = f[n-1,s]+f[n-1,s-1]+..f[n-1,0] // number <= 10, where last 10 go down 9,8,7.. elements
 * f[1,0] = 1
 * f[1,1] = 1
 * ...
 * f[1,9] = 1
 */
int main(int argc, char **argv) {
	int nd;
	cin >> nd;
	assert((nd&1) == 0); // we don't expect odd number of digits (otherwise just *10 the result)
	int n = nd/2;
	assert(n < 51);
	vector<vector<lnum10>> f(2, vector<lnum10>(n*9+1, lnum10(1)));
	int h = 10;
	for (int i=1; i<n; i++) {
		int cur = i&1;
		int prev = (i+1)&1;
		int j = 0;
		lnum10 s(0); // aggregation window of f[n-1][s]+f[n-1][s-1]... (of upto 10 elements)
		while (j<10) {
			s += f[prev][j];
			f[cur][j] = s;
			j++;
		}
		while (j<h) {
			s += f[prev][j];
			s -= f[prev][j-10];
			f[cur][j] = s;
			j++;
		}
		h += 9;
		while (j<h) {
			s -= f[prev][j-10];
			f[cur][j] = s;
			j++;
		}
	}
	int cur = (n+1)&1;
	lnum10 ss(0);
	for (int i=0; i<n*9+1; i++) {
		lnum10 sq(f[cur][i]);
		sq *= sq;
		ss += sq;
	}
	cout << ss.to_string() << endl;
	return 0;
}
