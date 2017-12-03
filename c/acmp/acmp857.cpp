/* ACMP 857 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

// prefix function
// compute prefix for string s of size sz
// pp random access iterator should have the same size
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

int main(int argc, char **argv) {
	int n;
	cin >> n;
	unordered_map<string, uint64_t> udict;
	for (int i=0; i<n; i++) {
		string t;
		cin >> t;
		int p[t.length()];
		prefix_function(t, t.length(), p);
		int len = p[t.length()-1];
		for (int j=1; j<=len; j++)
			udict[t.substr(0, j)]++;
		udict[t]++;
	}
	map<string, uint64_t> dict(udict.begin(), udict.end());
	uint64_t cum = 0;
	for (auto &sc:dict) {
		int c = sc.second;
		sc.second = cum;
		cum += c;
		//cerr << sc.first << " " << sc.second << endl;
	}
	dict[string(1, 'z'+1)] = cum; 
	int m;
	cin >> m;
	for (int i=0; i<m; i++) {
		string s;
		cin >> s;
		auto lb = dict.lower_bound(s);
		auto ub = dict.upper_bound(s);
		uint64_t ans = ub->second - lb->second;
		cout << ans << endl;
	}
	return 0;
}
