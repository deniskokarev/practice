#include <iostream>
#include <algorithm>
/* CodeForces CF1037B problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	int64_t s;
	cin >> n >> s;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	sort(aa, aa+n);
	int64_t ans = 0;
	int i, j;
	for (i=0,j=n-1;i<j;i++,j--) {
		if (aa[i] > s)
			ans += aa[i]-s;
		if (aa[j] < s)
			ans += s-aa[j];
	}
	ans += abs(aa[i]-s);
	cout << ans << endl;
	return 0;
}
