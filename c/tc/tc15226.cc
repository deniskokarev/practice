/* TopCoder https://arena.topcoder.com/#/u/practiceCode/17356/73140/15226/2/331894 */
#include "gtest/gtest.h"
#include <vector>

using namespace std;

class ResistorFactory {
	static constexpr long long ONE = 1000000000LL;
	int pp[64];
	long double vv[64];
	vector<int> init_res;
	static int add_par(vector<int> &res, int i, int j) {
		res.push_back(i);
		res.push_back(j);
		res.push_back(1);
		return int(res.size()/3);
	}
	static int add_seq(vector<int> &res, int i, int j) {
		res.push_back(i);
		res.push_back(j);
		res.push_back(0);
		return int(res.size()/3);
	}
public:
	static long double play(const vector<int> &prog) {
		int sz = int(prog.size() / 3);
		long double rr[sz+1];
		rr[0] = ONE;
		for (int i=0; i < sz; i++) {
			switch (prog[i*3+2]) {
				case 1:
					rr[i+1] = rr[prog[i*3]] * rr[prog[i*3+1]] / (rr[prog[i*3]] + rr[prog[i*3+1]]);
					break;
				default:
					rr[i+1] = rr[prog[i*3]] + rr[prog[i*3+1]];
			}
		}
		return rr[sz];
	}
	ResistorFactory():pp{0},vv{0},init_res() {
		int p;
		pp[31] = p = add_par(init_res, 0, 0);
		vv[31] = (ONE >> 1);
		for (int i=2; i<33; i++) {
			pp[32 - i] = p = add_par(init_res, p, p);
			vv[32 - i] = ONE / (long double)(1LL << i);
		}
		pp[32] = 0;
		vv[32] = ONE;
		pp[33] = p = add_seq(init_res, 0, 0);
		vv[33] = (ONE << 1);
		for (int i=2; i<32; i++) {
			pp[32 + i] = p = add_seq(init_res, p, p);
			vv[32 + i] = (ONE << i);
		}
	}
	vector<int> construct(long long n) const {
		long double nld = n;
		vector<int> res(init_res);
		int l = pp[0];
		for (int i=63; i>0; i--) {
			if (nld >= vv[i]) {
				l = add_seq(res, l, pp[i]);
				nld -= vv[i];
			}
		}
		return res;
	}
};

static ResistorFactory rf;

TEST(TC, TC0) {
	long double dres = ResistorFactory::play(vector<int>());
	EXPECT_EQ(1000000000, dres);
}

TEST(TC, TC1) {
	long double dres = ResistorFactory::play(vector<int>({0, 0, 0, 0, 1, 0}));
	EXPECT_EQ(3000000000, dres);
}

TEST(TC, TC2) {
	long double dres = ResistorFactory::play(vector<int>({0, 0, 0, 0, 1, 0, 1, 2, 0, 3, 1, 1 }));
	EXPECT_NEAR(dres, 1428571428, 1);
}

TEST(TC, AC0) {
	long long c = 1;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC1) {
	long long c = 2;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC2) {
	long long c = 1000000000;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC3) {
	long long c = 3000000000;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC4) {
	long long c = 1200000000;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC5) {
	long long c = 1428571428;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC6) {
	long long c = 12000000001;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}

TEST(TC, AC7) {
	long long c = 333333333;
	vector<int> res =  rf.construct(c);
	long double dres = ResistorFactory::play(res);
	EXPECT_NEAR(c, dres, 1);
}
