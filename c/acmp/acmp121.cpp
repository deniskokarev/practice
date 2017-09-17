/* ACMP 121 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n+1];
	for (int i=1; i<=n; i++)
		cin >> aa[i];
	sort(aa+1, aa+n+1);
	long long rr[n+1];
	rr[0] = 0;
	rr[1] = INT_MAX;
	for (int i=2; i<=n; i++)
		rr[i] = min(rr[i-2]+aa[i]-aa[i-1], rr[i-1]+aa[i]-aa[i-1]);
	cout << rr[n] << endl;
	return 0;
}
