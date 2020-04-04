class Solution {
	static constexpr int MOD = 1e9+7;
	struct E {
		uint64_t s, e;
		bool operator<(const E &o) const {
			return e>o.e;
		}
	};
public:
	static int maxPerformance(int n, const vector<int>& speed, const vector<int>& efficiency, int k) {
		const int sz = speed.size();
		vector<E> ee(sz);
		for (int i=0; i<sz; i++)
			ee[i] = E {(uint64_t)speed[i], (uint64_t)efficiency[i]};
		sort(ee.begin(), ee.end());
		uint64_t ans = 0;
		uint64_t ss = 0; // sum of speeds
		priority_queue<int,vector<int>,greater<int>> pq;
		for (int i=0; i<sz; i++) {
			pq.push(ee[i].s);
			ss += ee[i].s;
			if (pq.size() > k) {
				ss -= pq.top();
				pq.pop();
			}
			ans = max(ans, ss*ee[i].e);
		}
		return ans % MOD;
	}
};

