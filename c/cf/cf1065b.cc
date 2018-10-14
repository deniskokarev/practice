#include <iostream>
/* CodeForces CF1065B problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, m;
	cin >> n >> m;
	int64_t mn = max(0LL, n-2*m);
	int64_t f=0, t=n+1;
	while (f<t) {
		int64_t h = f+(t-f)/2;
		int64_t sz = h*(h-1)/2;
		if (sz < m)
			f = h+1;
		else
			t = h;
	}
	int64_t mx = n-f;
	cout << mn << ' ' << mx << '\n';
	return 0;
}
