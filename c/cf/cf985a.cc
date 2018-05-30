#include <iostream>
#include <algorithm>
/* CodeForces CF985A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int pp[n/2];
	for (auto &p:pp)
		cin >> p;
	sort(pp, pp+n/2);
	int f = 1;
	int ans = 0;
	for (auto &p:pp) {
		ans += abs(p-f);
		f += 2;
	}
	cout << ans << endl;
	return 0;
}
