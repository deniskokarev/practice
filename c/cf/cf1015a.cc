#include <iostream>
#include <vector>
/* CodeForces CF1015A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<char> xx(m+1, 0);
	while (n--) {
		int l, r;
		cin >> l >> r;
		for (int i=l; i<=r; i++)
			xx[i] = 1;
	}
	int ans = 0;
	for (int i=1;i<=m;i++)
		ans += (xx[i]==0);
	cout << ans << endl;
	for (int i=1;i<=m;i++)
		if (xx[i]==0)
			cout << i << ' ';
	cout << endl;
	return 0;
}
