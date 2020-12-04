class Solution {
	using LI = list<int>;
	using LIT = list<int>::iterator;
	static void prune_one(LI &sel, stack<LIT> &gt) {
		if (gt.empty()) {
			sel.pop_back();
		} else {
			auto it = gt.top();
			auto pit = prev(it);
			auto nit = next(it);
			sel.erase(it);
			gt.pop();
			if (*pit > *nit)
				gt.push(pit);
		}
	}
public:
	static vector<int> mostCompetitive(const vector<int>& nums, int k) {
		stack<LIT> gt; // positions of *LIT > *next(LIT)
		LI sel;
		int sz = nums.size();
		sel.push_front(nums[sz-1]);
		for (int i=sz-2; i>=0 && i>=sz-k; i--) {
			sel.push_front(nums[i]);
			if (*sel.begin() > *next(sel.begin()))
				gt.push(sel.begin());
		}
		for (int i=sz-k-1; i>=0; i--) {
			if (nums[i] <= sel.front()) {
				sel.push_front(nums[i]);
				prune_one(sel, gt);
			}
		}
		return {sel.begin(), sel.end()};
	}
};
