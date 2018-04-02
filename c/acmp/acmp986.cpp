/* ACMP 986 */
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
	int n, fx, fy, l;
	scanf("%d%d%d%d", &n, &fx, &fy, &l);
	int l2 = l*l;
	for (int i=1; i<=n; i++) {
		int sx, sy;
		scanf("%d%d", &sx, &sy);
		int d2 = (sx-fx)*(sx-fx)+(sy-fy)*(sy-fy);
		if (d2<=l2) {
			printf("%d\n", i);
			goto end;
		}
	}
	printf("Yes\n");
 end:
	return 0;
}
