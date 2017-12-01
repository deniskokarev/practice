/* ACMP 1161 */
#include <stdio.h>

constexpr int MX_SZ = 1024*1024;

#define MIN(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	char s[MX_SZ];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n' && sz<MX_SZ)
		s[sz++] = c;
	int zz[sz]; // suffix fn z function // taken from e-maxx
	zz[0] = 0;
	for (int i=1,l=0,r=0; i<sz; i++) {
		if (i <= r)
			zz[i] = MIN(r-i+1, zz[i-l]);
		int cnt;
		for (cnt=0; i+cnt < sz && s[cnt] == s[i+cnt]; cnt++);
		zz[i] = cnt;
		if (i+cnt-1 > r) {
			l = i;
			r = i+cnt-1;
		}
	}
	for (auto &z:zz)
		printf("%d ", z);
	printf("\n");
    return 0;
}
