#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/* CodeForces CF757C problem */
using namespace std;

constexpr uint64_t MOD = 1e9+7;

struct FactMod {
	vector<uint64_t> f;
	FactMod(uint32_t m) {
		f.resize(m+1);
		f[0] = f[1] = 1;
		for (uint64_t i=2; i<=m; i++)
			f[i] = (f[i-1] * i)%MOD;
	}
	uint64_t operator()(uint32_t n) {
		return f.at(n);
	}
};

struct SC {
	int sch;
	int cnt;
	bool operator<(const SC &b) const {
		if (sch < b.sch) {
			return false;
		} else if (sch == b.sch) {
			return cnt < b.cnt;
		} else {
			return true;
		}
	}
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	FactMod fact(m);
	vector<map<int, int>> ss(n);	// school type->cnt
	map<int, vector<SC>> tstat; // type -> (sch,cnt)*
	vector<bool> tpres(m+1, false); // missing types
	int nsch = 0;
	for (auto &s:ss) {
		int g;
		for (cin >> g; g>0; g--) {
			int m;
			cin >> m;
			s[m]++;
			tpres[m] = true;
		}
		for (auto &e:s)
			tstat[e.first].push_back({nsch, e.second});
		nsch++;
	}
	map<vector<SC>, vector<int>> itstat; // inverted tstat: (sch,cnt),(sch,cnt),(sch,cnt) -> type*
	for (auto &e:tstat)
		itstat[e.second].push_back(e.first);
	uint64_t sum = 1;
	for (auto &e:itstat)
		sum = sum * fact(e.second.size()) % MOD;
	// count all missing types separately
	int tmiss = 0;
	for (int t=0; t<m; t++)
		if (!tpres[t+1])
			tmiss++;
	sum = sum * fact(tmiss) % MOD;
	cout << sum << endl;
	return 0;
}
