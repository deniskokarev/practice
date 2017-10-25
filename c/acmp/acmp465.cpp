/* ACMP 465 */

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
};

#include <iostream>

using namespace std;

/* no 2 zeros (or 2 ones together) is known to be a fibbonaci sequence */
int main(int argc, char **argv) {
	int n;
	cin >> n;
	lnum10 f1(1); // fib - 1
	lnum10 f2(1); // fib - 2
	for (int i=0; i<n; i++) {
		lnum10 f(f1);
		f += f2;
		f2 = f1;
		f1 = f;
	}
	cout << f1.to_string() << endl;
	return 0;
}
