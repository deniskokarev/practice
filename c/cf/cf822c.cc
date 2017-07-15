#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

/* CodeForces CF822C problem */
using namespace std;

struct V {
	int l, r;
	int64_t c;
	int len;
};

struct P {
	int p;
	int64_t mnc;
	bool operator<(const P &b) const {
		return p<b.p;
	}
};

#define dim(X) ((sizeof(X)/sizeof(X[0])))

int main(int argc, char **argv) {
	int n, x;
	cin >> n >> x;
	V vv[n];
	vector<vector<P>> rr(200001), ll(200001);
	for (auto &v:vv) {
		cin >> v.l >> v.r >> v.c;
		v.len = v.r-v.l+1;
		rr[v.len].push_back((P){v.r, v.c});
		ll[v.len].push_back((P){v.l, v.c});
	}
	for (auto &r:rr) {
		sort(r.begin(), r.end());
		for (int i=1; i<r.size(); i++)
			r[i].mnc = min(r[i].mnc, r[i-1].mnc);
	}
	for (auto &l:ll) {
		sort(l.begin(), l.end());
		for (int i=l.size()-2; i>=0; i--)
			l[i].mnc = min(l[i].mnc, l[i+1].mnc);
	}
	int64_t mn = LLONG_MAX;
	for (auto &v:vv) {
		if (v.len >= x)
			continue;
		int cl = x-v.len;
		P r = {v.r};
		auto it = upper_bound(ll[cl].begin(), ll[cl].end(), r);
		if (it != ll[cl].end())
			mn = min(mn, v.c+it->mnc);
		P l = {v.l-1};
		it = lower_bound(rr[cl].begin(), rr[cl].end(), l);
		if (it != rr[cl].end())
			mn = min(mn, v.c+it->mnc);
	}
	if (mn == LLONG_MAX)
		cout << -1;
	else
		cout << mn;
	cout << endl;
	return 0;
}
