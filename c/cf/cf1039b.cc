#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>
/* CodeForces CF139B problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, k;
	cin >> n >> k;
	bool ans = false;
	mt19937 rnd(0);
	string s;
	int cnt = 0;
	int64_t f = 1, t = n+1;
	if (k == 0) {
		while (f<t) {
			int64_t m=f+(t-f)/2;
			cnt++;
			cout << f << " " << m << endl;
			cin >> s;
			if (s == "Yes")
				t = m;
			else
				f = m+1;
		}
		cnt++;
		cout << f << " " << f << endl;
		cin >> s;
		assert(s == "Yes");
	} else {
		while (!ans) {
			while (f+5*k<t) {
				int64_t m=f+(t-f)/2;
				cnt++;
				cout << f << " " << m << endl;
				cin >> s;
				if (s == "Yes") {
					f = max(1LL, f-k);
					t = min(n+1, m+k+1);
				} else {
					f = max(1LL, m-k+1);
					t = min(n+1, t+k);
				}
			}
			cnt++;
			int64_t pos = f+(rnd()%(t-f));
			cout << pos << " " << pos << endl;
			cin >> s;
			ans = (s == "Yes");
			f = max(1LL, f-k-1);
			t = min(n+1, t+k+1);
		}
	}
	return 0;
}
