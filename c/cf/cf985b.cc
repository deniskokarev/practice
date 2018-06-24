#include <iostream>
#include <cstdio>
#include <algorithm>
/* CodeForces CF985B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int cnt[m];
	fill(cnt, cnt+m, 0);
	char mm[n][m+1];
	for (int r=0; r<n; r++) {
		scanf(" %s", mm[r]);
		for (int c=0; c<m; c++)
			cnt[c] += mm[r][c]-'0';
	}
	int ans = false;
	for (int r=0; r<n && !ans; r++) {
		ans = true;
		for (int c=0; c<m; c++)
			ans &= (mm[r][c] != '1' || cnt[c] > 1);
	}
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
