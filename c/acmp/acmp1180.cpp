/* ACMP 1180 */
#include <stdio.h>
#include <math.h>
#include <memory.h>

#define max(A,B) ((A>B)?A:B)

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int sq = max(sqrt(n), 1);
	int b = (n+sq-1)/sq;
	int bucket[sq];
	int el[sq][b];
	memset(bucket, -1, sizeof(bucket));
	memset(el, 0, sizeof(el));
	for (int i=0,bi=0; bi<sq; bi++) {
		for (int j=0; j<b && i<n; j++,i++) {
			scanf("%d", &el[bi][j]);
			bucket[bi] = max(bucket[bi], el[bi][j]);
		}
	}
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		int mnb = l/b+1;
		int mxb = r/b-1;
		int mx = -1;
		for (int i=mnb; i<mxb; i++)
			mx = max(mx, bucket[i]);
		for (int j=l%b; j<b; j++)
			mx = max(mx, el[l/b][j]);
		for (int j=0; j<=r%b; j++)
			mx = max(mx, el[r/b][j]);
		printf("%d ", mx);
	}
	printf("\n");
	return 0;
}
