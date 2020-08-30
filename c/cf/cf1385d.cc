#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...D problem */
using namespace std;

int best(const vector<vector<int>> &hh, int f, int t, int c) {
	if (f == t) {
		return 1-(hh[t][c]-hh[f-1][c]);
	} else {
		int m = (t+f)/2;
		int sc_l = (m-f+1)-(hh[m][c]-hh[f-1][c]) + best(hh, m+1, t, c+1);
		int sc_r = (t-m)-(hh[t][c]-hh[m][c]) + best(hh, f, m, c+1);
		return min(sc_l, sc_r);
	}
}

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int sz;
		cin >> sz;
		string s;
		cin >> s;
		for (auto &c:s)
			c -= 'a';
		vector<vector<int>> hh(sz+1, vector<int>(26));
		for (int i=1; i<=sz; i++)
			for (int c=0; c<26; c++)
				hh[i][c] = hh[i-1][c]+(s[i-1]==c);
		cout << best(hh, 1, sz, 0) << '\n';
	}
	return 0;
}
