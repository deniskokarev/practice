#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1203B problem */
using namespace std;

int main(int argc, char **argv) {
	int q;
	cin >> q;
	while (q--) {
		int n;
		cin >> n;
		vector<int> aa(4*n);
		for (auto &a:aa)
			cin >> a;
		sort(aa.begin(), aa.end());
		int lp = 1, rp = 4*n-1;
		int ans = true;
		ans &= (aa[lp-1] == aa[lp]);
		ans &= (aa[rp-1] == aa[rp]);
		int ta = aa[lp]*aa[rp];
		lp += 2;
		rp -= 2;
		while (lp+1 < rp) {
			ans &= (aa[lp-1] == aa[lp]);
			ans &= (aa[rp-1] == aa[rp]);
			ans &= (aa[lp]*aa[rp] == ta);
			lp += 2;
			rp -= 2;
		}
		cout << (ans?"YES":"NO") << '\n';
	}
	return 0;
}
