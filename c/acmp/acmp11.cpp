/* ACMP 11 */
/* NB: just like 544 only with variable k and with long arithmetic */

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

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int k, n;
	cin >> k >> n;
	k++; // for simplicity
	vector<lnum10> cc(k);
	const lnum10 zero("0");
	fill(cc.begin(), cc.end(), zero);
	cc[0] = lnum10("1");
	for (int i=0; i<n; i++) {
		for (int j=1; j<k; j++)
			cc[(i+j)%k] += cc[i%k];
		cc[i%k] = zero;
	}
	cout << cc[n%k].to_string() << endl;
	return 0;
}
