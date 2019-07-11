#include <iostream>
#include <vector>
#include <map>
#include <list>
/* https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/ */
using namespace std;

class Solution {
public:
    static bool canThreePartsEqualSum(vector<int>& A) {
		int sz = A.size()+1;
        vector<int> sa(sz);
		copy(A.begin(), A.end(), sa.begin()+1);
		for (int i=1; i<sz; i++)
			sa[i] += sa[i-1];
		map<int,list<int>> rsa;
		for (int i=sz-1; i>=0; i--)
			rsa[sa[sz-1]-sa[i]].push_back(i);
		for (int i=1; i<sz; i++) {
			for (auto j:rsa[sa[i]]) {
				if (j>i && sa[i] == sa[j]-sa[i]) {
					cerr << "i=" << i << " j=" << j << " sum=" << sa[i] << endl;
					return true;
				}
			}
		}
		return false;
    }
};

void test1() {
	vector<int> a {0,2,1,-6,6,-7,9,1,2,0,1};
	cerr << Solution::canThreePartsEqualSum(a) << endl;
}

void test2() {
	vector<int> a {0,2,1,-6,6,7,9,-1,2,0,1};
	cerr << Solution::canThreePartsEqualSum(a) << endl;
}

int main(int argc, char **argv) {
	test1();
	test2();
	return 0;
}
