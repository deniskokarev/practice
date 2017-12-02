/* ACMP 204 */
#include <iostream>

using namespace std;

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
	string ss;
	cin >> ss;
	int sz = ss.length();
	int pp[sz];
	prefix_function(ss, sz, pp);
    int ans = sz;
	for (int i=sz-1; i>0; i--)
		if (sz%(sz-pp[i]) == 0)
			ans = min(ans, sz-pp[sz-1]);
    printf("%d\n", ans);
	return 0;
}
