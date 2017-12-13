/* ACMP 595 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

// we simply match the biggest last prefix and then match the remaining inverted string
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
		int lst = ps.length()-1;
		//cerr << "pfx1: " << ps.substr(lst-pp[lst]+1, pp[lst]) << " pfx2: " << ps.substr(0, pp[lst]) << endl;
		//cerr << "sfx1: " << rs1.substr(pp[lst], len-pp[lst]) << " sfx2: " << s2.substr(pp[lst], len-pp[lst]) << endl;
		if (rs1.substr(pp[lst], len-pp[lst]) == s2.substr(pp[lst], len-pp[lst])) {
			cout << "Yes" << endl << len-pp[lst] << endl;
		} else {
			cout << "No" << endl;
		}
	} else {
		cout << "No" << endl;
	}
	return 0;
}
