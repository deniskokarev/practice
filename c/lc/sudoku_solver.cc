/* https://leetcode.com/problems/sudoku-solver/ */

/**
 * constraints mask that we drag recursively through solution
 */
struct Msk {
	bitset<10> row[9]{0}; // row[r][d] == 1 means we have digit d in row r
	bitset<10> col[9]{0}; // col[c][d] == 1 means we have digit d in column c
	bitset<10> quad[3][3]{{0}}; // quad[r/3][c/3][d] == 1 means we have digit d in quadrant for row,col
};

struct Cell {
	int row, col;
};

/**
 * We need to place one of permitted digits in place[place_idx] Cell on board brd
 * Once place[place_idx] digit identified we proceed to place_idx-1 Cell recursively
 * msk constraint is updated as we progress. msk is undone on backtracking
 * When all place[] Cells covered print the solution
 * Return 1 if a solutions detected - brd will contain solution
 */
int solve(vector<vector<char>> &brd, Msk &msk, const vector<Cell> &place, int place_idx) {
	if (place_idx < 0) {
		return 1;
	} else {
		int cnt = 0;
		int r = place[place_idx].row;
		int c = place[place_idx].col;
		int q_r = r/3;
		int q_c = c/3;
		bitset<10> constr = msk.row[r] | msk.col[c] | msk.quad[q_r][q_c];
		for (int d=1; d<10; d++) {
			if (!constr[d]) {
				msk.row[r][d] = msk.col[c][d] = msk.quad[q_r][q_c][d] = 1;
				brd[r][c] = d+'0';
				if (solve(brd, msk, place, place_idx-1))
					return 1;
				msk.row[r][d] = msk.col[c][d] = msk.quad[q_r][q_c][d] = 0;
			}
		}
		return cnt;
	}
}

class Solution {
public:
    void solveSudoku(vector<vector<char>>& brd) {
        Msk msk;
        vector<Cell> place;
        for (int r=0; r<9; r++) {
            for (int c=0; c<9; c++) {
                if (brd[r][c] == '.') {
                    place.push_back({r,c});
                } else {
                    int d = brd[r][c]-'0';
		    msk.row[r][d] = 1;
                    msk.col[c][d] = 1;
                    msk.quad[r/3][c/3][d] = 1;
                }
            }
        }
        assert(solve(brd, msk, place, place.size()-1) > 0);
    }
};
