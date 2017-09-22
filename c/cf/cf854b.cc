#include <iostream>
/* CodeForces CF854B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int mx = 0;
	int mn = 0;
	if (0 < k && k < n) {
		mn = 1;
		while (k > 0 && n > k+2) {
			int dk = min(k, (n-k)/3);
			mx += 2*dk;
			k -= dk;
			n -= 3*dk;
		}
 		if (k > 0) {
			mx++;
			if (n-k>1)
				mx++;
		}
	}
	cout << mn << ' ' << mx << endl;
	return 0;
}
