#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1029C problem */
using namespace std;

/**
 * number or intersected segments if overlap size is >= o
 */
int n_inter(const vector<pair<int,int>> &ss, int o) {
	vector<pair<int,int>> pp(ss.size()*2);
	int sz = 0;
	for (auto &s:ss) {
		if (s.second-o >= s.first) {
			pp[sz++] = make_pair(s.first, +1); 
			pp[sz++] = make_pair(s.second-o+1, -1);
		}
	}
	sort(pp.begin(), pp.begin()+sz);
	int mx_d = -1;
	for (int i=0,d=0; i<sz; i++) {
		d += pp[i].second;
		mx_d = max(mx_d, d);
	}
	return mx_d;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<pair<int,int>> ss(n);
	for (auto &s:ss)
		cin >> s.first >> s.second;
	int key = n-2;
	int f=0, t=1e9+1;
	while (f<t) {
		int m=f+(t-f)/2;
		if (n_inter(ss, m) > key)
			f = m+1;
		else
			t = m;
	}
	if (f>0)
		cout << f-1 << endl;
	else
		cout << 0 << endl;
	return 0;
}
