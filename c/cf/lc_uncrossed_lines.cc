#include <iostream>
#include <vector>
/* https://leetcode.com/problems/uncrossed-lines/ */
using namespace std;

class Solution {
public:
    static const int maxUncrossedLines(const vector<int>& A, const vector<int>& B) {
		vector<vector<int>> sol(A.size()+1, vector<int>(B.size()+1));
		for (int i=0; i<A.size(); i++) {
			for (int j=0; j<B.size(); j++) {
				if (A[i] == B[j])
					sol[i+1][j+1] = max(sol[i][j+1], max(sol[i][j]+1, sol[i+1][j]));
				else
					sol[i+1][j+1] = max(sol[i][j+1], max(sol[i][j], sol[i+1][j]));
			}
		}
#if 0
		for (auto &r:sol) {
			for (auto a:r)
				cerr << a << ' ';
			cerr << '\n';
		}
#endif
		return sol[A.size()][B.size()];
    }
};

int main(int argc, char **argv) {
	cout << Solution::maxUncrossedLines({1,4,2}, {1,2,4}) << endl;
	cout << Solution::maxUncrossedLines({2,5,1,2,5}, {10,5,2,1,5,2}) << endl;
	cout << Solution::maxUncrossedLines({1,3,7,1,7,5}, {1,9,2,5,1}) << endl;
	cout << Solution::maxUncrossedLines({}, {}) << endl;
	return 0;
}
