#include <cstddef>

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
