#include <iostream>
#include <cstring>
/* CodeForces CF1006B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int aa[2001];
	int vv[n];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		aa[a]++;
		vv[i] = a;
	}
	int j = k;
	int ans = 0;
	for (int i=2000; i>=0; i--) {
		if (j == 0) {
			aa[i] = 0;
		} else {
			if (aa[i] < j) {
				ans += i*aa[i];
				j -= aa[i];
			} else if (aa[i] >= j) {
				ans += i*j;
				aa[i] = j;
				j = 0;
			}
		}
	}
	cout << ans << endl;
	int c = -1;
	j = k;
	for (int i=0; i<n; i++) {
		if (j == 1) {
			cout << n-i << ' ';
			break;
		}
		if (aa[vv[i]] > 0) {
			cout << i-c << ' ';
			c = i;
			aa[vv[i]]--;
			j--;
		}
	}
	cout << endl;
	return 0;
}
