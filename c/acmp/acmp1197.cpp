/* ACMP 1197 */
#include <iostream>
#include <algorithm>

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
	char s[sz];
	uint64_t cnt = 0;
	for (int i=sz-1; i>=0; i--) {
		s[i] = ss[i];
		prefix_function(s+i, sz-i, pp);
		int *mxp = max_element(pp, pp+sz-i);
		cnt += (sz-i) - *mxp;
	}
    cout << cnt << endl;
	return 0;
}
