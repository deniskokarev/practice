class Solution {
public:
	static int minimumMountainRemovals(const vector<int>& nums) {
		int sz = nums.size();
		vector<int> l(sz), r(sz);
		vector<int> seq;
		for (int i=0; i<sz; i++) {
			int n = nums[i];
			auto it = lower_bound(seq.begin(), seq.end(), n);
			if (it == seq.end())
				seq.push_back(n);
			else if (*it > n)
				*it = n;
			l[i] = seq.size();
		}
#if 0
		for (int i=0; i<sz; i++)
			cerr << l[i] << ' ';
		cerr << '\n';
#endif
		seq.resize(0);
		for (int i=sz-1; i>=0; i--) {
			int n = nums[i];
			auto it = lower_bound(seq.begin(), seq.end(), n);
			if (it == seq.end())
				seq.push_back(n);
			else if (*it > n)
				*it = n;
			r[i] = seq.size();
		}
#if 0
		for (int i=0; i<sz; i++)
			cerr << r[i] << ' ';
		cerr << '\n';
#endif
		int mx = 0;
		for (int i=1; i<sz-1; i++)
			mx = max(mx, l[i]+r[i]-1);
		return sz-mx;
	}
};

