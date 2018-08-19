#include <stdio.h>
#include <string.h>
#include <unordered_set>
#include <numeric>
/* CodeForces CF1005C problem */

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	unsigned aa[n];
	char xx[n];
	memset(xx, 0, sizeof(xx));
	for (auto &a:aa)
		scanf("%d", &a);
	std::unordered_set<unsigned> dd;
	for (int i=0; i<n; i++) {
		if (dd.find(aa[i]) != dd.end())
			xx[i] = 1;
		for (int l2=0; l2<32; l2++) {
			unsigned p2 = 1<<l2;
			if (aa[i] <= p2) {
				unsigned diff = p2 - aa[i]; 
				dd.insert(diff);
			}
		}
	}
	dd.clear();
	for (int i=n-1; i>=0; i--) {
		if (dd.find(aa[i]) != dd.end())
			xx[i] = 1;
		for (int l2=0; l2<32; l2++) {
			unsigned p2 = 1<<l2;
			if (aa[i] <= p2) {
				unsigned diff = p2 - aa[i]; 
				dd.insert(diff);
			}
		}
	}
	int sum = std::accumulate(xx, xx+n, 0);
	printf("%d\n", n-sum);
	return 0;
}
