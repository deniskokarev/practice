/* ACMP 121 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	unsigned aa[n];
	for (auto &a:aa)
		cin >> a;
	sort(aa, aa+n);
	unsigned rr[3];
	rr[0] = 0;
	rr[1] = INT_MAX;
	for (int i=1,ri=2; i<n; i++,ri++)
		rr[ri%3] = min(rr[(ri+3-2)%3]+aa[i]-aa[i-1], rr[(ri+3-1)%3]+aa[i]-aa[i-1]);
	cout << rr[n%3] << endl;
	return 0;
}
