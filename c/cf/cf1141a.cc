#include <iostream>
/* CodeForces CF1141A problem */
using namespace std;

int p23(int *pp, int n) {
	while (n%2==0 || n%3==0) {
		if (n%2==0) {
			n /= 2;
			pp[2]++;
		}
		if (n%3==0) {
			n /= 3;
			pp[3]++;
		}
	}
	return n;
}

int main(int argc, char **argv) {
	int64_t n, m;
	cin >> n >> m;
	int np[4] = {0,0,0,0};
	int mp[4] = {0,0,0,0};
	n = p23(np, n);
	m = p23(mp, m);
	int ans;
	if (m != n || np[2]>mp[2] || np[3]>mp[3])
		ans = -1;
	else
		ans = mp[2]-np[2] + mp[3]-np[3];
	cout << ans << endl;
	return 0;
}
