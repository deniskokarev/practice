/* ACMP 1098 */
#include <iostream>
#include <bitset>
#include <cassert>

using namespace std;

using BRD = bitset<10>[10];
using MSK = BRD[10][10];

static MSK mq, mr;

int cnt;

// try to place k[0] and k[1] pieces on brd starting row r
static inline void place(const BRD &bq, const BRD &br, int r, int n, int kq, int kr) {
	if (kq == 0 && kr == 0) {
		cnt++;
	} else {
		for (int i=r; i<n-kq-kr+1; i++) {
			for (int j=0; j<n; j++) {
				if (!br[i][j]) {
					BRD cbq, cbr;
					copy(bq, bq+n, cbq);
					copy(br, br+n, cbr);
					if (kr > 0) {
						kr--;
						for (int i1=i+1; i1<n; i1++) {
							cbr[i1] |= mr[i][j][i1];
							cbq[i1] |= mq[i][j][i1];
						}
						place(cbq, cbr, i+1, n, kq, kr);
						kr++;
					}
					if (!bq[i][j] && kq > 0) {
						kq--;
						for (int i1=i+1; i1<n; i1++) {
							cbr[i1] |= mq[i][j][i1];
							cbq[i1] |= mq[i][j][i1];
						}
						place(cbq, cbr, i+1, n, kq, kr);
						kq++;
					}
				}
			}
		}
	}
}

static BRD brdq, brdr;

int main(int argc, char **argv) {
	int n, kq, kr;
	cin >> n >> kq >> kr;
	assert(n<11);

	// bottom part of R piece attack mask
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			BRD &b = mr[i][j];
			for (int r=0; i+r<n; r++)
				b[i+r][j] = true;
		}
	}
	// bottom part of Q piece attack mask
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			BRD &b = mq[i][j];
			for (int r=0; i+r<n; r++) {
				b[i+r][j] = true;
				if (j-r>=0)
					b[i+r][j-r] = true;
				if (j+r<n)
					b[i+r][j+r] = true;
			}
		}
	}

	place(brdq, brdr, 0, n, kq, kr);
	cout << cnt << endl;
	return 0;
}
