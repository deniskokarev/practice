#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int base = 13;

struct SSTR {
	int b, e; // [b, e)
};

// hash-assisted comparison by looking at common prefix
struct SSTR_CMP {
	const vector<uint64_t> &ss_hpow;
	const vector<uint64_t> &ss_hash;
	const string s;
	const int sz;
	bool operator()(const SSTR &a, const SSTR &b) {
		int mnl = min(a.e-a.b, b.e-b.b);
		// upper-bound search
		int f=1, t=mnl+1;
		while (f<t) {
			int m = f+(t-f)/2;
			uint64_t ha = (ss_hash[a.b+m]-ss_hash[a.b])*ss_hpow[sz-a.b-m];
			uint64_t hb = (ss_hash[b.b+m]-ss_hash[b.b])*ss_hpow[sz-b.b-m];
			if (ha == hb)
				f = m+1;
			else
				t = m;
		}
		if (f<=mnl)
			return s[a.b+f-1] < s[b.b+f-1];
		else
			return (a.e-a.b) < (b.e-b.b);
	}
};

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sz = s.size();
	vector<SSTR> ss(sz, SSTR {0, 0});
	vector<uint64_t> ss_hpow(sz+1);
	ss_hpow[0] = 1;
	vector<uint64_t> ss_hash(sz+1);
	ss_hash[0] = 0;
	for (int i=0; i<sz; i++) {
		ss[i].b = i;
		ss[i].e = sz;
		ss_hpow[i+1] = ss_hpow[i]*base;
		ss_hash[i+1] = ss_hash[i]+ss_hpow[i+1]*s[i];
	}
	sort(ss.begin(), ss.end(), SSTR_CMP {ss_hpow, ss_hash, s, sz});
	for (int i=0; i<sz; i++)
		cout << ss[i].b << ' ';
	cout << endl;
	return 0;
}
