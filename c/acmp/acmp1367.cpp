/* ACMP 1367 */

#include <vector>
#include <cassert>
#include <string>

// need long arithmetic to find x%k
struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	lnum10(const std::string &s):a() {
		for (int i=(int)s.length(); i>0; i-=9)
			if (i < 9)
				a.push_back(atoi(s.substr (0, i).c_str()));
			else
				a.push_back(atoi(s.substr (i-9, 9).c_str()));
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
#include <queue>
#include <algorithm>

using namespace std;

struct D {
	bool seen;
	unsigned cd; // current digit
	unsigned pr; // prev remainder
};

int main(int argc, char **argv) {
	string xs;
	cin >> xs;
	lnum10 x(xs);
	unsigned k;
	cin >> k;
	int dsz;
	cin >> dsz;
	unsigned dd[dsz];
	for (auto &d:dd)
		cin >> d;
	sort(dd, dd+dsz);
	unsigned rem = (x/=k);
	if (rem == 0) {
		cout << xs << endl;
	} else {
		// we'll just "walk" all possible remainders in BFS fashion
		D dist[k];
		fill(dist, dist+k, D {false, UINT_MAX, UINT_MAX});
		dist[rem] = D {true, UINT_MAX, UINT_MAX};
		queue<unsigned> qq;
		qq.push(rem);
		while (!qq.empty()) {
			unsigned rem = qq.front();
			for (auto d:dd) {
				unsigned nrem = (rem*10+d)%k;
				if (!dist[nrem].seen) {
					dist[nrem] = D {true, d, rem};
					qq.push(nrem);
				}
			}
			qq.pop();
		}
		if (!dist[0].seen) {
			cout << -1 << endl;
		} else {
			string s;
			for (unsigned r=0; dist[r].cd < UINT_MAX; r=dist[r].pr)
				s.push_back(dist[r].cd+'0');
			reverse(s.begin(), s.end());
			cout << xs << s << endl;
		}
	}
	return 0;
}
