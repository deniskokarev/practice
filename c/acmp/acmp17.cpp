/* ACMP 17 */
#include <cstdio>
#include <algorithm>
#include <iterator>

// suffix function (z function)
// compute suffix sizes for string s of size sz
// zz random access iterator should have the same size
// taken from wikipedia (e-maxx implementation has a performance problem)
template <typename RIC, typename RIN> void suffix_function(const RIC s, size_t len, RIN z) {
	using T = typename std::iterator_traits<RIN>::value_type;
    z[0] = len;
    for (T j,i=1,l=0,r=0; i < len; i++) {
        if (i > r) {
            for (j = 0; ((j + i) < len) && (s[i + j] == s[j]) ; j++);
            z[i] = j;
            l = i;
            r = (i + j - 1);
        } else {
            if (z[i - l] < (r - i + 1)) {
                z[i] = z[i - l];
            } else {
                for (j = 1; ((j + r) < len) && (s[r + j] == s[r - i + j]); j++);
                z[i] = (r - i + j);
                l = i;
                r = (r + j - 1);
            }
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
	unsigned zz[sz]; // suffix function
	suffix_function(s, sz, zz);
    int ans = 1;
    for (int i=sz-1; i>0; i--)
        if (i+zz[i] == sz && (sz-1)%i == 0)
            ans = i;	
	printf("%d\n", ans);
	return 0;
}
