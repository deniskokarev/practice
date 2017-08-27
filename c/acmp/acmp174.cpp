/* ACMP 174 */
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
int main() {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	double g;
	cin >> g;
	sort(aa, aa+n);
	for (auto &a:aa)
		if (a>g)
			g = (g+a)/2;
	printf("%.6f\n", g);
	return 0;
}

