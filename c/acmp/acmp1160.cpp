/* ACMP 1160 */
#include <stdio.h>

int main(int argc, char **argv) {
	char s[1024*1024];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n')
		s[sz++] = c;
	int pp[sz]; // prefix function
	int k=0;
	pp[0] = 0;
	for (int i=1; i<sz; i++) {
		for (; k>0 && s[i] != s[k]; k=pp[k-1]);
		if (s[i] == s[k]) {
			k++;
			pp[i] = k;
		} else {
			pp[i] = 0;
		}
	}
	for (auto &p:pp)
		printf("%d ", p);
	printf("\n");
	return 0;
}
