#include <iostream>
#include <vector>
#include <map>

/* CodeForces CF757C problem */
using namespace std;

constexpr uint64_t MOD = 1e9+7;

struct FactMod {
	vector<uint64_t> f;
	FactMod(uint32_t m) {
		f.resize(m+1);
		f[0] = f[1] = 1;
		for (uint32_t i=2; i<=m; i++)
			f[i] = (f[i-1] * i) % MOD;
	}
	uint64_t operator()(uint32_t n) {
		return f.at(n);
	}
};

struct SC {
	int sch;
	int cnt;
	bool operator<(const SC &b) const {
		return (sch < b.sch) || ((sch == b.sch) && (cnt < b.cnt));
	}
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<SC>> tstat(m+1); // type -> (sch,cnt)*
	for (int i=0; i<n; i++) {
		map<int,int> s; // type->cnt
		int g;
		for (cin >> g; g>0; g--) {
			int t;
			cin >> t;
			s[t]++;
		}
		for (auto &e:s)
			tstat[e.first].push_back({i, e.second});
		s.clear();
	}
	map<vector<SC>, vector<int>> itstat; // inverted tstat: (sch,cnt),(sch,cnt),(sch,cnt) -> type*
	for (int i=1; i<=m; i++)
		if (tstat[i].size() > 0)
			itstat[tstat[i]].push_back(i);
	FactMod fact(m);
	uint64_t sum = 1;
	for (auto &e:itstat)
		sum = sum * fact(e.second.size()) % MOD;
	// count all missing types separately
	int tmiss = 0;
	for (int i=1; i<=m; i++)
		if (tstat[i].size() < 1)
			tmiss++;
	sum = sum * fact(tmiss) % MOD;
	cout << sum << endl;
	return 0;
}
