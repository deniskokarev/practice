#include <cstdio>
/* ACMP 424 */
using namespace std;

static int ans(unsigned n, int p) {
	if (n <= 1)
		return p;
	if (p)
		return ans((n+8)/9, p^1);
	else
		return ans((n+1)/2, p^1);
};

int main(int argc, char **argv) {
	unsigned n;
	scanf("%u", &n);
	printf("%s wins.\n", ans(n, 1)?"Ollie":"Stan");
	return 0;
}
