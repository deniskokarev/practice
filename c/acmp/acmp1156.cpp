/* ACMP 1156 */
#include <iostream>
#include <vector>

using namespace std;

// using polynomial hash-assisted string comparison
// using two independent PolyHashes, as 64bit hash is too tight for our ~10^10 substrings
// (didn;t want to use long arithmetic)

// polynomial hash for all substrings of s string
// 64 bit space gives 50% cache collision on ~5*10^9 strings
// needs O(n) space and time to precompute, then O(1)
// suitable to compare the substrings of s
// may not be used to compare the substrings beteen two separate PolyHash
// object, as s.length() is used as highest power
struct PolyHash {
	unsigned base; // polynomial base
	vector<uint64_t> hh;
	vector<uint64_t> pp; // memorize the powers of base too
	PolyHash(const string &s, unsigned b):base(b),hh(s.length()+1),pp(hh.size()) {
		int len = s.length();
		uint64_t p=1,h=0;
		pp[0] = p;
		hh[0] = h;
		for (int j=0; j<len; j++) {
			p *= base;
			h += s[j]*p;
			pp[j+1] = p;
			hh[j+1] = h;
		}
	}
	uint64_t operator()(int b, int len) const {
		uint64_t h = hh[b+len] - hh[b];
		return h * pp[hh.size()-b-len];
	}
};

// hash-assisted less operator working in O(log(len))
// a-la:
// s.subtr(a, len) < s.substr(b, len)
// NB: using 2 independent hashes as I'm too lazy to implement proper 128 bit hash with long arithmetic 
bool h_less(const string &s, const PolyHash &hash1, const PolyHash &hash2, int a, int b, int len) {
	int f = 0, t = len;
	// find first mismatching length
	while (f<t) {
		int mid = f+(t-f)/2;
		if (hash1(a,mid) != hash1(b,mid) || hash2(a,mid) != hash2(b,mid))
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
	// using 2 independent hashes as I'm too lazy to implement proper hash with long arithmetic
	// 64 bit hash is too tight for our 10^10 substrings
	PolyHash hash1(ss, 3);
	PolyHash hash2(ss, 5);
	int l = s.length();
	int mn = 0;
	for (int i=0; i<l; i++)
		if (h_less(ss, hash1, hash2, i, mn, l))
			mn = i;
	cout << ss.substr(mn, l) << endl;
	return 0;
}
