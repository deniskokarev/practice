#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
/* CodeForces CF1154B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	set<int> vv;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		vv.insert(a);
	}
	vector<int> aa(vv.size());
	copy(vv.begin(), vv.end(), aa.begin());
	if (aa.size() == 1) {
		cout << 0;
	} else if (aa.size() == 2) {
		int d = aa[1] - aa[0];
		if ((d&1) == 0)
			cout << d/2;
		else
			cout << d;
	} else if (aa.size() == 3 && aa[1]-aa[0] == aa[2]-aa[1]) {
		cout << aa[1] - aa[0];
	} else {
		cout << -1;
	}
	cout << endl;
	return 0;
}
