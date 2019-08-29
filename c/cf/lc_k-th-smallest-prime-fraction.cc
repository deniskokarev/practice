#include <iostream>
#include <vector>
#include <queue>
/* https://leetcode.com/problems/k-th-smallest-prime-fraction/ */
using namespace std;

struct Q {
    int p, q;
};

struct Qcmp {
	const vector<int> &A;
    bool operator()(const Q &a, const Q &b) const {
        return A[a.p]*A[b.q] > A[b.p]*A[a.q];
    }
};

class Solution {
public:
    static vector<int> kthSmallestPrimeFraction(const vector<int>& A, int K) {
		Qcmp qcmp = Qcmp{A};
        priority_queue<Q,vector<Q>,Qcmp> qq(qcmp);
        int sz = A.size();
        vector<vector<int>> ord(sz, vector<int>(sz));
        int seq = 1;
        qq.push(Q{0, sz-1});
        while(!qq.empty()) {
            Q t = qq.top();
            qq.pop();
            if (!ord[t.p][t.q]) {
				if (seq == K)
					return vector<int>{A[t.p], A[t.q]};
                ord[t.p][t.q] = seq++;
                if (t.p+1 < t.q)
                    qq.push(Q{t.p+1, t.q});
                if (t.q-1 > t.p)
                    qq.push(Q{t.p, t.q-1});
            }
        }
        return vector<int>{-1,-1};
    }
};

int main(int argc, char **argv) {
	auto res = Solution::kthSmallestPrimeFraction({1,2,3,5}, 3);
	cout << res[0] << " / " << res[1] << endl;
	return 0;
}
