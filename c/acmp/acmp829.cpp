/* ACMP 829 */
#include <iostream>
#include <array>
#include <vector>
#include <set>
 
using namespace std;
 
// polynomial hash for all substrings of s string
// 64 bit space gives 50% cache collision on ~5*10^9 strings
// needs O(n) space and O(n) time to precompute, then O(1)
// suitable to compare the substrings of s
// NB! may not be used to compare the substrings beteen two separate PolyHash
// object, as s.length() is used as highest power
// NB!!! if you need to have better probability use MultiHash composition
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
	uint64_t operator()(int b, int len) const {
		uint64_t h;
		h = hash[b+len] - hash[b];
		return h * powers[sz-b-len];
	}
};
 
// helper fn
template<typename IT> PolyHash<IT> create_polyhash(const IT begin, const IT end, unsigned base=3) {
	return PolyHash<IT>(begin, end, base);
}
 
// composition of 64-bit hashes
template<typename IT, int W> struct MultiHash {
	PolyHash<IT> hash[W];
	std::array<uint64_t, W> operator()(int b, int len) const {
		std::array<uint64_t, W> res;
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

template<typename T, size_t W> string to_string(const array<T, W> &aa) {
	string s;
	for (auto a:aa)
		s += to_string(a) + '\x0';
	return s;
}

int main(int argc, char **argv) {
	const int bases[] = {3}; // composition of 2 polynomial hashes is enough
	string a, b;
	cin >> a >> b;
	size_t blen = b.length();
	// must pad both strings to equal length be able to compare hashes
	int mxsz = 1e5+1;
	set<string> known_hashes; // need to keep all known hashes for quick lookup
	{
		string bb = b+b;
		bb += string(mxsz - bb.length(), '\x0');
		auto hb = create_multihash(bb.begin(), bb.end(), bases);
		for (int i=0; i<blen; i++)
			known_hashes.insert(to_string(hb(i, blen)));
	}
	a += string(mxsz - a.length(), '\x0');
	auto ha = create_multihash(a.begin(), a.end(), bases);
	int cnt = 0;
	for (int i=0; i<=a.length()-blen; i++) {
		string hs = to_string(ha(i, blen));
		if (known_hashes.find(hs) != known_hashes.end()) {
			//cerr << "i: " << i << " s: " << a.substr(i, blen) << endl;
			cnt++;
		}
	}
	cout << cnt << endl;
	return 0;
}
