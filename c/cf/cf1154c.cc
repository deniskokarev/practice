#include <iostream>
/* CodeForces CF1154C problem */
using namespace std;

using uint = unsigned;

bool solve_r(uint m, int d, int64_t a, int64_t b, int64_t c) {
	int nn[7][3] = {
		{0, 0, 0},
		{1, 0, 0},
		{1, 1, 0},
		{1, 1, 1},
		{2, 1, 1},
		{2, 1, 2},
		{2, 2, 2}
	};
	int q = (m+d)/7;
	int64_t na = 3*q;
	int64_t nb = 2*q;
	int64_t nc = 2*q;
	int r = (m+d)%7;
	na += nn[r][0];
	nb += nn[r][1];
	nc += nn[r][2];
	na -= nn[d][0];
	nb -= nn[d][1];
	nc -= nn[d][2];
	return na <= a && nb <=b && nc <= c;
}

int main(int argc, char **argv) {
	int a, b, c;
	cin >> a >> b >> c;
	uint mx = 0;
	for (int d=0; d<7; d++) {
		uint f=0, t=2e9+1;
		while (f<t) {
			uint m = f+(t-f)/2;
			if (solve_r(m, d, a, b, c))
				f = m+1;
			else
				t = m;
		}
		mx = max(mx, f);
	}
	cout << mx-1 << endl;
	return 0;
}
