/* ACMP 1035 */
#include <algorithm>
#include <vector>
#include <cassert>
#include <stdio.h>

using namespace std;

constexpr int MXPW = 1000;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (auto &a:aa)
		scanf("%d", &a);
	int m;
	scanf("%d", &m);
	vector<pair<int,int>> cc(m); // price,pow
	for (auto &c:cc)
		scanf("%d%d", &c.second, &c.first);
	int mnprice[MXPW+1]; // power->mn price
	fill(mnprice, mnprice+MXPW+1, INT_MAX);
	sort(cc.begin(), cc.end());
	for (auto &c:cc) {
		assert(c.second <= MXPW);
		mnprice[c.second] = min(mnprice[c.second], c.first);
	}
	for (int p=MXPW; p>0; p--)
		mnprice[p-1] = min(mnprice[p-1], mnprice[p]);
	long long s = 0;
	for (auto &a:aa)
		s += mnprice[a];
	printf("%lld\n", s);
	return 0;
}
