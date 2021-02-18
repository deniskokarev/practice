class Solution {
public:
	static int kthLargestValue(vector<vector<int>>& mat, int k) {
		int h = mat.size();
		int w = mat[0].size();
		vector<int> res;
		res.push_back(mat[0][0]);
		for (int i=1; i<w; i++)
			res.push_back(mat[0][i] = mat[0][i] ^ mat[0][i-1]);
		for (int i=1; i<h; i++)
			res.push_back(mat[i][0] = mat[i][0] ^ mat[i-1][0]);
		for (int r=1; r<h; r++)
			for (int c=1; c<w; c++)
				res.push_back(mat[r][c] = mat[r-1][c] ^ mat[r][c-1] ^ mat[r-1][c-1] ^ mat[r][c]);
		nth_element(res.begin(), res.begin()+k-1, res.end(), greater<int>());
		return res[k-1];
	}
};
