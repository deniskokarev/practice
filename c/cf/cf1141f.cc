#include <iostream>
#include <vector>
#include <list>
#include <map>
/* CodeForces CF1141F problem */
using namespace std;

struct A {
	int64_t k;
	int j, i;
	int prev;
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t aa[n+1];
	aa[0] = 0;
	for (int i=1; i<=n; i++) {
		cin >> aa[i];
		aa[i] += aa[i-1];
	}
	vector<A> ans;
	ans.push_back(A {0, -1, -1, -1});
	map<int,map<int,int>> sm_ans; // sum -> pos -> (k,A)
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=i; j++) {
			int64_t sm = aa[i]-aa[j-1];
			if (sm_ans.find(sm) == sm_ans.end())
				sm_ans[sm][-1] = 0;
		    auto &p2a = sm_ans[sm];
			auto fnd = prev(p2a.lower_bound(j));
			auto lst = prev(p2a.end());
			if (fnd->first < j && ans[fnd->second].k+1 > ans[lst->second].k) {
				p2a[i] = ans.size();
				ans.push_back(A{ans[fnd->second].k+1, j, i, fnd->second});
			}
		}
	}
	int k = 0;
	int id = -1;
	for (auto &s:sm_ans) {
		auto &p2a = s.second;
		auto l = prev(p2a.end());
		if (ans[l->second].k > k) {
			k = ans[l->second].k;
			id = l->second;
		}
	}
	cout << k << endl;
	while (id > 0) {
		cout << ans[id].j << ' ' << ans[id].i << '\n';
		id = ans[id].prev;
	}
	return 0;
}
