/* ACMP 202 */
#include <cstdio>

// prefix function
// compute prefix for string s of size sz
// pp random access array should have the same size
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

constexpr int MX_SZ = 1024*64;

int main(int argc, char **argv) {
	char s[MX_SZ];
	char t[MX_SZ];
	char ts[MX_SZ+MX_SZ];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n')
		s[sz++] = c;
	int s_ln = sz;
	sz = 0;
	while ((c=fgetc(stdin)) >=0 && c != '\n')
		t[sz++] = c;
	int t_ln = sz;
	sz = 0;
	for (int i=0; i<t_ln; i++)
		ts[sz++] = t[i];
	ts[sz++] = 0; // adding separator
	for (int i=0; i<s_ln; i++)
		ts[sz++] = s[i];
	int pp[sz];
	prefix_function(ts, sz, pp);
	for (int i=t_ln; i<sz; i++)
		if (pp[i] == t_ln)
			printf("%d ", i-t_ln-t_ln);
	printf("\n");
	return 0;
}
