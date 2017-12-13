/* ACMP 1156 */
#include <iostream>
#include <vector>
#include <array>

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
 
// hash-assisted less operator working in O(log(n))
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
	auto mh = create_multihash(ss.begin(), ss.end(), (int[]){3, 5});
	int l = s.length();
	int mn = 0;
	for (int i=1; i<l; i++)
		if (h_less(ss, mh, i, mn, l))
			mn = i;
	cout << ss.substr(mn, l) << endl;
	return 0;
}
