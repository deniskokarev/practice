/* ACMP 188 */

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
};

#include <iostream>

using namespace std;

/*
 * number of derrangements !n may be found recursively, similarly to factorial n!
 * n! = ((n-1)!+(n-2)!)*(n-1)
 * !n = (!(n-1)+!(n-2))*(n-1)
 */
int main(int argc, char **argv) {
	int cnt;
	cin >> cnt;
	lnum10 n1(0); // !(n-1)
	lnum10 n2(1); // !(n-2)
	lnum10 n(0);
	for (unsigned i=2; i<=cnt; i++) {
		n = n1;
		n += n2;
		n *= (i-1);
		n2 = n1;
		n1 = n;
	}
	cout << n.to_string() << endl;
	return 0;
}
