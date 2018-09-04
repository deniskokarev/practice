#include <iostream>
/* CodeForces CF1029B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	// already sorted
	int l = 0;
	int mx = 1;
	while (l<n) {
		int cnt = 1;
		int r;
		for (r=l+1; r<n && aa[r]<=aa[r-1]*2; r++,cnt++);
		mx = max(mx, cnt);
		l = r;
	}
	cout << mx << endl;
	return 0;
}
