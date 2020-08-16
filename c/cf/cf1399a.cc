#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> aa(n);
		for (auto &a:aa)
			cin >> a;
		sort(aa.begin(), aa.end());
		bool ans = true;
		for (int i=1; i<n; i++)
			ans &= (aa[i] < aa[i-1]+2);
		cout << (ans?"YES\n":"NO\n");
	}
	return 0;
}
