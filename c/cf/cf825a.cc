#include <stdio.h>
/* CodeForces CF825A problem */

int main(int argc, char **argv) {
	int n;
	fscanf(stdin, "%d\n", &n);
	int p = 0;
	char aa[9+1] = {0};
	for (int i=0; i<n; i++) {
		char c = fgetc(stdin);
		if (c == '0')
			p++;
		else
			aa[p]++;
	}
	p++;
	for (int i=0; i<p; i++)
		fputc(aa[i]+'0', stdout);
	fputc('\n', stdout);
	return 0;
}
