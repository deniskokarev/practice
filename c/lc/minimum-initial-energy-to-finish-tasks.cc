class Solution {
	struct T {
		int a, mn;
		bool operator<(const T &o) const {
			int d = mn-a;
			int od = o.mn-o.a;
			return d<od;
		}
	};
	static bool can_complete(const vector<T> &tt, int e) {
		int sz = tt.size();
		for (int i=sz-1; i>=0; i--) {
			if (tt[i].mn > e)
				return false;
			e -= tt[i].a;
		}
		return true;
	}
public:
	static int minimumEffort(const vector<vector<int>>& tasks) {
		vector<T> tt;
		for (auto &t:tasks)
			tt.push_back(T{t[0],t[1]});
		sort(tt.begin(), tt.end());
		int f=0, t=INT_MAX;
		while (f<=t) {
			int mid = f+(t-f)/2;
			if (can_complete(tt, mid))
				t = mid-1;
			else
				f = mid+1;
		}
		return t+1;
	}
};

