/* ACMP 1098 */
#include <iostream>
#include <bitset>
#include <cassert>

using namespace std;

using BRD = bitset<10>[10];
using MSK = BRD[10][10];

enum {
	R = 0,
	Q = 1
};

struct Mask {
	MSK msk[2];
	Mask(int n) {
		for (int p=0; p<2; p++)
			for (int i=0; i<n; i++)
				for (int j=0; j<n; j++)
					for (int i1=0; i1<n; i1++)
						msk[p][i][j][i1] = bitset<10>(0);
		// bottom part of R piece attack mask
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				BRD &b = msk[R][i][j];
				for (int r=0; i+r<n; r++)
					b[i+r][j] = true;
			}
		}
		// bottom part of Q piece attack mask
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				BRD &b = msk[Q][i][j];
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
};

// try to place k[0] and k[1] pieces on brd starting row r
static inline void place(const BRD brd[2], int r, int n, int k[2], const MSK msk[2], int &cnt) {
	if (k[R] == 0 && k[Q] == 0) {
		cnt++;
	} else {
		for (int i=r; i<n-k[R]-k[Q]+1; i++) {
			for (int j=0; j<n; j++) {
				if (!brd[R][i][j]) {
					BRD cbrd[2];
					copy(brd[R], brd[R]+n, cbrd[R]);
					copy(brd[Q], brd[Q]+n, cbrd[Q]);
					if (k[R] > 0) {
						k[R]--;
						for (int i1=i+1; i1<n; i1++) {
							cbrd[R][i1] |= msk[R][i][j][i1];
							cbrd[Q][i1] |= msk[Q][i][j][i1];
						}
						place(cbrd, i+1, n, k, msk, cnt);
						k[R]++;
					}
					if (!brd[Q][i][j] && k[Q] > 0) {
						k[Q]--;
						for (int i1=i+1; i1<n; i1++) {
							cbrd[R][i1] |= msk[Q][i][j][i1];
							cbrd[Q][i1] |= msk[Q][i][j][i1];
						}
						place(cbrd, i+1, n, k, msk, cnt);
						k[Q]++;
					}
				}
			}
		}
	}
}

int main(int argc, char **argv) {
	int n, k[2];
	cin >> n >> k[Q] >> k[R];
	assert(n<11);
	int cnt = 0;
	BRD brd[2];
	for (int p=0; p<2; p++)
		for (int i=0; i<n; i++)
			brd[p][i] = bitset<10>(0);
	Mask m(n);
	place(brd, 0, n, k, m.msk, cnt);
	cout << cnt << endl;
	return 0;
}
