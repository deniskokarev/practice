// https://leetcode.com/problems/random-pick-with-weight/
class Solution {
	int sz;
	vector<int> sm;
	int64_t tot;
	mt19937 rnd;
public:
	Solution(const vector<int>& w):sz(w.size()),sm(sz+1),rnd(0) {
		sm[0] = -1; // ! important, otherwise we cannot use lower_bound()
		for (int i=1; i<=sz; i++)
			sm[i] = sm[i-1] + w[i-1];
		tot = sm[sz]-sm[0];
	}
	int pickIndex() {
		int k = tot*rnd()/mt19937::max();
		auto fnd = lower_bound(sm.begin(), sm.end(), k);
		return fnd-sm.begin()-1;
	}
};

