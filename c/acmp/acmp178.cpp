#include <stdio.h>
#include <limits.h>
#include <algorithm>

/* ACMP 178 problem */

using namespace std;

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (int i=0; i<n; i++)
		scanf("%d", &aa[i]);
	int bb[n];
	copy(aa, aa+n, bb);
	sort(bb, bb+n);
	int mx_cnt = -1;
	int mx_el = -1;
	int i = 0;
	while (i<n) {
		int j, cnt = 0;
		for (j=i; j<n; j++)
			if (bb[j] == bb[i])
				cnt++;
			else
				break;
		if (cnt > mx_cnt) {
			mx_cnt = cnt;
			mx_el = bb[i];
		}
		i = j;
	}
	for (int i=0; i<n; i++)
		if (aa[i] != mx_el)
			printf("%d ", aa[i]);
	for (int i=0; i<mx_cnt; i++)
		printf("%d ", mx_el);
	printf("\n");
	return 0;
}
