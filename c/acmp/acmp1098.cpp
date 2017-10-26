/* ACMP 1098 */
#include <iostream>
#include <cassert>

// screw any further optimization
// it takes about 5min to precompute all values

//#define _PRECOMPUTE_ 

using namespace std;

// sum of i*i, where i=[1, n]
int sumsq(int n) {
	return n*(n+1)*(2*n+1)/6;
}

// hypothetically we could go upto n=15
struct Brd {
	int n;
	// free column
	uint16_t c;
	// left and right diagonals where one can place Rook
	uint64_t rd;
	// left and right diagonals where one can place Queen
	uint64_t qd;
	Brd(int _n):n(_n),c(0),rd(0),qd(0) {}
};
  
// try to place k[0] and k[1] pieces on brd starting row r
inline unsigned place(Brd &brd, int r, int kq, int kr) {
	unsigned cnt = 0;
	if (kq == 0 && kr == 0) {
		cnt++;
	} else {
		int n = brd.n;
		int im = n-kq-kr+1;
		for (int i=r; i<im; i++) {
			uint64_t dl = 1<<(i+n+n);
			uint64_t dr = 1<<(n-i-1);
			uint64_t dmsk = dl|dr;
			uint16_t c = 1;
			for (int j=0; j<n; j++,dmsk<<=1,c<<=1) {
				if (!((brd.c & c) | (brd.rd & dmsk))) {
					brd.c ^= c;
					if (kr > 0) {
						kr--;
						auto oqd = brd.qd;
						brd.qd |= dmsk;
						cnt += place(brd, i+1, kq, kr);
						brd.qd = oqd;
						kr++;
					}
					if (!(brd.qd & dmsk) && kq > 0) {
						kq--;
						brd.rd ^= dmsk;
						brd.qd ^= dmsk;
						cnt += place(brd, i+1, kq, kr);
						brd.rd ^= dmsk;
						brd.qd ^= dmsk;
						kq++;
					}
					brd.c ^= c;
				}
			}
		}
	}
	return cnt;
}

#ifdef _PRECOMPUTE_

// render ac[] array
int main(int argc, char **argv) {
	int sz = sumsq(11)-1;
	cout << "const static unsigned ac[" << sz << "] = {";
	int p = 0;
	for (int n=1; n<11; n++) {
		for (int kq=0; kq<=n; kq++) {
			for (int kr=0; kr<=n; kr++) {
				if (p != 0)
					cout << ", ";
				if (kq+kr>n) {
					cout << 0;
				} else {
					Brd brd(n);
					cout << place(brd, 0, kq, kr);
				}
				p++;
			}
		}
	}
	cout << "};" << endl;
	assert(sz == p);
	return 0;
}
 
#else

const static unsigned ac[505] = {1, 1, 1, 0, 1, 4, 2, 4, 0, 0, 0, 0, 0, 1, 9, 18, 6, 9, 16, 4, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1, 16, 72, 96, 24, 16, 88, 116, 24, 0, 44, 72, 20, 0, 0, 24, 8, 0, 0, 0, 2, 0, 0, 0, 0, 1, 25, 200, 600, 600, 120, 25, 280, 904, 880, 168, 0, 140, 612, 668, 132, 0, 0, 204, 328, 100, 0, 0, 0, 82, 50, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 1, 36, 450, 2400, 5400, 4320, 720, 36, 680, 4164, 9656, 7540, 1184, 0, 340, 3072, 8068, 6368, 996, 0, 0, 1024, 3928, 3424, 432, 0, 0, 0, 982, 1240, 120, 0, 0, 0, 0, 248, 24, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 1, 49, 882, 7350, 29400, 52920, 35280, 5040, 49, 1400, 13988, 60000, 109196, 71016, 9668, 0, 700, 10884, 55016, 105480, 68100, 8780, 0, 0, 3628, 28008, 61860, 40904, 5288, 0, 0, 0, 7002, 23090, 17112, 2504, 0, 0, 0, 0, 4618, 4992, 992, 0, 0, 0, 0, 0, 832, 280, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 1, 64, 1568, 18816, 117600, 376320, 564480, 322560, 40320, 64, 2576, 38264, 264224, 879112, 1320856, 737444, 88488, 0, 1288, 30960, 260716, 943880, 1451988, 799544, 92632, 0, 0, 10320, 138272, 599424, 983496, 544488, 59472, 0, 0, 0, 34568, 233680, 448324, 259616, 28860, 0, 0, 0, 0, 46736, 136248, 90432, 11416, 0, 0, 0, 0, 0, 22708, 22344, 3464, 0, 0, 0, 0, 0, 0, 3192, 736, 0, 0, 0, 0, 0, 0, 0, 92, 0, 0, 0, 0, 0, 0, 0, 0, 1, 81, 2592, 42336, 381024, 1905120, 5080320, 6531840, 3265920, 362880, 81, 4368, 90448, 919952, 4886376, 13321960, 17065580, 8346832, 894964, 0, 2184, 75288, 959124, 5687412, 16270200, 21046344, 10131316, 1049940, 0, 0, 25096, 524992, 3843576, 12093600, 16175336, 7749984, 780488, 0, 0, 0, 131248, 1552480, 5927184, 8572664, 4188544, 416088, 0, 0, 0, 0, 310496, 1877736, 3232900, 1687608, 172992, 0, 0, 0, 0, 0, 312956, 834260, 511528, 58792, 0, 0, 0, 0, 0, 0, 119180, 110784, 16048, 0, 0, 0, 0, 0, 0, 0, 13848, 3168, 0, 0, 0, 0, 0, 0, 0, 0, 352, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 100, 4050, 86400, 1058400, 7620480, 31752000, 72576000, 81648000, 36288000, 3628800, 100, 6960, 191800, 2703456, 21038496, 91127896, 210892924, 235715912, 102624308, 9944400, 0, 3480, 163200, 2942136, 26079424, 120841116, 287684352, 322129396, 137867176, 12951636, 0, 0, 54400, 1650384, 18492056, 96403264, 242411264, 275622216, 116638880, 10611384, 0, 0, 0, 412596, 7677200, 49872012, 138974560, 164331000, 69518480, 6206236, 0, 0, 0, 0, 1535440, 16296576, 55597488, 71521024, 30873896, 2710048, 0, 0, 0, 0, 0, 2716096, 14834232, 22854784, 10485576, 900864, 0, 0, 0, 0, 0, 0, 2119176, 5092192, 2718648, 232264, 0, 0, 0, 0, 0, 0, 0, 636524, 511488, 46984, 0, 0, 0, 0, 0, 0, 0, 0, 56832, 7240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 724, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main(int argc, char **argv) {
	int n, kq, kr;
	cin >> n >> kq >> kr;
	assert(n<11);
	// !!! NB: (kq<=n && kr<=n) is not guaranteed
	// !!! we need an explicit condition for that
	if (kq>n || kr>n || kq+kr>n)
		cout << 0 << endl;
	else
		cout << ac[sumsq(n)-1+kq*(n+1)+kr] << endl;
	return 0;
}
 
#endif
