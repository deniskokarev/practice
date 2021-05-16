/* ACMP 1702 */
#include <cstdio>
#include <algorithm>

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (auto &a:aa)
		scanf("%d", &a);
	while (n) {
		int pos = std::max_element(aa, aa+n) - aa;
		printf("%d ", pos);
		std::swap(aa[pos], aa[n-1]);
		n--;
	}
	printf("\n");
	return 0;
}
