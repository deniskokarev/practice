class Solution {
public:
	static vector<vector<int>> restoreMatrix(const vector<int>& sm_row, const vector<int>& sm_col) {
		vector<int> row(sm_row);
		vector<int> col(sm_col);
		int h = sm_row.size();
		int w = sm_col.size();
		vector<vector<int>> mm(h, vector<int>(w));
		for (int r=0; r<h; r++) {
			for (int c=0; c<w; c++) {
				mm[r][c] = min(row[r], col[c]);
				row[r] -= mm[r][c];
				col[c] -= mm[r][c];
			}
		}
		return mm;
	}
};

