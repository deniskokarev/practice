/* ACMP 857 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

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

struct Trie {
	static constexpr int sz = 'z' - 'a' + 1;
	unique_ptr<Trie> next[sz];
	int cnt;
	Trie():cnt(0){}
	Trie *expand(uint8_t idx) {
		uint8_t i = idx - 'a';
		i %= sz;
		if (next[i] == nullptr)
			next[i] = unique_ptr<Trie>(new Trie());
		return next[i].get();
	}
	const Trie *down(uint8_t idx) const {
		uint8_t i = idx - 'a';
		i %= sz;
		return next[i].get();
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	Trie root;
	for (int i=0; i<n; i++) {
		string t;
		cin >> t;
		int p[t.length()];
		prefix_function(t, t.length(), p);
		int len = p[t.length()-1];
		Trie *chld = &root;
		int j = 0;
		while (j<len) {
			chld = chld->expand(t[j++]);
			chld->cnt++;
		}
		while (j<t.length())
			chld = chld->expand(t[j++]);
		chld->cnt++;
	}
	int m;
	cin >> m;
	for (int i=0; i<m; i++) {
		int ans = 0;
		string s;
		cin >> s;
		int j = 0;
		int len = s.length();
		const Trie *chld = &root;
		while (j<len && chld != nullptr) {
			chld = chld->down(s[j]);
			j++;
		}
		if (chld != nullptr && j==len)
			ans += chld->cnt;
		cout << ans << endl;
	}
	return 0;
}
