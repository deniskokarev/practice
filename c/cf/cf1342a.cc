#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1342A problem */
using namespace std;

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int64_t x, y;
		int64_t a, b;
		int64_t ans;
		cin >> x >> y >> a >> b;
		if (x*y > 0) {
			x = abs(x);
			y = abs(y);
			if (x>y)
				swap(x, y);
			int64_t a1 = (y-x)*a + x*b;
			int64_t a2 = x*a + y*a;
			ans = min({a1,a2});
		} else {
			if (x>y)
				swap(x,y);
			int64_t a1 = abs(x)*a + abs(y)*a;
			int64_t a2 = abs(x)*b + abs(y-x)*a;
			int64_t a3 = abs(y)*b + abs(y-x)*a;
			ans = min({a1,a2,a3});
		}
		cout << ans << "\n";
	}
	return 0;
}
