#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <algorithm>
#include <cmath>
#include <cassert>
/* inf 1993 - queens placing on chessboard of size N */
using namespace std;

class Brd {
public:
	static constexpr int MXSZ = 200;
protected:
	int sz;
	vector<int> hh; // horizontals
	mt19937 rnd;
	pair<int,int> rand_pair() {
		int64_t r1, r2;
		do {
			r1 = int64_t(rnd())*sz/(mt19937::max()+1LL);
			r2 = int64_t(rnd())*sz/(mt19937::max()+1LL);
		} while (r1 == r2);
		return make_pair(min(r1, r2), max(r1, r2));
	}
	struct R {
		mt19937 &rnd;
		size_t operator()(int i) {
			return rnd() % i;
		}
	};
public:
	Brd(int _sz):sz(_sz),hh(sz),rnd(sz) {
		R rs_rnd {rnd};
		assert(sz <= MXSZ);
		for (int i=0; i<sz; i++)
			hh[i] = i;
		random_shuffle(hh.begin(), hh.end(), rs_rnd);
	}
	// need to reach 0
	int cost() const {
		bitset<MXSZ*2> sm_hi, sm_lo;
		for (int i=0; i<sz; i++) {
			sm_hi[hh[i]+sz-i] = 1;
			sm_lo[hh[i]+i] = 1;
		}
		return sz*2 - sm_hi.count() - sm_lo.count();
	}
	// we'll optimize by trying to flip random rows
	int try_flip(pair<int, int> *flip) {
		*flip = rand_pair();
		swap(hh[flip->first], hh[flip->second]);
		int c = cost();
		swap(hh[flip->second], hh[flip->first]);
		return c;
	}
	void commit_flip(const pair<int, int> &flip) {
		swap(hh[flip.first], hh[flip.second]);
	}
	ostream &dbg_prn(ostream &os, const Brd &b) {
		for (int i=0; i<b.sz; i++) {
			for (int j=0; j<b.sz; j++)
				if (b.hh[i] == j)
					os << "Q ";
				else
					os << ". ";
			os << '\n';
		}
		return os;
	}
	friend ostream &operator<<(ostream &os, const Brd &b);
};

ostream &operator<<(ostream &os, const Brd &b) {
	for (auto h:b.hh)
		cout << h+1 << ' ';
	return os;
}

bool transition(int t, int e1, int e2, mt19937 &rnd) {
	double de = e2-e1;
	if (de < 0) {
		return true;
	} else {
		double p = exp(-de*1e8/t);
		double r = double(rnd())/mt19937::max();
		return r<p;
	}
}

int main(int argc, char **argv) {
	mt19937 rnd;
	int sz;
	cin >> sz;
	// simulated annealing optimization
	Brd brd(sz);
	int enrg = brd.cost();
	int t = 1e7;
	while (enrg>0 && t>0) {
		pair<int,int> flip;
		int nenrg = brd.try_flip(&flip);
		if (transition(t, enrg, nenrg, rnd)) {
			brd.commit_flip(flip);
			enrg = nenrg;
		}
		t--;
	}
	if (!t) {
		cerr << "cannot find solution" << endl;
		return -1;
	} else {
		cout << brd << endl;
		return 0;
	}
}
