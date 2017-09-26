/* ACMP 401 */
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
	bool less(int pa, const lnum10 &b, int pb) const {
		if (a.size()-pa<b.a.size()-pb) {
			return true;
		} else if (a.size()-pa == b.a.size()-pb) {
			for (int i=(int)a.size()-1,j=(int)b.a.size()-1; i>=pa; i--,j--) {
				if (a[i] < b.a[j])
					return true;
				else if (a[i] > b.a[j])
					return false;
			}
		}
		return false;
	}
	bool operator<(const lnum10 &b) const {
		return less(0, b, 0);
	}
	bool operator==(const lnum10 &b) const {
		return a == b.a;
	}
	// long division
	// @return remainder *this mod b
	lnum10 operator /=(const lnum10 &b) {
		int pa = (int)a.size()-(int)b.a.size();
		lnum10::VEC q(pa+1); // quotient
		unsigned long long bhi = b.a.back();
		while (pa>=0) {
			while (a.size() > 1 && a.back() == 0) {
				q[pa] = 0;
				a.pop_back();
				pa--;
			}
			if (pa<0)
				break;
			// making an estimate instead of doing a binary search in entire [0..base) range
			unsigned long long rhi = a[pa+b.a.size()-1];
			if (a.size() > pa+b.a.size())
				rhi += ((unsigned long long)a[pa+b.a.size()])*base;
			unsigned f = unsigned(rhi/(bhi+1));
			unsigned t = unsigned((rhi+1)/bhi+1);
			if (t>base)
				t=base;
			while (f<t-1) {
				int m = f+(t-f)/2;
				lnum10 s = b;
				s *= m;
				if (s.less(0, *this, pa))
					f = m;
				else
					t = m;
			}
			if (t==base)
				t--;
			lnum10 s = b;
			s *= t;
			if (less(pa, s, 0)) {
				t--;
				s -= b;
			}
			q[pa] = t;
			sub(pa, s);
			pa--;
		}
		while (q.size() > 1 && q.back() == 0)
			q.pop_back();
		lnum10 r;
		std::swap(a, r.a);
		std::swap(a, q);
		return r;
	}
};


#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	int N, A, B;
	cin >> N >> A >> B;
	vector<vector<lnum10>> bb(2, vector<lnum10>(max(A, B)+1, 1));
	for (int n=1; n<=N; n++) {
		for (int ab=1; ab<=max(A,B); ab++) {
			bb[n&1][ab] = bb[n&1][ab-1];
			bb[n&1][ab] += bb[(n+1)&1][ab];
		}
	}
	lnum10 ans = bb[N&1][A];
	ans *= bb[N&1][B];
	cout << ans.to_string() << endl;
	return 0;
}
