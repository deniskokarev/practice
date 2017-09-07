/* ACMP 659 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
 
using namespace std;

// bitset::bitset performance is not exactly clear
// using our own O(n)
struct BITS_CNT {
	int n[1<<16];
	BITS_CNT() {
		fill(n, n+(1<<16), 0);
		for (int i=0; i<(1<<16); i++)
			for (int j=0; j<16; j++)
				n[i] += (i>>j)&1;
	}
};

union BITS {
	static const BITS_CNT bitcnt;
	uint32_t i;
	uint16_t bb[2];
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
	const int n;
	int mxf;
	BITS sel;
	BITS best;
};

void choose_team(int k, int f, SEL_CTX &sc) {
	if (k>0) {
		for (int i=f; i<sc.n; i++) {
			sc.sel.set(i);
			choose_team(k-1, i+1, sc);
			sc.sel.clear(i);
		}
	} else {
		int tt = 0;
		int ot = 0;
		for (int i=0; i<sc.n; i++) {
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
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--, v2--;
		int mn_v = min(v1, v2);
		int mx_v = max(v1, v2);
		ff[mn_v].set(mx_v);
	}
	SEL_CTX sc {ff, n, 0, {0}, {0}};
	choose_team(k, 0, sc);
	for (int p=0; p<n; p++)
		if (sc.best.isset(p))
			cout << p+1 << ' ';
	cout << endl;
	return 0;
}
