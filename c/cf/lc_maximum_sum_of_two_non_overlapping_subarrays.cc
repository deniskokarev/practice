#include <iostream>
#include <vector>
/* https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/ */
using namespace std;

class Solution {
    static int solve(const vector<int>& A, int L, int M) {
		int sz = A.size();
		vector<int64_t> sm(sz+1);
		for (int i=0; i<sz; i++)
			sm[i+1] = sm[i]+A[i];
        vector<int64_t> best_sml(sz+1);
		for (int i=L; i<=sz; i++)
			best_sml[i] = max(best_sml[i-1], sm[i]-sm[i-L]);
        vector<int64_t> best_smm(sz+1);
		for (int i=sz-M; i>0; i--)
			best_smm[i] = max(best_smm[i+1], sm[i+M]-sm[i]);
		int64_t ans = 0;
		for (int i=0; i<sz; i++)
			ans = max(ans, best_sml[i]+best_smm[i]);
		return ans;
    }
public:
    static int maxSumTwoNoOverlap(const vector<int>& A, int L, int M) {
		return max(solve(A, L, M), solve(A, M, L));
    }
};

int main(int argc, char **argv) {
	cout << Solution::maxSumTwoNoOverlap({0,6,5,2,2,5,1,9,4}, 1, 2) << endl;
	cout << Solution::maxSumTwoNoOverlap({3,8,1,3,2,1,8,9,0}, 3, 2) << endl;
	cout << Solution::maxSumTwoNoOverlap({2,1,5,6,0,9,5,0,3,8}, 4, 3) << endl;
	cout << Solution::maxSumTwoNoOverlap({1,0,3}, 1, 2) << endl;
	return 0;
}
