#include <iostream>
#include <vector>
#include <map>

/* https://leetcode.com/contest/weekly-contest-132/problems/longest-arithmetic-sequence/ */

using namespace std;

class Solution {
public:
    static int longestArithSeqLength(vector<int>& A) {
		int ans = 0;
		map<pair<int,int>,int> cnt;
		for (int i=1; i<A.size(); i++) {
			for (int j=0; j<i; j++) {
				int d = A[i]-A[j];
				if (d != 0) {
					int &co = cnt[make_pair(A[j],d)];
					int &cn = cnt[make_pair(A[i],d)];
					cn = max(cn, co+1);
					ans = max(ans, cn);
				}
			}
		}
		return ans+1;
    }
};

void test1() {
	vector<int> in {3,6,9,12};
	cout << Solution::longestArithSeqLength(in) << "\n";
}

void test2() {
	vector<int> in {9,4,7,2,10};
	cout << Solution::longestArithSeqLength(in) << "\n";
}

void test3() {
	vector<int> in {20,1,15,3,10,5,8};
	cout << Solution::longestArithSeqLength(in) << "\n";
}

void test4() {
	vector<int> in {12,28,13,6,34,36,53,24,29,2,23,0,22,25,53,34,23,50,35,43,53,11,48,56,44,53,31,6,31,57,46,6,17,42,48,28,5,24,0,14,43,12,21,6,30,37,16,56,19,45,51,10,22,38,39,23,8,29,60,18};
	cout << Solution::longestArithSeqLength(in) << "\n";
}

int main(int argc, char **argv) {
	test1();
	test2();
	test3();
	test4();
	return 0;
}
