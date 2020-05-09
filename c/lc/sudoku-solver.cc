/**
 * https://leetcode.com/problems/sudoku-solver/
 * solumated annealing optimization
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <set>
#include <random>

class Solution {
	struct STAT {
		int score;
		int occ[9][9];
		int q[3][3][9];
		STAT():score{0},occ{{0}},q{{{0}}} {
		}
		void remove(int d, int r, int c) {
			score -= (q[r/3][c/3][d]-1);
			q[r/3][c/3][d]--;
			score -= (occ[r][c]-1);
			occ[r][c]--;
		}
		void add(int d, int r, int c) {
			q[r/3][c/3][d]++;
			score += (q[r/3][c/3][d]-1);
			occ[r][c]++;
			score += (occ[r][c]-1);
		}
	};
	// a move consists of a digit and 2 columns to swap
	struct MV {
		int d, c1, c2;
	};
	static int flip_dig_rows(const std::vector<std::vector<char>>& board, int row[9][9], STAT &stat, const MV &mv) {
		int r1 = row[mv.d][mv.c1];
		int r2 = row[mv.d][mv.c2];
		stat.remove(mv.d, r1, mv.c1);
		stat.remove(mv.d, r2, mv.c2);
		std::swap(row[mv.d][mv.c1], row[mv.d][mv.c2]);
		std::swap(r1, r2);
		stat.add(mv.d, r1, mv.c1);
		stat.add(mv.d, r2, mv.c2);
		return stat.score;
	}
	// simulated annealing transition rule
	static bool transition(int t, int e1, int e2, std::mt19937 &rnd) {
		double de = e2-e1;
		if (de < 0) {
			return true;
		} else {
			constexpr double magic = 3e7;
			double p = exp(-de*magic/t);
			double r = double(rnd())/std::mt19937::max();
			return r<p;
		}
	}
	static int anneal(std::vector<std::vector<char>>& board, int row[9][9], STAT &stat, const MV mv[], int mv_sz) {
		int t = 1e7; // hope to find solution in less than 1e7 steps
		std::mt19937 rnd(0);
		int e = stat.score;
		while (t && e) {
			const MV &m = mv[int64_t(rnd())*mv_sz/std::mt19937::max()];
			flip_dig_rows(board, row, stat, m);
			if (!transition(t, e, stat.score, rnd))
				flip_dig_rows(board, row, stat, m); // flip back
			e = stat.score;
			t--;
		}
		std::cerr << "t=" << t << " e=" << e << "\n";
		//prn(row2brd(row));
		return e;
	}
	static std::vector<std::vector<char>> reconstruct_board(int row[9][9]) {
		std::vector<std::vector<char>> board(9, std::vector<char>(9, '0'));
		for (int d=0; d<9; d++)
			for (int c=0; c<9; c++)
				board[row[d][c]][c] += d+1;
		return board;
	}
public:
	static void solveSudoku(std::vector<std::vector<char>>& board) {
		STAT stat;
		int row[9][9];	// row[d][c] says which row the digit d stands in column c
		MV mv[9*9*8/2];	// permitted moves
		int mv_sz = 0;
		// configure a starting position with fixed assignments and permitted moves
		for (int d=0; d<9; d++) {
			for (int c=0; c<9; c++)
				row[d][c] = -1;
			std::set<int> ad {0,1,2,3,4,5,6,7,8};
			// statically assign all known places
			for (int r=0; r<9; r++) {
				for (int c=0; c<9; c++) {
					if (board[r][c] == d+'1') {
						row[d][c] = r;
						ad.erase(r);
					}
				}
			}
			for (int c=0; c<9; c++) {
				if (row[d][c] < 0) {
					row[d][c] = *ad.begin();
					ad.erase(ad.begin());
				}
			}
			// make sure fixed places statically assigned
			for (int r=0; r<9; r++)
				for (int c=0; c<9; c++)
					assert(board[r][c] != d+'1' || row[d][c] == r);
			// permitted moves must exclude fixed assignments
			for (int c1=0; c1<9; c1++)
				for (int c2=c1+1; c2<9; c2++)
					if (board[row[d][c1]][c1] != d+'1' && board[row[d][c2]][c2] != d+'1')
						mv[mv_sz++] = MV {d, c1, c2};
			// compute the initial score
			for (int c=0; c<9; c++)
				stat.add(d, row[d][c], c);
		}
		// run simulation
		int e = anneal(board, row, stat, mv, mv_sz);
		assert(e == 0);
		board = reconstruct_board(row);
    }
};

using namespace std;

static void prn(const vector<vector<char>>& board) {
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++)
			cerr << board[i][j] << ' ';
		cerr << '\n';
	}
	cerr << '\n';
}

static vector<vector<char>> board0(9, vector<char>(9, '.'));

static vector<vector<char>> board1 {
	{'5','3','.','.','7','.','.','.','.'},
	{'6','.','.','1','9','5','.','.','.'},
	{'.','9','8','.','.','.','.','6','.'},
	{'8','.','.','.','6','.','.','.','3'},
	{'4','.','.','8','.','3','.','.','1'},
	{'7','.','.','.','2','.','.','.','6'},
	{'.','6','.','.','.','.','2','8','.'},
	{'.','.','.','4','1','9','.','.','5'},
	{'.','.','.','.','8','.','.','7','9'}
};

static vector<vector<char>> board2 {
	{'.','.','9','7','4','8','.','.','.'},
	{'7','.','.','.','.','.','.','.','.'},
	{'.','2','.','1','.','9','.','.','.'},
	{'.','.','7','.','.','.','2','4','.'},
	{'.','6','4','.','1','.','5','9','.'},
	{'.','9','8','.','.','.','3','.','.'},
	{'.','.','.','8','.','3','.','2','.'},
	{'.','.','.','.','.','.','.','.','6'},
	{'.','.','.','2','7','5','9','.','.'}
};

static vector<vector<char>> board3 {
	{'5','1','9','7','4','8','6','3','2'},
	{'7','8','3','6','5','2','4','1','9'},
	{'4','2','6','1','3','9','8','7','5'},
	{'3','5','7','9','8','6','2','4','1'},
	{'2','6','4','3','1','7','5','9','8'},
	{'1','9','8','5','2','4','3','6','7'},
	{'9','7','5','8','6','3','1','2','4'},
	{'8','3','2','4','9','1','7','5','6'},
	{'6','4','1','2','7','5','9','8','3'}
};

static vector<vector<char>> board4 {
	{'.','.','.','2','.','.','.','6','3'},
	{'3','.','.','.','.','5','4','.','1'},
	{'.','.','1','.','.','3','9','8','.'},
	{'.','.','.','.','.','.','.','9','.'},
	{'.','.','.','5','3','8','.','.','.'},
	{'.','3','.','.','.','.','.','.','.'},
	{'.','2','6','3','.','.','5','.','.'},
	{'5','.','3','7','.','.','.','.','8'},
	{'4','7','.','.','.','1','.','.','.'}
};

static vector<vector<char>> board5 {
	{'.','.','.','.','.','7','.','.','9'},
	{'.','4','.','.','8','1','2','.','.'},
	{'.','.','.','9','.','.','.','1','.'},
	{'.','.','5','3','.','.','.','7','2'},
	{'2','9','3','.','.','.','.','5','.'},
	{'.','.','.','.','.','5','3','.','.'},
	{'8','.','.','.','2','3','.','.','.'},
	{'7','.','.','.','5','.','.','4','.'},
	{'5','3','1','.','7','.','.','.','.'}
};


int main(int argc, char **argv) {
	for (auto &b:{board0, board1, board2, board3, board4, board5}) {
		auto board = b;
		prn(board);
		Solution::solveSudoku(board);
		prn(board);
	}
	return 0;
}
