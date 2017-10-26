/* ACMP 1098 */
#include <iostream>
#include <cassert>

using namespace std;

struct Brd {
	// left and right diagonals where one can place Rook
	uint64_t c_rd;
	// left and right diagonals where one can place Queen
	uint64_t qd;
};

static int cnt;
static int n;
static Brd brd;
static int kq;
static int kr;

// try to place k[0] and k[1] pieces on brd starting row r
static void place(int r) {
	if (kq == 0 && kr == 0) {
		cnt++;
	} else {
		int im = n-kq-kr+1;
		for (int i=r; i<im; i++) {
			const uint64_t dl = 1<<(i+n+n);
			const uint64_t dr = 1<<(n-i-1);
			uint64_t c = 1ULL<<40;
			uint64_t dmsk = dl|dr|c;
			for (int j=0; j<n; j++,dmsk<<=1,c<<=1) {
				if (!(brd.c_rd & dmsk)) {
					brd.c_rd ^= c;
					if (kr > 0) {
						kr--;
						const auto oqd = brd.qd;
						brd.qd |= dmsk;
						place(i+1);
						brd.qd = oqd;
						kr++;
					}
					brd.c_rd ^= c;
					if (!(brd.qd & dmsk) && kq > 0) {
						kq--;
						brd.c_rd ^= dmsk;
						brd.qd ^= dmsk;
						place(i+1);
						brd.c_rd ^= dmsk;
						brd.qd ^= dmsk;
						kq++;
					}
				}
			}
		}
	}
}

int main(int argc, char **argv) {
	cin >> n >> kq >> kr;
	assert(n<11);
	place(0);
	cout << cnt << endl;
	return 0;
}
