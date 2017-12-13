/* ACMP 1157 */
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
  
using namespace std;

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

// hash-assisted common string length search
template<typename HASH> unsigned h_commonlen(const HASH &fhash, unsigned fp, const HASH &rhash, unsigned rp, unsigned mxlen) {
	// upper bound search
	unsigned f=0, t=mxlen;
	while (f<t) {
		unsigned m = f+(t-f)/2;
		if (fhash(fp, m) != rhash(rp, m))
			t = m;
		else
			f = m+1;
	}
	// correct the result
	if (fhash(fp, f) != rhash(rp, f))
		f--;
	return f;
}

// O(n*log(n)) solution using hashes
int main(int argc, char **argv) {
	string s;
	cin >> s;
	int bases[] = {3, 5, 7}; // had to use 3*64-bit hashes with bases 3, 5 and 7
	auto fhash = create_multihash(s.begin(), s.end(), bases);
	reverse(s.begin(), s.end());
	auto rhash = create_multihash(s.begin(), s.end(), bases);
	int len = s.length();
	uint64_t cnt = 0;
	// odd palindromes
	for (int i=0; i<len; i++) {
		unsigned fp = i, rp = len-i-1, mxlen = min(len-i, i+1);
		unsigned sz = h_commonlen(fhash, fp, rhash, rp, mxlen);
		//cerr << "odd fp: " << fp << " rp: " << rp << " mxlen: " << mxlen << " sz: " << sz << endl;
		cnt += sz;
	}
	// even palindromes
	for (int i=1; i<len; i++) {
		unsigned fp = i, rp = len-i, mxlen = min(len-i, i);
		unsigned sz = h_commonlen(fhash, fp, rhash, rp, mxlen);
		//cerr << "even fp: " << fp << " rp: " << rp << " mxlen: " << mxlen << " sz: " << sz << endl;
		cnt += sz;
	}
	cout << cnt << endl;
	return 0;
}
