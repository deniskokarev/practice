#include <cstdio>
#include <algorithm>
/* INF 113075 */

int main(int argc, char **argv) {
	int n, k, ssz;
	scanf("%d%d%d", &n, &k, &ssz);
	int ss[ssz+1]; // input will be sorted
	ss[0] = 0;
	for (int i=1; i<ssz+1; i++)
		scanf("%d", &ss[i]);
	int d = 0;
	int hops = 0;
	while (d+k<n) {
		size_t fnd = std::upper_bound(ss, ss+ssz+1, d+k)-ss;
		int dn = ss[fnd-1];
		if (dn == d) {
			hops = -1;
			break;
		}
		d = dn;
		hops++;
	}
	printf("%d\n", hops);
	return 0;
}
