#include <iostream>
#include <vector>
#include <set>
/* https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/ */
using namespace std;

class Solution {
public:
    static bool queryString(string S, int N) {
		set<int> res;
		res.insert(0);
        for (int w=1; w<32; w++) {
			int64_t n = 0;
			int i;
			int64_t p2 = 1LL<<w;
			for (i=0; i<w && i<S.size(); i++) {
				n *= 2;
				n += S[i]-'0';
			}
			res.insert(n);
			for (; i<S.size(); i++) {
				n *= 2;
				n += S[i]-'0';
				n -= p2 * (S[i-w]-'0');
				res.insert(n);
			}
		}
		vector<int> vres(res.size());
		copy(res.begin(), res.end(), vres.begin());
		return (vres.size()>N && vres[N] == N);
    }
};

void test1() {
	cerr << Solution::queryString("0110", 3) << endl;
}

void test2() {
	cerr << Solution::queryString("0110", 4) << endl;
}

int main(int argc, char **argv) {
	test1();
	test2();
	return 0;
}
