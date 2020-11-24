class Solution {
public:
	static int minOperationsMaxProfit(const vector<int>& customers, int boardingCost, int runningCost) {
		int q = 0;
		int mx = 0;
		int ans = -1;
		int sm = 0;
		int sz = customers.size();
		int i;
		for (i=0; i<sz; i++) {
			q += customers[i];
			sm += boardingCost * min(4, q);
			sm -= runningCost;
			if (sm > mx) {
				mx = sm;
				ans = i+1;
			}
			q -= min(4, q);
			//cerr << "(1) i=" << i << " sm=" << sm << endl;
		}
		sm += q / 4 * boardingCost * 4;
		sm -= q / 4 * runningCost;
		i += q / 4;
		if (sm > mx) {
			mx = sm;
			ans = i;
		}
		q %= 4;
		//cerr << "(2) i=" << i << " sm=" << sm << endl;
		if (q) {
			i++;
			sm += boardingCost * min(4, q);
			sm -= runningCost;
			if (sm > mx) {
				mx = sm;
				ans = i;
			}
			q -= min(4, q);
			//cerr << "(3) i=" << i << " sm=" << sm << endl;
		}
		return ans;
	}
};

