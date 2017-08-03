#include <iostream>
#include <map>
#include <climits>

/* CodeForces CF822C problem */
using namespace std;

struct V {
	int l, r;
	int64_t c;
	int len;
};

map<int,int64_t> ll[200001];

int main(int argc, char **argv) {
	int n, x;
	cin >> n >> x;
	V vv[n];
	for (auto &v:vv) {
		cin >> v.l >> v.r >> v.c;
		v.len = v.r-v.l+1;
		if (ll[v.len][v.l] == 0)
			ll[v.len][v.l] = v.c;
		else
			ll[v.len][v.l] = min(ll[v.len][v.l], v.c);
	}
	for (auto &l:ll) {
		auto pv = l.rbegin();
		if (pv != l.rend())
			for (auto nx=next(pv); nx!=l.rend(); pv=nx,++nx)
				nx->second = min(pv->second, nx->second);
	}
	int64_t mn = LLONG_MAX;
	for (auto &v:vv) {
		if (v.len >= x)
			continue;
		int cl = x-v.len;
		auto &ml = ll[cl];
		auto it = ml.upper_bound(v.r);
		if (it != ml.end())
			mn = min(mn, v.c + it->second);
	}
	if (mn == LLONG_MAX)
		cout << -1;
	else
		cout << mn;
	cout << endl;
	return 0;
}
