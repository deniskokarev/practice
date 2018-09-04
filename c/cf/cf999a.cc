#include <iostream>
/* CodeForces CF999A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int ans = 0;
	int i=0, j=n-1;
	while (aa[i]<=k && i<n) {
		ans++;
		i++;
	}
	while (aa[j]<=k && j>i) {
		ans++;
		j--;
	}
	cout << ans << endl;
	return 0;
}
