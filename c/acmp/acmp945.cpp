/* ACMP 945 */

#include <algorithm>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	long long aa[n]; // to fit 2^32
	for (long long &a:aa)
		scanf("%lld", &a);
	sort(aa, aa+n);
	while (k-- > 0) {
		long long b;
		scanf("%lld", &b);
		if (binary_search(aa, aa+n, b))
			fputs("YES ", stdout);
		else
			fputs("NO ", stdout);
	}
	fputc('\n', stdout);
	return 0;
}
