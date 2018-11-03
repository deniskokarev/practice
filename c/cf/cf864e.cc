#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF864E problem */
using namespace std;

struct O {
	int id, t, d, p;
};

struct R {
	int p;
	int id;
	R *prev;
	bool operator<(const R &b) const {
		return p < b.p;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<O> oo(n);
	for (int i=0; i<n; i++) {
		O &o = oo[i];
		o.id = i;
		cin >> o.t >> o.d >> o.p;
	}
	sort(oo.begin(), oo.end(), [](const O &a, const O &b){return a.d < b.d;});
	int mxt = oo[n-1].d;
	vector<vector<R>> dp(mxt+1, vector<R>(n+1, R {0, -1, nullptr})); // (t,oi) -> (cost, prev t, prev oi)
	for (int t=1; t<=mxt; t++) {
		for (int oi=1; oi<=n; oi++) {
			const O &o = oo[oi-1];
			dp[t][oi] = max(dp[t][oi-1], dp[t-1][oi]);
			if (t < o.d && t >= o.t && dp[t-o.t][oi-1].p + o.p > dp[t][oi-1].p)
				dp[t][oi] = R {dp[t-o.t][oi-1].p + o.p, o.id, &dp[t-o.t][oi-1]};
		}
	}
	cout << dp[mxt][n].p << endl;
	vector<int> ids;
	if (dp[mxt][n].id >= 0) {
		ids.push_back(dp[mxt][n].id);
		for (R *nxt = dp[mxt][n].prev; nxt->id >= 0; nxt = nxt->prev)
			ids.push_back(nxt->id);
	}
	reverse(ids.begin(), ids.end());
	cout << ids.size() << endl;
	for (int i:ids)
		cout << i+1 << ' ';
	cout << endl;
	return 0;
}
