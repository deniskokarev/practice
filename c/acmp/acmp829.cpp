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
	using value_type = unsigned long long;
	unsigned mod;
	unsigned base; // polynomial base
	int sz;
	std::vector<unsigned> hash;
	std::vector<unsigned> powers;
	PolyHash() {
	}
	PolyHash(const IT begin, const IT end, unsigned mod, unsigned b=257):mod(mod),base(b),sz(std::distance(begin, end)+1),hash(sz),powers(sz) {
		value_type p=1,h=0;
		hash[0] = h;
		powers[0] = p;
		int i=1;
		for (auto it=begin; it != end; ++it, ++i) {
			p *= base;
			p %= mod;
			unsigned v = (*it);
			h += v * p;
			h %= mod;
			hash[i] = h;
			powers[i] = p;
		}
	}
	value_type operator()(int b, int len) const {
		value_type h = (value_type(hash[b+len]) + mod - hash[b]) % mod;
		return (h * powers[sz-b-len]) % mod;
	}
};
  
// helper fn
template<typename IT> PolyHash<IT> create_polyhash(const IT begin, const IT end, unsigned mod) {
	return PolyHash<IT>(begin, end, mod);
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
template<typename IT, int W> MultiHash<IT, W> create_multihash(const IT begin, const IT end, const unsigned (&mods)[W]) {
	MultiHash<IT,W> mh;
	for (int i=0; i<W; i++)
		mh.hash[i] = create_polyhash(begin, end, mods[i]);
	return mh;
}
 
int main(int argc, char **argv) {
	// composite hash of 2x32-bit values is enough for this problem
	// if you're careful it still fits the 16MB memory constraint
	const unsigned mods[] = {4294967279, 4294967291};
	string a, b;
	cin >> a >> b;
	size_t blen = b.length();
	// must pad both strings to equal length be able to compare hashes
	int mxsz = max(a.length(), blen*2)+1;
	// determine the multihash element type without actually running it yet
	using hash_value_type = typename decltype(create_multihash(a.begin(), a.end(), mods))::value_type;
	// need to keep all known hashes for quick lookup
	set<hash_value_type> known_hashes;
	{
		// release memory for hash b immediately after adding hashes into the set
		string bb = b+b;
		bb += string(mxsz - bb.length(), '\x0'); // pad for eq length
		auto hb = create_multihash(bb.begin(), bb.end(), mods);
		for (int i=0; i<blen; i++)
			known_hashes.insert(hb(i, blen));
	}
	a += string(mxsz - a.length(), '\x0'); // pad for eq length
	auto ha = create_multihash(a.begin(), a.end(), mods);
	int cnt = 0;
	for (int i=0; i<=a.length()-blen; i++)
		if (known_hashes.find(ha(i, blen)) != known_hashes.end())
			cnt++;
	cout << cnt << endl;
	return 0;
}
