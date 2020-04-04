class Solution {
public:
    static int numTeams(const vector<int>& rating) {
		int sz = rating.size();
        vector<int> c_lt(sz);
        vector<int> c_gt(sz);
		for (int i=0; i<sz; i++)
			for (int j=i+1; j<sz; j++)
				if (rating[i] > rating[j])
					c_lt[i]++;
				else if (rating[i] < rating[j])
					c_gt[i]++;
		int ans = 0;
		for (int i=0; i<sz; i++)
			for (int j=i+1; j<sz; j++)
				if (rating[i] < rating[j])
					ans += c_gt[j];
				else if (rating[i] > rating[j])
					ans += c_lt[j];
		return ans;
		
    }
};

