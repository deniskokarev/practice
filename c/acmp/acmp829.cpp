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
 
int main(int argc, char **argv) {
	string a, b;
	cin >> a >> b;
	size_t blen = b.length();
	// must pad both strings to equal length be able to compare hashes
	int mxsz = 2e5+1;
	set<uint64_t> known_hashes; // need to keep all known hashes for quick lookup
	string bb = b+b;
	bb += string(mxsz - bb.length(), '\x0');
	auto hb = create_polyhash(bb.begin(), bb.end());
	for (int i=0; i<blen; i++)
		known_hashes.insert(hb(i, blen));
	a += string(mxsz - a.length(), '\x0');
	auto ha = create_polyhash(a.begin(), a.end());
	int cnt = 0;
	for (int i=0; i<=a.length()-blen; i++) {
		if (known_hashes.find(ha(i, blen)) != known_hashes.end()) {
			//cerr << "i: " << i << " s: " << a.substr(i, blen) << endl;
			cnt++;
		}
	}
	cout << cnt << endl;
	return 0;
}
