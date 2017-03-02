#include <iostream>
#include <vector>
/* CodeForces CF777C problem */
using namespace std;

int main(int argc, char **argv) {
	int r, c;
	cin >> r >> c;
	vector<int> ccnt(c, 0);
	vector<vector<int>> a {vector<int>(c, 0), vector<int>(c, INT_MAX)};
	vector<int> mx(r, 0);
	for (int i=0; i<r; i++) {
		for (int j=0; j<c; j++) {
			cin >> a[i&1][j];
			if (a[i&1][j] < a[(i+1)&1][j])
				ccnt[j] = i;
			mx[i] = max(mx[i], i-ccnt[j]);
		}
	}
	int k;
	cin >> k;
	for (int i=0; i<k; i++) {
		int l, r;
		cin >> l >> r;
		bool rc = (mx[r-1] >= (r-l))?true:false;
		cout << (rc?"Yes":"No") << endl;
	}
	return 0;
}
