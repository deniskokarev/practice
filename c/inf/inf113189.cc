#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
/* informatics 113189 */
using namespace std;

struct C {
	int a, c;
};

constexpr int INF = INT_MAX/2;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	C cc[n];
	for (auto &c:cc)
		cin >> c.a;
	for (auto &c:cc)
		cin >> c.c;
	sort(cc, cc+n, [](const C &a, const C &b){return a.c < b.c;});
	vector<int> xx(n);
	for (int i=0; i<n; i++)
		xx[i] = cc[i].c;
	// dp[y][n] -> c, where y - candy_no, n - number of candies we can take, c - allowed max_c
	vector<vector<int>> dp(n+1, vector<int>(n+1));
	fill(dp[0].begin(), dp[0].end(), INF);
	dp[0][0] = 0;
	for (int y=1; y<=n; y++) {
		dp[y] = dp[y-1];
		auto &c = cc[y-1];
		for (int cnt=1; cnt<=n; cnt++)
			if (dp[y-1][cnt-1]+c.a <= c.c)
				dp[y][cnt] = min(dp[y][cnt], dp[y-1][cnt-1]+c.a);
	}
	int ans = 0;
	for (int i=n; i>=0; i--) {
		if (dp[n][i]<INF) {
			ans = i;
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
