/* ACMP 1158 */
#include <cstdio>
#include <cstring>
#include <cassert>
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
	using value_type = uint32_t;
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
	f--;
	return f;
}

char ss[200001];
unsigned pos[100000];
char out[100000];

// O(n*log(n)*log(n)) solution using hashes
int main(int argc, char **argv) {
	int rc = scanf("%200000s", ss);
	int len = strlen(ss);
	assert(rc == 1 && len <= 100000 && "problem constraints");
	int bases[] = {3,5}; // use 2*32-bit hashes with bases 3, 5
	copy(ss, ss+len, ss+len);
	for (int i=0; i<len; i++)
		pos[i] = i;
	// release hash mem space immediately after we're done
	auto hash = create_multihash(ss, ss+len+len, bases);
	sort(pos, pos+len, [len,hash](const int a, const int b) {
			unsigned clen = h_commonlen(hash, a, hash, b, len);
			return ss[a+clen] < ss[b+clen];
	});
	//cerr << ss.substr(pos[0], len) << endl;
	int fp = len+1;
	for (int i=0; i<len; i++) {
		if (pos[i] == 0)
			fp = min(fp, i);
		out[i] = ss[pos[i]+len-1];
	}
	out[len] = 0;
	fprintf(stdout, "%d\n", fp+1);
	fwrite(out, 1, len, stdout);
	fputc('\n', stdout);
	return 0;
}
