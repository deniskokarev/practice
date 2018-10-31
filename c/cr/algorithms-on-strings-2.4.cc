#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SSTR {
	const string *s;
	int pos, sz;
	bool operator<(const SSTR &b) const {
		int cmp = 0;
		int i = 0;
		while (cmp == 0 && i < sz && i < b.sz) {
			cmp = int((*s)[pos+i]) - int((*b.s)[b.pos+i]);
			i++;
		}
		if (cmp == 0)
			return (sz<b.sz);
		else
			return (cmp<0);
	}
};

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sz = s.size();
	vector<SSTR> ss(sz, SSTR {&s, 0, 0});
	for (int i=0; i<sz; i++) {
		ss[i].pos = i;
		ss[i].sz = sz-i;
	}
	sort(ss.begin(), ss.end());
	for (int i=0; i<sz; i++)
		cout << ss[i].pos << ' ';
	cout << endl;
	return 0;
}
