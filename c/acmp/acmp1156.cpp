/* ACMP 1156 */
#include <iostream>
#include <vector>

using namespace std;

// polynomial hash for all substrings of s string
// needs O(n) space and time to precompute
// suitable to compare the substrings of s
// may not be used to compare the substrings beteen two separate PolyHash
// object. The s.length() is used as highest power
struct PolyHash {
	static constexpr unsigned base = 3; // polynomial base
	vector<uint64_t> hh; // 64 bit space gives 50% cache collision on ~5*10^9 strings
	vector<uint64_t> pp; // memorize the powers of base too
	PolyHash(const string &s):hh(s.length()+1),pp(hh.size()) {
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
bool h_less(const string &s, const PolyHash &hash, int a, int b, int len) {
	int f = 0, t = len;
	// find first mismatching length
	while (f<t) {
		int mid = f+(t-f)/2;
		if (hash(a,mid) != hash(b,mid))
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
	PolyHash hash(ss);
	int l = s.length();
	int mn = 0;
	for (int i=0; i<l; i++)
		if (h_less(ss, hash, i, mn, l))
			mn = i;
	cout << ss.substr(mn, l) << endl;
	return 0;
}
