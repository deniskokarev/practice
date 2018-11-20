#include <cstdio>
/* CodeForces CF1059C problem */
using namespace std;

void solve(int n, int f) {
	switch (n) {
	case 1:
		printf("%d ", f);
		break;
	case 2:
		printf("%d %d ", f, 2*f);
		break;
	case 3:
		printf("%d %d %d ", f, f, 3*f);
		break;
	default:
		for (int i=1; i<=n; i+=2)
			printf("%d ", f);
		solve(n/2, f*2);
	}
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	solve(n, 1);
	printf("\n");
	return 0;
}
