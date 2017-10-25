/* ACMP 629 */
#include <iostream>

using namespace std;

static inline bool choose(int f, int t, int *res, int ri, int n, int &cnt) {
	if (ri >= n) {
		cnt--;
		return (cnt == 0);
	}
	for (int i=f; i<t; i++) {
		res[ri] = i;
		if (choose(i+1, t+1, res, ri+1, n, cnt))
			return true;
	}
	return false;
}

int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	int res[k];
	if (choose(0, n-k+1, res, 0, k, m)) {
		string s;
		for (auto r:res)
			s += 'a'+r;
		cout << s << endl;
	}
	return 0;
}
