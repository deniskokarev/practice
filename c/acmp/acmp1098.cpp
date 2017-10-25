/* ACMP 1098 */
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

struct Brd {
	int n;
	// free column
	int c[10];
	// left and right diagonals where one can place Rook
	int rdl[20];
	int rdr[20];
	// left and right diagonals where one can place Queen
	int qdl[20];
	int qdr[20];
	Brd(int _n):n(_n) {
		assert(n<11);
		fill(c, c+n, 0);
		fill(rdl, rdl+n+n, 0);
		fill(rdr, rdr+n+n, 0);
		fill(qdl, qdl+n+n, 0);
		fill(qdr, qdr+n+n, 0);
	}
};

// try to place k[0] and k[1] pieces on brd starting row r
static inline int place(Brd &brd, int r, int kq, int kr) {
	int cnt = 0;
	if (kq == 0 && kr == 0) {
		cnt++;
	} else {
		int n = brd.n;
		for (int i=r; i<n-kq-kr+1; i++) {
			for (int j=0; j<n; j++) {
				int dl = i+j;
				int dr = n-i-1+j;
				if (!brd.c[j] && !brd.rdl[dl] && !brd.rdr[dr]) {
					brd.c[j] = 1;
					if (kr > 0) {
						kr--;
						int oqdl = brd.qdl[dl];
						int oqdr = brd.qdr[dr];
						brd.qdl[dl] = 1;
						brd.qdr[dr] = 1;
						cnt += place(brd, i+1, kq, kr);
						brd.qdl[dl] = oqdl;
						brd.qdr[dr] = oqdr;
						kr++;
					}
					if (!brd.qdl[dl] && !brd.qdr[dr] && kq > 0) {
						kq--;
						brd.rdl[dl] = 1;
						brd.rdr[dr] = 1;
						brd.qdl[dl] = 1;
						brd.qdr[dr] = 1;
						cnt += place(brd, i+1, kq, kr);
						brd.rdl[dl] = 0;
						brd.rdr[dr] = 0;
						brd.qdl[dl] = 0;
						brd.qdr[dr] = 0;
						kq++;
					}
					brd.c[j] = 0;
				}
			}
		}
	}
	return cnt;
}

int main(int argc, char **argv) {
	int n, kq, kr;
	cin >> n >> kq >> kr;
	Brd brd(n);
	int cnt = place(brd, 0, kq, kr);
	cout << cnt << endl;
	return 0;
}
