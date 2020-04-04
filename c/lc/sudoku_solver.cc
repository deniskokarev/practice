#include <iostream>
#include <vector>
#include <cassert>
/* https://leetcode.com/problems/sudoku-solver/ */
using namespace std;

static vector<int> get_nbit(int n) {
	vector<int> res(1U << n);
	for (int i=0; i<1<<n; i++) {
		int cnt = 0;
		for (int j=0; j<30; j++)
			cnt += ((i&1<<j) != 0);
		res[i] = cnt;
	}
	return res;
}

static const vector<int> nbit = get_nbit(10);

static int get_nonet(int y, int x) {
	int y3 = y/3;
	int x3 = x/3;
	return y3 * 3 + x3;
}

static int get_dig(unsigned n) {
	for (int b=1, d=1; b<1<<30; b*=2,d++)
		if (n & b)
			return d;
	return 0;
}


static bool recalc(int *y, int *x,
				   const vector<unsigned> &ny,
				   const vector<unsigned> &nx,
				   const vector<unsigned> &nh,
				   vector<vector<unsigned>> &sol,
				   vector<vector<char>>& board,
				   int szy,
				   int szx)
{
	int mnx = -1, mny = -1, mn = 11;
	for (int y=0; y<szy; y++) {
		for (int x=0; x<szx; x++) {
			if (board[y][x] == '.') {
				unsigned &d = sol[y][x];
				d &= ny[y];
				d &= nx[x];
				d &= nh[get_nonet(y, x)];
				int n = nbit[d];
				if (n >= 1 && n < mn) {
					mn = n;
					mny = y;
					mnx = x;
				}
			}
		}
	}
	*y = mny;
	*x = mnx;
	return (mny >= 0);
}

static void neg_apply(int y, int x, int d,
				  vector<unsigned> &ny,
				  vector<unsigned> &nx,
				  vector<unsigned> &nh)
{
	ny[y] &= ~d;
	nx[x] &= ~d;
	nh[get_nonet(y, x)] &= ~d;
}

static bool check(const vector<vector<char>>& board) {
	bitset<9> ny[9];
	bitset<9> nx[9];
	bitset<9> nh[9];
	for (int y=0; y<9; y++) {
		for (int x=0; x<9; x++) {
			assert(board[y][x] >= '1' && board[y][x] <= '9');
			int d = board[y][x] - '1';
			ny[y][d] = 1;
			nx[x][d] = 1;
			nh[get_nonet(y, x)][d] = 1;
		}
	}
	for (int i=0; i<9; i++) {
		//cerr << "i=" << i << " ny=" << ny[i] << " nx=" << nx[i] << " nh=" << nh[i] << endl;
#if 1
		assert(ny[i] == 511);
		assert(nx[i] == 511);
		assert(nh[i] == 511);
#endif
	}
	return true;
}

class Solution {
public:
	static void solveSudoku(vector<vector<char>>& board) {
		const int szy = int(board.size());
		const int szx = int(board[0].size());
		assert(szy == szx && szx == 9);
		vector<unsigned> ny(szy, ~0U);
		vector<unsigned> nx(szy, ~0U);
		vector<unsigned> nh(9, ~0U);
		vector<vector<unsigned>> sol(szy, vector<unsigned>(szx));
		for (int y=0; y<szy; y++) {
			for (int x=0; x<szx; x++) {
				unsigned d = ((1U<<9)-1);
				if (board[y][x] == '.') {
					sol[y][x] = d;
				} else {
					d ^= 1U << (board[y][x] - '1');
					ny[y] &= d;
					nx[x] &= d;
					nh[get_nonet(y, x)] &= d;
				}
			}
		}
		int x, y;
		while (recalc(&y, &x, ny, nx, nh, sol, board, szy, szx)) {
			int d = get_dig(sol[y][x]);
			int dp2 = 1<<(d-1);
			sol[y][x] = 0;
			board[y][x] = d + '0';
			neg_apply(y, x, dp2, ny, nx, nh);
		}
		//check(board);
	}
};

static vector<vector<char>> conv(const vector<string> &bb) {
	vector<vector<char>> res(9, vector<char>(9));
	for (int i=0; i<9; i++)
		for (int j=0; j<9; j++)
			res[i][j] = bb[i][j];
	return res;
}

static string conv(const vector<vector<char>> &bb) {
	string s;
	for (auto &b:bb) {
		for (auto c:b) {
			s += c;
			s += ' ';
		}
		s += '\n';
	}
	return s;
}

int main(int argc, char **argv) {
	auto b = conv({
			    ".........",
				".........",
				".........",
				".........",
				".........",
			    ".........",
				".........",
				".........",
				"........."
				});
	Solution::solveSudoku(b);
	//cout << conv(b);
	vector<vector<char>> b2 = {
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
	Solution::solveSudoku(b2);
	cout << conv(b2);
	return 0;
}
