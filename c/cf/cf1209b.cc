#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1209B problem */
using namespace std;

struct L {
	int a, b;
};

constexpr int MXT = 5*5*5;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<L> ll(n);
	for (auto &l:ll)
		cin >> l.a >> l.b;
	vector<vector<int>> st(MXT, vector<int>(n));
	for (int li=0; li<n; li++) {
		auto &l = ll[li];
		st[0][li] = s[li]-'0';
		for (int t=1; t<MXT; t++)
			if (t < l.b)
				st[t][li] = st[t-1][li];
			else if ((t - l.b) % l.a == 0)
				st[t][li] = !st[t-1][li];
			else
				st[t][li] = st[t-1][li];
	}
	int mx = -1;
	for (int t=0; t<MXT; t++)
		mx = max(mx, accumulate(st[t].begin(), st[t].end(), 0));
	cout << mx << endl;
	return 0;
}
