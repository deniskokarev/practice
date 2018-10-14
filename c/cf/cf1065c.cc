#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1065C problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t n, k;
	cin >> n >> k;
	vector<int64_t> ac(3e5+1);
	int mnh = INT_MAX;
	for (int i=0; i<n; i++) {
		int h;
		cin >> h;
		ac[h]++;
		mnh = min(mnh, h);
	}
	for (int i=int(ac.size())-2; i>=0; i--)
		ac[i] += ac[i+1];
	int ans = 0;
	int h = int(ac.size())-1;
	while (h > mnh) {
		int64_t shave = 0;
		while (shave + ac[h] <= k && h > mnh) {
			shave += ac[h];
			h--;
		}
		ans++;
	}
	cout << ans << endl;
	return 0;
}
