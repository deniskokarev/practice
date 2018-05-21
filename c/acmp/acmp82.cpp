#include <stdio.h>
#include <cstring>
#include <cassert>
/* ACMP 82 */
using namespace std;

constexpr int MX = 1e5;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int cnt[MX+1];
	memset(cnt, 0, sizeof(cnt));
	int a;
	while (n--) {
		scanf("%d", &a);
		assert(0 <= a && a <= MX);
		cnt[a] = 1;
	}
	while (m--) {
		scanf("%d", &a);
		assert(0 <= a && a <= MX);
		cnt[a] |= 2;
	}
	for (int i=0; i<=MX; i++)
		if (cnt[i] == 3)
			printf("%d ", i);
	printf("\n");
	return 0;
}
