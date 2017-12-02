/* ACMP 1161 */
#include <stdio.h>

#include <iterator>
#include <algorithm>

// two implementations of suffix function
// depending on the input set one may work better than other

#if 1
// suffix function (z function)
// compute suffix sizes for string s of size sz
// zz random access iterator should have the same size
// implementation from wikipedia
template <typename RIC, typename RIN> void suffix_function(const RIC s, size_t len, RIN z) {
	using T = typename std::iterator_traits<RIN>::value_type;
    z[0] = 0;
    for (T j,i=1,l=0,r=0; i < len; i++) {
        if (i > r) {
            for (j = 0; ((j + i) < len) && (s[i + j] == s[j]); j++);
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
#else
// implementation from e-maxx
template <typename RIC, typename RIN> void suffix_function(const RIC s, size_t sz, RIN zz) {
	using T = typename std::iterator_traits<RIN>::value_type;
    zz[0] = 0;
    for (T i=1,l=0,r=0; i<sz; i++) {
        if (i <= r)
            zz[i] = std::min(r-i+1, zz[i-l]);
        T cnt;
        for (cnt=0; i+cnt < sz && s[cnt] == s[i+cnt]; cnt++);
        zz[i] = cnt;
        if (i+cnt-1 > r) {
            l = i;
            r = i+cnt-1;
        }
    }
}
#endif

constexpr int MX_SZ = 1024*1024;

#define MIN(A,B) ((A<B)?A:B)

int main(int argc, char **argv) {
	char s[MX_SZ];
	int sz = 0;
	int c;
	while ((c=fgetc(stdin)) >=0 && c != '\n' && sz<MX_SZ)
		s[sz++] = c;
	int zz[sz]; // suffix fn z function // taken from wikipedia
	suffix_function(s, sz, zz);
	for (auto &z:zz)
		printf("%d ", z);
	printf("\n");
    return 0;
}
