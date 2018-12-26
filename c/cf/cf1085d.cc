#include <cstdio>
#include <algorithm>
/* CodeForces CF1085D problem */
using namespace std;

int main(int argc, char **argv) {
	int n, s;
	scanf("%d%d", &n, &s);
	int vv[n];
	fill(vv, vv+n, 0);
	for (int i=0; i<n-1; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		vv[f]++;
		vv[t]++;
	}
	int l = 0;
	for (int i=0; i<n; i++)
		if (vv[i] == 1)
			l++;
	printf("%.8f\n", 2.0*s/l);
	return 0;
}
