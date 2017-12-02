/* ACMP 17 */
#include <cstdio>

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

constexpr int MX_SZ = 1024*32;

int main(int argc, char **argv) {
	int s[MX_SZ];
	int sz = 0;
	int n;
	scanf("%d", &n);
	while (sz < n)
		scanf("%d", &s[sz++]);
	int pp[sz]; // prefix function
	prefix_function(s, sz, pp);
	int ans = sz-1;
	if ((sz-1)%(sz-1-pp[sz-2]) == 0)
		ans = sz-1-pp[sz-2];
	printf("%d\n", ans);
	return 0;
}
