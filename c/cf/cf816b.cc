#include <iostream>
#include <algorithm>

/* CodeForces CF816B problem */
using namespace std;

struct IV {
	int p;
	int dir; // +/-1
	bool operator<(const IV &b) const {
		return p<b.p;
	}
};

#define dim(X)	((sizeof(X)/sizeof(X[0])))
				 
int nn[200002];
IV iv[400002];
int nc[200003];

int main(int argc, char **argv) {
	int n, k, q;
	cin >> n >> k >> q;
	int niv = 0;
	iv[niv++] = {0, 0};
	for (int i=0; i<n; i++) {
		int l, r;
		cin >> l >> r;
		iv[niv++] = {l, +1};
		iv[niv++] = {r+1, -1};
	}
	iv[niv++] = {200001, 0};
	sort(iv, iv+niv);
	int cnt = 0;
	for (int i=1; i<niv;) {
		int j;
		for (int m=iv[i-1].p; m<=iv[i].p; m++)
			nn[m] = cnt;
		for (j=i; j<niv && iv[i].p == iv[j].p; j++)
			cnt += iv[j].dir;
		i = j;
	}
	nc[0] = 0;
	for (int i=1; i<=dim(nn); i++) {
		nc[i] = nc[i-1];
		if (nn[i-1]>=k)
			nc[i]++;
	}
#if 0
	for (int i=90; i<101; i++)
		cerr << nn[i] << ' ';
	cerr << endl;
	for (int i=90; i<101; i++)
		cerr << nc[i] << ' ';
	cerr << endl;
#endif
	for (int i=0; i<q; i++) {
		int l, r;
		cin >> l >> r;
		cout << nc[r+1]-nc[l] <<endl;
	}
	return 0;
}
