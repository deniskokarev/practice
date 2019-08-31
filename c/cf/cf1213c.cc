#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1213C problem */
using namespace std;

int main(int argc, char **argv) {
	int q;
	cin >> q;
	while (q--) {
		int64_t n, m;
		cin >> n >> m;
		int64_t ans = 0;
		for (int i=1; i<10; i++) {
			if (n >= m*i) {
				int d = m*i%10;
				ans += ((n-(m*i))/m/10+1)*d;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
