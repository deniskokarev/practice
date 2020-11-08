class Solution {
	static constexpr int MOD = 1e9+7;
public:
	static int maxProfit(const vector<int>& inventory, int orders) {
		int sz = inventory.size();
		vector<int> sinv(inventory);
		sort(sinv.begin(), sinv.end());
		stack<pair<int64_t,int>> stack;
		stack.push({0,1});
		int l = 1;
		for (int i=1; i<sz; i++) {
			if (sinv[i-1] == sinv[i]) {
				l++;
			} else {
				stack.push({sinv[i-1],l});
				l = 1;
			}
		}
		stack.push({sinv[sz-1],l});
		int64_t sm = 0;
		int ord = 0;
		while (stack.top().first) {
			auto top = stack.top();
			stack.pop();
			int64_t hi = top.first;
			int64_t lo = stack.top().first;
			l = top.second;
			int d = (hi-lo)*l;
			if (ord + d <= orders) {
				sm += (hi*(hi+1) - lo*(lo+1))/2*l;
				sm %= MOD;
				stack.top().second += l;
				ord += d;
			} else {
				int h = (orders-ord)/l;
				lo = hi - h;
				d = (hi-lo)*l;
				ord += d;
				sm += (hi*(hi+1) - lo*(lo+1))/2*l;
				sm += (orders - ord) * lo;
				sm %= MOD;
				break;
			}
		}
		return sm;
	}
};

