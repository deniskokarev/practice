class Solution {
public:
	static int largestSubmatrix(vector<vector<int>>& mm) {
		int h = mm.size();
		int w = mm[0].size();
		for (int r=h-2; r>=0; r--)
			for (int c=0; c<w; c++)
				mm[r][c] = (mm[r+1][c]+1) * mm[r][c];
		int mx = 0;
		for (auto &row:mm) {
			sort(begin(row), end(row), std::greater<int>());
			int w = 1;
			for (int l:row) {
				mx = max(mx, w*l);
				w++;
			}
		}
		return mx;
	}
};
