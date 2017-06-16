#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
/* CodeForces CF811B problem */
/* advanced version with O(N*log(N) + M*log(N)*log(N)) */
using namespace std;

int bcnt_lt(const vector<int> &v, int b, int e, int n) {
	int m;
	int f = b;
	int t = e;
	while (f<t) {
		m = f+(t-f)/2;
		if (v[m] < n)
			f = m+1;
		else
			t = m;
	}
	if (v[m]<n)
		return m-b+1;
	else
		return m-b;
}

int lt_count(vector<vector<int>> &msrt, int pos, int n) {
	int b = 0;
	int cnt = 0;
	int msz = msrt[0].size();
	for (int i=msrt.size()-1; i>=0; i--) {
		if (pos-b >= msz) {
			cnt += bcnt_lt(msrt[i], b, b+msz, n);
			b += msz;
		}
		msz /= 2;
	}
	return cnt;
}

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int pp[n];
	for (auto &p:pp)
		cin >> p;
	// keep all mergesort stages to get count of less than elements to the left in ~O(log(n)*log(n))
	int p2, p;
	for (p2=0,p=1; p<n; p2++,p<<=1);
	vector<vector<int>> msrt(p2+1, vector<int>(p));
	copy(pp, pp+n, &msrt[0][0]);
	fill(&msrt[0][n], &msrt[0][p], INT_MAX); // fill up the tail to simplify things
	int msz = 1;
	for (int i=1; i<p2+1; i++) {
		copy(&msrt[i-1][0], &msrt[i-1][p], &msrt[i][0]);
		for (int j=0; j<p/msz/2; j++)
			inplace_merge(&msrt[i][j*2*msz], &msrt[i][j*2*msz+msz], &msrt[i][(j+1)*2*msz]);
		msz *= 2;
	}
	for (int i=0; i<m; i++) {
		int l, r, x;
		cin >> l >> r >> x;
		int cr = lt_count(msrt, r, pp[x-1]);
		int cl = lt_count(msrt, l-1, pp[x-1]);
		int c = cr-cl;
		cout << ((c+l == x)?"Yes":"No") << endl;
	}
	return 0;
}
