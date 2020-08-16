#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF...C problem */
using namespace std;

int cnt(const vector<int> &ww, int s) {
	vector<int> vv(ww);
	int sz = ww.size();
	int cnt = 0;
	for (int i=0; i<sz; i++) {
		for (int j=i+1; j<sz; j++) {
			if (vv[i]+vv[j] == s) {
				cnt++;
				vv[j] = INT_MIN;
				goto end;
			}
		}
	end:;
	}
	return cnt;
}

int main(int argc, char **argv) {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> ww(n);
		for (auto &w:ww)
			cin >> w;
		//sort(ww.begin(), ww.end());
		int mx = INT_MIN;
		for (int s=0; s<=2*n; s++)
			mx = max(mx, cnt(ww, s));
		cout << mx << "\n";
	}
	return 0;
}
