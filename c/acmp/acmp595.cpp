/* ACMP 595 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
	PolyHash(const string &s, unsigned b=3):base(b),hh(s.length()+1),pp(hh.size()) {
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

// we simply go by all known matched prefixes and check if the suffix matches too
int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1 >> s2;
	if (s1.length() == s2.length()) {
		int len = s1.length();
		string ps = s2+'\x0'+s1;
		int pp[ps.length()];
		prefix_function(ps.begin(), ps.length(), pp);
		string rs1(s1);
		reverse(rs1.begin(), rs1.end());
		PolyHash hash1(rs1);
		PolyHash hash2(s2);
		int i=1;
		for (int j=s2.length()+1; j<ps.length(); j++,i++) {
			//cerr << "pfx1: " << ps.substr(j-pp[j]+1, pp[j]) << " pfx2: " << ps.substr(0, pp[j]) << endl;
			if (hash1(pp[j], len-pp[j]) == hash2(pp[j], len-pp[j]) && rs1.substr(pp[j], len-pp[j]) == s2.substr(pp[j], len-pp[j])) {
				cout << "Yes" << endl;
				cout << i-pp[j] << endl;
				return 0;
			}
		}
	}
	cout << "No" << endl;
	return 0;
}
