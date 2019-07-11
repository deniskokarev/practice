#include <iostream>
#include <numeric>
#include <algorithm>
/* CodeForces CF1141E problem */
using namespace std;

int fnd(int64_t *ss, int n, int64_t h) {
	for (int i=0; i<=n; i++)
		if (h+ss[i] <= 0)
			return i;
	return -1;
}

int main(int argc, char **argv) {
	int64_t h;
	int n;
	cin >> h >> n;
	int dd[n];
	for (auto &d:dd)
		cin >> d;
	int64_t ss[n+1];
	ss[0] = 0;
	for (int i=0; i<n; i++)
		ss[i+1] = ss[i]+dd[i];
	int64_t f = 0;
	if (ss[n] < 0) {
		int64_t t = -h/ss[n]+1;
		while (f<t) {
			int64_t m = f+(t-f)/2;
			int64_t hs = h+ss[n]*m;
			if (fnd(ss, n, hs) < 0)
				f = m+1;
			else
				t = m;
		}
	}
	int64_t ans = f*n+fnd(ss, n, h+ss[n]*f);
	//cerr << "f=" << f << " ans=" << ans << endl;
	if (ans >= 0)
		cout << ans << endl;
	else
		cout << -1 << endl;
	return 0;
}
