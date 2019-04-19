#include <iostream>
#include <vector>
#include <queue>
/* https://leetcode.com/problems/best-sightseeing-pair */
using namespace std;

class Solution {
public:
    static int maxScoreSightseeingPair(vector<int>& A) {
		int mx = -1;
		for (int w=1; w<1001; w++)
			for (int i=w; i<A.size(); i++)
				mx = max(mx, A[i]+A[i-w]-w);
		return mx;
    }
};

void test1() {
	vector<int> a {8,1,5,2,6};
	cerr << Solution::maxScoreSightseeingPair(a) << endl;
}

int main(int argc, char **argv) {
	test1();
	return 0;
}
