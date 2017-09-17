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
	unsigned rr[3];
	rr[0] = 0;
	rr[1] = INT_MAX;
	for (int i=2,ri=2; i<=n; i++,ri++)
		rr[ri%3] = min(rr[(ri+3-2)%3]+aa[i]-aa[i-1], rr[(ri+3-1)%3]+aa[i]-aa[i-1]);
	cout << rr[n%3] << endl;
	return 0;
}
