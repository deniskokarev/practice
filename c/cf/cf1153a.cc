#include <iostream>
/* CodeForces CF1153A problem */
using namespace std;

int main(int argc, char **argv) {
	int n, t;
	cin >> n >> t;
	struct A {
		int w, ans;
	} ans {INT_MAX, -1};
	for (int i=0; i<n; i++) {
		int s, d;
		cin >> s >> d;
		int w;
		if (s < t) {
			int n = (t-s+d-1)/d;
			w = s+n*d - t;
		} else {
			w = (s-t);
		}
		if (w < ans.w) {
			ans.w = w;
			ans.ans = i;
		}
	}
	cout << ans.ans + 1 << endl;
	return 0;
}
