/* ACMP 857 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// suffix function (z function)
// compute suffix sizes for string s of size sz
// zz random access iterator should have the same size
// implementation from wikipedia
template <typename RIC, typename RIN> void suffix_function(const RIC s, size_t len, RIN z) {
	using T = typename std::iterator_traits<RIN>::value_type;
    z[0] = 0;
    for (T j,i=1,l=0,r=0; i < len; i++) {
        if (i > r) {
            for (j = 0; ((j + i) < len) && (s[i + j] == s[j]); j++);
            z[i] = j;
            l = i;
            r = (i + j - 1);
        } else {
            if (z[i - l] < (r - i + 1)) {
                z[i] = z[i - l];
            } else {
                for (j = 1; ((j + r) < len) && (s[r + j] == s[r - i + j]); j++);
                z[i] = (r - i + j);
                l = i;
                r = (r + j - 1);
            }
        }
    }
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	unordered_map<string, uint64_t> udict;
	for (int i=0; i<n; i++) {
		string t;
		cin >> t;
		int sz = t.length();
		int zz[sz];
		suffix_function(t, sz, zz);
#if 0
		for (auto &z:zz)
			cerr << z << " ";
		cerr << endl;
#endif
		for (int j=1; j<sz; j++)
			if (j+zz[j] == sz)
				udict[t.substr(j, zz[j])]++;
		udict[t]++;
	}
#if 0
	for (auto &sc:udict)
		cerr << sc.first << " " << sc.second << endl;
#endif
	int m;
	cin >> m;
	for (int i=0; i<m; i++) {
		string s;
		cin >> s;
		auto f = udict.find(s);
		uint64_t ans = 0;
		if (f != udict.end())
			ans = f->second;
		cout << ans << endl;
	}
	return 0;
}
