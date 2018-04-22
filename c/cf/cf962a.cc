#include <iostream>
#include <algorithm>
#include <numeric>
/* CodeForces CF962A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int64_t total = accumulate(aa, aa+n, int64_t(0));
	int64_t sum = 0;
	int ans = -1;
	for (int i=0; i<n; i++) {
		sum += aa[i];
		if (sum*2 >= total) {
			ans = i+1;
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
