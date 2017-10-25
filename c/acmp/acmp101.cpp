/* ACMP 101 */
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

using BRD = vector<bitset<10>>;

// bottom part of maharaja piece attack mask
struct Mask {
	vector<vector<BRD>> msk;
	Mask(int n):msk(n, vector<BRD>(n, vector<bitset<10>>(n, 0))) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				BRD &b = msk[i][j];
				if (i+2 < n) {
					if (j+1 < n)
						b[i+2][j+1] = true;
					if (j-1 >= 0)
						b[i+2][j-1] = true;
				}
				if (i+1 < n) {
					if (j+2 < n)
						b[i+1][j+2] = true;
					if (j-2 >= 0)
						b[i+1][j-2] = true;
				}
				for (int r=0; i+r<n; r++) {
					b[i+r][j] = true;
					if (j-r>=0)
						b[i+r][j-r] = true;
					if (j+r<n)
						b[i+r][j+r] = true;
				}
			}
		}
	}
	const vector<BRD> &operator[](int i) const {
		return msk[i];
	}
};

// try to place k pieces on brd starting row r
void place(const BRD &brd, int r, int n, int k, const Mask &msk, int &cnt) {
	if (k <= 0) {
		cnt++;
	} else {
		for (int i=r; i<n-k+1; i++) {
			for (int j=0; j<n; j++) {
				if (!brd[i][j]) {
					BRD cbrd(brd);
					for (int i1=i+1; i1<n; i1++)
						cbrd[i1] |= msk[i][j][i1];
					place(cbrd, i+1, n, k-1, msk, cnt);
				}
			}
		}
	}
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	assert(n<11);
	int cnt = 0;
	BRD brd(n);
	Mask msk(n);
	place(brd, 0, n, k, msk, cnt);
	cout << cnt << endl;
	return 0;
}
