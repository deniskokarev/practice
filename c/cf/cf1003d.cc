#include <iostream>
#include <cmath>
#include <bitset>
#include <cstring>
#include <vector>
/* CodeForces CF1003D problem */
using namespace std;

constexpr int MAX = INT_MAX/2;

int main(int argc, char **argv) {
	int n, q;
	cin >> n >> q;
	vector<vector<int>> bbcnt(33, vector<int>(33, MAX));
	vector<int> cnt(33, 0);
	while (n--) {
		int a;
		cin >> a;
		int l2 = log2(a);
		cnt[l2+1]++;
	}
	for (int l2=1; l2<33; l2++)
		for (int j=0,c=1; j<32 && c<=cnt[l2]; j++,c*=2)
			bbcnt[l2][l2+j] = c;
	for (int l2=1; l2<33; l2++)
		for (int j=l2; j<33; j++)
			bbcnt[l2][j] = min(bbcnt[l2][j], bbcnt[l2][j-1]+bbcnt[l2-1][j-1]);
	for (int l2=1; l2<33; l2++)
		for (int j=1; j<33; j++)
			bbcnt[l2][j] = min(bbcnt[l2][j], bbcnt[l2-1][j]);
#if 0
	for (int j=31; j>=0; j--) {
		for (int l2=0; l2<32; l2++)
			cerr << bbcnt[l2][j] << ' ';
		cerr << endl;
	}
#endif
	while (q--) {
		int a;
		cin >> a;
		bitset<32> ab(a);
		int s = 0;
		for (int i=0; i<32; i++) {
			if (ab[i]) {
				if (bbcnt[32][i+1] < MAX) {
					s += bbcnt[32][i+1];
				} else {
					s = -1;
					break;
				}
			}
		}
		cout << s << '\n';
	}
	return 0;
}
