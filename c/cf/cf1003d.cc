#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <valarray>
/* CodeForces CF1003D problem */
using namespace std;

constexpr int MAX = INT_MAX/2;

struct B {
	int n;
	valarray<int> cnt;
	B():n(MAX),cnt(0,33){};
	bool operator <(const B &b) const {
		return n < b.n;
	}
	B operator +(const B &b) const {
		B res(*this);
		res.n += b.n;
		res.cnt += b.cnt;
		return res;
	}
};

// cnt will be updated, bit is 1-based
int bestcnt(int bit, valarray<int> &cnt) {
	vector<vector<B>> bbcnt(bit+1, vector<B>(bit+1));
	for (int l2=1; l2<=bit; l2++) {
		for (int j=l2,c=1; j<=bit && c<=cnt[l2]; j++,c*=2) {
			bbcnt[l2][j].n = c;
			bbcnt[l2][j].cnt[l2] = c;
		}
	}
	for (int l2=2; l2<=bit; l2++) {
		for (int j=l2; j<=bit; j++) {
			if (bbcnt[l2][j].n > bbcnt[l2-2][j-1].n + bbcnt[l2-1][j-1].n)
				bbcnt[l2][j] = bbcnt[l2-2][j-1] + bbcnt[l2-1][j-1];
			if (bbcnt[l2][j].n > bbcnt[l2-1][j].n)
				bbcnt[l2][j] = bbcnt[l2-1][j];
		}
	}
#if 0
	for (int j=bit; j>0; j--) {
		for (int l2=1; l2<=bit; l2++)
			cerr << bbcnt[l2][j].n << ' ';
		cerr << '\n';
	}
#endif
	if (bbcnt[bit][bit].n < MAX) {
		cnt -= bbcnt[bit][bit].cnt;
#if 0
		for (int i=1; i<33; i++)
			cerr << cnt[i] << ' ';
		cerr << '\n';
#endif
		return bbcnt[bit][bit].n;
	} else {
		return -1;
	}
}

int main(int argc, char **argv) {
	int n, q;
	cin >> n >> q;
	valarray<int> cnt(33);
	while (n--) {
		int a;
		cin >> a;
		int l2 = log2(a);
		cnt[l2+1]++;
	}
	while (q--) {
		int a;
		cin >> a;
		bitset<32> ab(a);
		valarray<int> c(cnt);
		int s = 0;
		for (int i=31; i>=0; i--) {
			if (ab[i]) {
				int b = bestcnt(i+1, c);
				if (b < 1) {
					s = -1;
					break;
				} else {
					s += b;
				}
			}
		}
		cout << s << '\n';
	}
	return 0;
}
