#include <iostream>
/* CodeForces http://codeforces.com/group/DE717HedLL/contest/213027/problem/C problem */
using namespace std;

const int64_t mod = 1e9+7;

enum {
	A, B, C, D, SZ
};

struct MM {
	int64_t mm[SZ][SZ];
};

const MM o = {{
	{0, 1, 1, 1},
	{1, 0, 1, 1},
	{1, 1, 0, 1},
	{1, 1, 1, 0}
}};

void npaths(int n, MM &mm) {
	if (n < 2) {
		mm = o;
	} else {
		MM l;
		const MM *r;
		if (n%2 == 0) {
			npaths(n/2, l);
			r = &l;
		} else {
			npaths(n-1, l);
			r = &o;
		}
		for (int i=0; i<SZ; i++) {
			for (int j=0; j<SZ; j++) {
				mm.mm[i][j] = 0;
				for (int k=0; k<SZ; k++)
					mm.mm[i][j] += l.mm[i][k] * r->mm[k][j];
				mm.mm[i][j] %= mod;
			}
		}
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	MM ans;
	npaths(n, ans);
	cout << ans.mm[A][A] << endl;
	return 0;
}
