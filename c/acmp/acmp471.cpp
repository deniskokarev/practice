/* ACMP 471 */
#include <iostream>

using namespace std;

/* composition of http://e-maxx.ru/algo/big_integer */
#include <vector>
#include <cstdio>
#include <cassert>
#include <string>

struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	// NB!: this is not == 0
	lnum10():a() {
	}
	lnum10(short n):a() {
		a.push_back(n);
	}
	lnum10(const std::string &s):a() {
		for (int i=(int)s.length(); i>0; i-=9)
			if (i < 9)
				a.push_back(atoi(s.substr (0, i).c_str()));
			else
				a.push_back(atoi(s.substr (i-9, 9).c_str()));
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
};

// cell->(n, nxt1, nxt2, nxt3)
const static int nn[10][4] = {
	{2, 4, 6},
	{2, 6, 8},
	{2, 7, 9},
	{2, 4, 8},
	{3, 0, 3, 9},
	{0},
	{3, 0, 1, 7},
	{2, 2, 6},
	{2, 1, 3},
	{2, 2, 4}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	lnum10 cc[2][10] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	for (int i=1; i<n; i++) {
		for (int j=0; j<10; j++) {
			cc[i&1][j] = 0;
			for (int k=1; k<=nn[j][0]; k++)
				cc[i&1][j] += cc[(i+1)&1][nn[j][k]];
		}
	}
	int r = (n+1)&1;
	lnum10 s(0);
	for (int i=0; i<10; i++)
		s += cc[r][i];
	cout << s.to_string() << endl;
	return 0;
}
