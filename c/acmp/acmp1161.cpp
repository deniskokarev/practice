/* ACMP 1161 */
#include <stdio.h>

constexpr int MX_SZ = 1024*1024;

int main(int argc, char **argv) {
	char s[MX_SZ];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n' && sz<MX_SZ)
		s[sz++] = c;
	int zz[sz]; // suffix fn
	zz[0] = 0;
	for (int i=1; i<sz; i++) {
		int hd, cnt;
		for (hd=0,cnt=0; i+cnt<sz && s[hd] == s[i+cnt]; hd++,cnt++);
		zz[i] = cnt;
		for (int j=0; j<cnt; j++)
			zz[i+j+1] = zz[j+1];
		i += cnt;
	}
	for (auto &z:zz)
		printf("%d ", z);
	printf("\n");
    return 0;
}
