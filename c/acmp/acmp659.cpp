/* ACMP 659 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
 
using namespace std;

// bitset::bitset performance is not exactly clear
// using our own O(n)
struct BITS_CNT {
	int n[256];
	BITS_CNT() {
		fill(n, n+256, 0);
		for (int i=0; i<256; i++)
			for (int j=0; j<8; j++)
				n[i] += (i>>j)&1;
	}
};

union BITS {
	static const BITS_CNT bitcnt;
	uint64_t i;
	uint8_t bb[8];
	void set(int n) {
		i |= 1ULL<<n;
	};
	bool isset(int n) {
		return i & 1ULL<<n;
	};
	void clear(int n) {
		i &= ~(1ULL<<n);
	};
	int count() {
		int cnt = 0;
			for (auto b:bb)
				cnt += bitcnt.n[b];
			return cnt;
	};
};

const BITS_CNT BITS::bitcnt;

struct SEL_CTX {
	const vector<BITS> &ff;
	const vector<int> &ffcnt;
	const int m;
	int mxf;
	BITS sel;
	BITS best;
};

void choose_team(int k, int f, int t, SEL_CTX &sc) {
	if (k>0) {
		for (int i=f; i<t; i++) {
			sc.sel.set(i);
			choose_team(k-1, i+1, t, sc);
			sc.sel.clear(i);
		}
	} else {
		int tt = 0;
		int ot = 0;
		for (int i=0; i<t; i++) {
			if (sc.sel.isset(i)) {
				BITS b = sc.ff[i];
				b.i &= sc.sel.i;
				tt += b.count();
			} else {
				BITS b = sc.ff[i];
				b.i &= ~sc.sel.i;
				ot += b.count();
			}
		}
		int fr = tt+ot;
		if (fr >= sc.mxf) {
			sc.best = sc.sel;
			sc.mxf = fr;
		}
	}
}
 
int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	vector<BITS> ff(n);
	vector<int> ffcnt(n);
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--, v2--;
		int mn_v = min(v1, v2);
		int mx_v = max(v1, v2);
		ff[mn_v].set(mx_v);
	}
	for (int i=0; i<n; i++)
		ffcnt[i] = ff[i].count();
	SEL_CTX sc {ff, ffcnt, m, 0, {0}, {0}};
	choose_team(k, 0, n, sc);
	for (int p=0; p<n; p++)
		if (sc.best.isset(p))
			cout << p+1 << ' ';
	cout << endl;
	return 0;
}
