#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1203D problem */
using namespace std;

int main(int argc, char **argv) {
	string s, t;
	cin >> s >> t;
	vector<int> tpos(t.size());
	int si=0, ti=0;
	while (si<s.size() && ti<t.size()) {
		if (s[si] == t[ti]) {
			tpos[ti] = si;
			ti++;
			if (ti == t.size())
				break;
		}
		si++;
	}
	// guaranteed to match
	int mx = s.size()-tpos[tpos.size()-1]-1;
	si = s.size()-1;
	ti = t.size()-1;
	while (ti > 0 && si >= tpos[ti-1]) {
		if (s[si] == t[ti]) {
			mx = max(mx, si-tpos[ti-1]-1);
			ti--;
		}
		si--;
	}
	while (si >= 0) {
		if (s[si] == t[0])
			mx = max(mx, si);
		si--;
	}
	cout << mx << endl;
	return 0;
}
