#include <iostream>
#include <cstring>
/* CodeForces CF1015E problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	struct D {
		int x;
		int l, r, u, d;
	} dd[n+2][m+2], ff[n+2][m+2], aa[n+2][m+2];
	memset(dd, 0, sizeof(dd));
	memset(ff, 0, sizeof(ff));
	memset(aa, 0, sizeof(aa));
	for (int i=1;i<=n;i++) {
		string s;
		cin >> s;
		for (int j=1;j<=m;j++)
			dd[i][j].x = (s[j-1]=='*');
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			dd[i][j].l = dd[i][j].x * (dd[i][j-1].l+1);
			dd[i][j].u = dd[i][j].x * (dd[i-1][j].u+1);
		}
	}
	for (int i=n;i>=1;i--) {
		for (int j=m;j>=1;j--) {
			dd[i][j].r = dd[i][j].x * (dd[i][j+1].r+1);
			dd[i][j].d = dd[i][j].x * (dd[i+1][j].d+1);
		}
	}
	for (int i=1;i<n;i++) {
		for (int j=1;j<m;j++) {
			int l = min(min(min(dd[i][j].l, dd[i][j].r), dd[i][j].u), dd[i][j].d);
			if (l > 1) {
				ff[i-l+1][j].d=2*l-1;
				ff[i][j-l+1].r=2*l-1;
				aa[i][j].x = 1;
				aa[i][j].l = l-1;
			}
		}
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=ff[i][j].r; k>0; k--,j++,k=max(k,ff[i][j].r))
				ff[i][j].x=1;
	for (int j=1;j<=m;j++)
		for (int i=1;i<=n;i++)
			for (int k=ff[i][j].d; k>0; k--,i++,k=max(k,ff[i][j].d))
				ff[i][j].x=1;
	int ans = true;
	int ans_sz = 0;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			ans &= (dd[i][j].x == ff[i][j].x);
			ans_sz += aa[i][j].x;
		}
	}
	if (ans) {
		cout << ans_sz << endl;
		for (int i=1;i<n;i++)
			for (int j=1;j<m;j++)
				if (aa[i][j].x != 0)
					cout << i << ' ' << j << ' ' << aa[i][j].l << '\n';
	} else {
		cout << -1 << endl;
	}
	return 0;
}
