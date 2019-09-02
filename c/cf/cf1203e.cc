#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1203E problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	for (auto &a:aa)
		cin >> a;
	sort(aa.begin(), aa.end());
	vector<int> oo(150000+2);
	for (auto a:aa) {
		if (!oo[a-1] && (a-1)>0)
			oo[a-1] = 1;
		else if (!oo[a])
			oo[a] = 1;
		else if (!oo[a+1])
			oo[a+1] = 1;
	}
	int ans = accumulate(oo.begin(), oo.end(), 0);
	cout << ans << endl;
	return 0;
}
