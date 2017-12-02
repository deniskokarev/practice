/* ACMP 1160 */
#include <stdio.h>

// prefix function
// compute prefix for string s of size sz
// pp random access iterator should have the same size
template <typename RIC, typename RIN> void prefix_function(const RIC s, size_t sz, RIN pp) {
	size_t k = 0;
	pp[0] = 0;
	for (size_t i=1; i<sz; i++) {
		for (; k>0 && s[i] != s[k]; k=pp[k-1]);
		if (s[i] == s[k]) {
			k++;
			pp[i] = k;
		} else {
			pp[i] = 0;
		}
	}
}

int main(int argc, char **argv) {
	char s[1024*1024];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n')
		s[sz++] = c;
	int pp[sz]; // prefix function
	prefix_function(s, sz, pp);
	for (auto &p:pp)
		printf("%d ", p);
	printf("\n");
	return 0;
}
