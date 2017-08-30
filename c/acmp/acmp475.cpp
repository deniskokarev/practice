/* ACMP 475 problem */

#include <stdio.h>
#include <algorithm>

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	unsigned dd[100000];
	unsigned n;
	for (n=0; n<dim(dd) && !feof(stdin); n++)
		if (fscanf(stdin, "%u", &dd[n]) != 1)
			break;
	std::sort(dd, dd+n);
	unsigned s = dd[1]-dd[0];
	unsigned i;
	for (i=1; i<n-1 && (dd[i+1]-dd[i] == s); i++);
	if (i == n-1)
		printf("Yes\n");
	else
		printf("No\n");
	return 0;
}
