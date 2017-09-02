/* ACMP 172 */
#include <iostream>

/* composition of http://e-maxx.ru/algo/big_integer */
#include <vector>
#include <cstdio>
#include <cassert>
struct lnum {
	const static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	lnum():a() {
	}
	lnum(const std::string &s):a() {
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
	void operator+=(const lnum &b) {
		int carry = 0;
		for (size_t i=0; i<std::max(a.size(),b.a.size()) || carry; ++i) {
			if (i == a.size())
				a.push_back (0);
			a[i] += carry + (i < b.a.size() ? b.a[i] : 0);
			carry = a[i] >= base;
			if (carry)  a[i] -= base;
		}
	}
	void operator-=(const lnum &b) {
		int carry = 0;
		for (size_t i=0; i<b.a.size() || carry; ++i) {
			a[i] -= carry + (i < b.a.size() ? b.a[i] : 0);
			carry = a[i] < 0;
			if (carry)  a[i] += base;
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
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
	void operator*=(const lnum &b) {
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
	/* @ returns this mod b */
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

using namespace std;

int main(int argc, char **argv) {
	string sn;
	cin >> sn;
	lnum n(sn);
	unsigned k;
	cin >> k;
	unsigned r = n /= k;
	cout << r << endl; 
	return 0;
}
