class Solution {
public:
	static int minSwaps(const vector<vector<int>> &grid) {
		int n = grid.size();
		vector<int> rsz(n);
		for (int i=0; i<n; i++)
			for (int j=n-1; j>=0 && grid[i][j] == 0; j--)
				rsz[i]++;
		int sw = 0;
		int l = 0;
		while (l < n-1) {
			for (; l < n-1 && rsz[l] >= n-l-1; l++);
			if (l < n-1) {
				int mx_r;
				for (mx_r=l+1; mx_r < n && rsz[mx_r] < n-l-1; mx_r++);
				if (mx_r < n) {
					while (mx_r > l) {
						swap(rsz[mx_r], rsz[mx_r-1]);
						mx_r--;
						sw++;
					}
				} else {
					return -1;
				}
			}
		}
#if 0
		cerr << "sw=" << sw << "\n";
		for (int i=0; i<n; i++)
			cerr << rsz[i] << ' ';
		cerr << '\n';
#endif
		return sw;
	}
};

