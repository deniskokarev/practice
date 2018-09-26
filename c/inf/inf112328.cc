#include <iostream>
#include <vector>
#include <climits>
/* ROI 2014E */

using namespace std;

int main(int argc, char **argv) {
	int n;
	std::cin >> n;
	int64_t s = 0;
	// top 2 deltas in each category
	struct D {
		int delta;
		int pos;
	} mx[2][2] {{{INT_MIN, 0}, {INT_MIN, 0}}, {{INT_MIN, 0}, {INT_MIN, 0}}}; // [cat][top] -> (dv,i)
	for (int i=1; i<=n; i++) {
		int a, b[2];
		cin >> a >> b[0] >> b[1];
		s += a;
		for (int c=0; c<2; c++) {
			if (mx[c][0].delta < b[c]-a) {
				mx[c][1] = mx[c][0];
				mx[c][0] = D {b[c]-a, i};
			} else if (mx[c][1].delta < b[c]-a) {
				mx[c][1] = D {b[c]-a, i};
			}
		}
	}
	struct ANS {
		int mx_delta;
		int pos1, pos2;
	} ans = {INT_MIN, -1, -1};
	for (int t1=0; t1<2; t1++)
		for (int t2=0; t2<2; t2++)
			if (mx[0][t1].pos != mx[1][t2].pos && ans.mx_delta < mx[0][t1].delta + mx[1][t2].delta)
				ans = ANS {mx[0][t1].delta + mx[1][t2].delta, mx[0][t1].pos, mx[1][t2].pos};
	cout << s+ans.mx_delta << endl
		 << ans.pos1 << ' ' << ans.pos2 << endl;
	return 0;
}
