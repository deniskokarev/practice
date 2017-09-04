/* ACMP 146 */

#include <iostream>
#include <algorithm>

using namespace std;

/* composition of http://e-maxx.ru/algo/big_integer */
#include <vector>
#include <cstdio>
#include <cassert>
struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	// NB: this is not == 0
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
	void operator-=(const lnum10 &b) {
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
	bool operator<(const lnum10 &b) const {
		if (a.size()<b.a.size()) {
			return true;
		} else if (a.size() == b.a.size()) {
			for (int i=(int)a.size()-1; i>=0; i--) {
				if (a[i] < b.a[i])
					return true;
				else if (a[i] > b.a[i])
					return false;
			}
		}
		return false;
	}
	bool operator==(const lnum10 &b) const {
		return a == b.a;
	}
	// @return *this mod b
	lnum10 operator /=(const lnum10 &b) {
		if (*this < b) {
			lnum10 r(*this);
			a.resize(0);
			return r;
		} else {
			lnum10 r(*this);
			lnum10 q;
			int app = (int)r.a.size()-(int)b.a.size();
			if (r.a.back() < b.a.back())
				app--;
			while (app >= 0) {
				lnum10 s;
				for (int i=0; i<app; i++)
					s.a.push_back(0);
				std::copy(b.a.begin(), b.a.end(), std::back_inserter(s.a));
				unsigned f=0, t=base;
				lnum10 mn;
				while (f<t) {
					unsigned m = f+(t-f)/2;
					mn = s;
					mn *= m;
					if (mn<r)
						f = m+1;
					else
						t = m;
				}
				if (t >= base) {
					t--;
				} else {
					mn = s;
					mn *= t;
					if (r<mn) {
						t--;
						mn -= s;
					}
				}
				q.a.push_back(t);
				r -= mn;
				app--;
			}
			reverse(q.a.begin(), q.a.end());
			a = q.a;
			while (a.size() > 1 && a.back() == 0)
				a.pop_back();
			return r;
		}
	}
};

int main(int argc, char **argv) {
	string ss;
	cin >> ss;
	lnum10 s(ss);
	string sx = "1"+string((ss.length()+1)/2, '0');
	lnum10 x(sx);
	lnum10 d;
	const lnum10 zero("0");
	const lnum10 one("1");
	lnum10 a("4"), b("2");
	do {
		x -= d;
		lnum10 s1(s);
		s1 /= x;
		d = x;
		d -= s1;
		d /= 2;
		//cerr << "x: " << x.to_string() << " d: " << d.to_string() << " s/x: " << s1.to_string() << endl;
	} while(zero<d);
	lnum10 sq(x);
	sq *= sq;
	if (s<sq)
		x -= one;
	cout << x.to_string() << endl;
	return 0;
}
