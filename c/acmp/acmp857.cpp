/* ACMP 857 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

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
	vector<string> tt;
	for (int i=0; i<n; i++) {
		string t;
		cin >> t;
		int p[t.length()];
		prefix_function(t, t.length(), p);
		int len = p[t.length()-1];
		for (int j=1; j<=len; j++)
			tt.push_back(t.substr(0, j));
		tt.push_back(t);
	}
	sort(tt.begin(), tt.end());
	for (const auto &t:tt)
		cerr << t << endl;
	int m;
	cin >> m;
	for (int i=0; i<m; i++) {
		string s;
		cin >> s;
		auto lb = lower_bound(tt.begin(), tt.end(), s);
		auto ub = upper_bound(tt.begin(), tt.end(), s);
		size_t ans = ub-lb;
		cout << ans << endl;
	}
	return 0;
}
