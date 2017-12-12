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

#include <vector>
#include <array>

// polynomial hash for all substrings of s string
// 64 bit space gives 50% cache collision on ~5*10^9 strings
// needs O(n) space and O(n) time to precompute, then O(1)
// suitable to compare the substrings of s
// NB! may not be used to compare the substrings beteen two separate PolyHash
// object, as s.length() is used as highest power
// NB!!! if you need to have better probability use MultiHash composition
template<typename IT> struct PolyHash {
	using value_type = uint64_t;
	unsigned base; // polynomial base
	int sz;
	std::vector<value_type> hash;
	std::vector<value_type> powers;
	PolyHash():base(0),sz(0) {
	}
	PolyHash(const IT begin, const IT end, unsigned b=3):base(b),sz(std::distance(begin, end)+1),hash(sz),powers(sz) {
		value_type p=1,h=0;
		hash[0] = h;
		powers[0] = p;
		int i=1;
		for (auto it=begin; it != end; ++it, ++i) {
			p *= base;
			h += (*it)*p;
			hash[i] = h;
			powers[i] = p;
		}
	}
	value_type operator()(int b, int len) const {
		value_type h;
		h = hash[b+len] - hash[b];
		return h * powers[sz-b-len];
	}
};
  
// helper fn
template<typename IT> PolyHash<IT> create_polyhash(const IT begin, const IT end, unsigned base=3) {
	return PolyHash<IT>(begin, end, base);
}
  
// composition of hashes
template<typename IT, int W> struct MultiHash {
	using hash_type = typename PolyHash<IT>::value_type;
	using value_type = std::array<hash_type, W>;
	PolyHash<IT> hash[W];
	std::array<hash_type, W> operator()(int b, int len) const {
		std::array<hash_type, W> res;
		for (int i=0; i<W; i++)
			res[i] = hash[i](b, len);
		return res;
	}
};

// hepler function to create multihash
template<typename IT, int W> MultiHash<IT, W> create_multihash(const IT begin, const IT end, const int (&bases)[W]) {
	MultiHash<IT,W> mh;
	for (int i=0; i<W; i++)
		mh.hash[i] = create_polyhash(begin, end, bases[i]);
	return mh;
}
