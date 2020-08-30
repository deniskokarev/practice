#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
/* CodeForces CF1393B problem */
using namespace std;

constexpr int MXL = 1e5+1;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> cnt(MXL);
	set<pair<int,int>> stat {{0,0},{0,0},{0,0},{0,0}}; // cnt,sz
	vector<set<pair<int,int>>::iterator> pos(MXL, stat.end());
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		auto p = pos[a];
		if (p != stat.end())
			stat.erase(p);
		cnt[a]++;
		stat.insert({cnt[a],a});
		pos[a] = stat.find({cnt[a],a});
	}
	int q;
	cin >> q;
	while (q--) {
		char s;
		int a;
		cin >> s >> a;
		auto p = pos[a];
		if (p != stat.end())
			stat.erase(p);
		cnt[a] += (s=='+');
		cnt[a] -= (s=='-');
		stat.insert({cnt[a],a});
		pos[a] = stat.find({cnt[a],a});
		auto lst = prev(stat.end());
		int nn[3];
		nn[0] = lst->first;
		--lst;
		nn[1] = lst->first;
		--lst;
		nn[2] = lst->first;
		bool ans = true;
		ans &= nn[0]>=4;
		nn[0] -= 4;
		sort(nn, nn+3);
		ans &= (nn[2]>=4) || (nn[2] >= 2 && nn[1] >= 2);
		static const char *YN[] {"NO", "YES"};
		cout << YN[ans] << '\n';
	}
	return 0;
}
