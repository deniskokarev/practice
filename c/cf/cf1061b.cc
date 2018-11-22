#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1061B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<int> aa(n);
	for (auto &a:aa)
		cin >> a;
	sort(aa.begin(), aa.end(), greater<int>());
	vector<int> bb(aa);
	int64_t ans = 0;
	for (int i=0; i<n-1; i++)
		if (bb[i+1] > 0 && bb[i] <= bb[i+1])
			bb[i+1] = max(1, bb[i]-1);
#if 0
	for (auto b:bb)
		cerr << b << ' ';
	cerr << endl;
#endif
	for (int i=0; i<n; i++)
		ans += aa[i]-bb[i];
	for (int i=0; i<n-1; i++)
		if (bb[i] > 1)
			ans += bb[i+1];
	cout << ans << endl;
	return 0;
}
