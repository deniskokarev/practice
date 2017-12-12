/* ACMP 1156 */
#include <iostream>
#include <vector>
 
using namespace std;
 
// polynomial hash for all substrings of s string
// 64 bit space gives 50% cache collision on ~5*10^9 strings
// needs O(n) space and O(n) time to precompute, then O(1)
// suitable to compare the substrings of s
// may not be used to compare the substrings beteen two separate PolyHash
// object, as s.length() is used as highest power
template<typename IT> struct PolyHash {
	unsigned base; // polynomial base
	int sz;
	std::vector<uint64_t> hash;
	std::vector<uint64_t> powers;
	PolyHash():base(0),sz(0) {
	}
	PolyHash(const IT begin, const IT end, unsigned b=3):base(b),sz(std::distance(begin, end)+1),hash(sz),powers(sz) {
		uint64_t p=1,h=0;
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
	uint64_t pow(int p) const {
		if (p < sz) {
			return powers[p];
		} else {
			uint64_t r = pow(p/2);
			r *= r;
			if (p&1)
				r *= base;
			return r;
		}
	}
	uint64_t pad(uint64_t h, int pad) const {
		return h * pow(pad);
	}
	uint64_t operator()(int b, int len) const {
		uint64_t h;
		h = hash[b+len] - hash[b];
		return pad(h, sz-b-len);
	}
};
 
// helper fn
template<typename IT> PolyHash<IT> create_polyhash(const IT begin, const IT end, unsigned base=3) {
	return PolyHash<IT>(begin, end, base);
}
 
// long hash for == and != comparison
template<int W> struct WideHash {
	uint64_t hash[W];
	bool operator==(const WideHash<W> &b) const {
		for (int i=0; i<W; i++)
			if (hash[i] != b.hash[i])
				return false;
		return true;
	}
	bool operator!=(const WideHash<W> &b) const {
		return ! (*this == b);
	}
};
 
// composition of 64-bit hashes
template<typename IT, int W> struct MultiHash {
	PolyHash<IT> hash[W];
	WideHash<W> operator()(int b, int len) const {
		WideHash<W> res;
		for (int i=0; i<W; i++)
			res.hash[i] = hash[i](b, len);
		return res;
	}
};
 
// hepler function to create multihash
template<typename IT, int W> MultiHash<IT, W> create_multihash(const PolyHash<IT> (&h)[W]) {
	return MultiHash<IT, W>(h);
}
 
// hepler function to create multihash
template<typename IT, int W> MultiHash<IT, W> create_multihash(const IT begin, const IT end, const unsigned (&bases)[W]) {
	MultiHash<IT,W> mh;
	for (int i=0; i<W; i++)
		mh.hash[i] = create_polyhash(begin, end, bases[i]);
	return mh;
}
 
// hash-assisted less operator working in O(log(len))
// a-la:
// s.subtr(a, len) < s.substr(b, len)
template<typename HASH> bool h_less(const string &s, const HASH &hash, int a, int b, int len) {
	int f = 0, t = len;
	// find first mismatching length
	while (f<t) {
		int mid = f+(t-f)/2;
		if (hash(a, mid) != hash(b, mid))
			t = mid;
		else
			f = mid+1;
	}
	return s[a+f-1] < s[b+f-1];
}
  
int main(int argc, char **argv) {
	string s;
	cin >> s;
	string ss = s+s;
	auto mh = create_multihash(ss.begin(), ss.end(), (unsigned[]){3, 5});
	int l = s.length();
	int mn = 0;
	for (int i=1; i<l; i++)
		if (h_less(ss, mh, i, mn, l))
			mn = i;
	cout << ss.substr(mn, l) << endl;
	return 0;
}
