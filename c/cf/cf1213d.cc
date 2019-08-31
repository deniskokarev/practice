#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
/* CodeForces CF1213D problem */
using namespace std;

constexpr int BITS = 30;
constexpr int MX = 2e5+1;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<vector<pair<int,int>>> mm(BITS, vector<pair<int,int>>(n, make_pair(0, -1)));
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		int l2 = log2(a);
		mm[l2][i].second = a;
		for (int l=l2-1; l>=0; l--)
			mm[l][i] = make_pair(mm[l+1][i].first+1, mm[l+1][i].second/2);
	}
	int mn = INT_MAX;
	for (int p=BITS-1; p>=0 && mn == INT_MAX; p--) {
		vector<pair<int,int>> &srt = mm[p];
		sort(srt.begin(), srt.end());
		vector<int> k_cnt(MX);
		vector<int> op_cnt(MX);
		for (auto se:srt) {
			if (se.second >= 0) {
				op_cnt[se.second] += se.first;
				k_cnt[se.second]++;
				if (k_cnt[se.second] == k)
					mn = min(mn, op_cnt[se.second]);
			}
		}
	}
	cout << mn << endl;
	return 0;
}
