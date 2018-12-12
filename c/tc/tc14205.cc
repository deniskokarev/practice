/* TopCoder https://arena.topcoder.com/index.html#/u/practiceCode/17372/51498/14205/2/331921 */
#include "gtest/gtest.h"
#include <vector>
#include <string>
using namespace std;

class FriendlyRooks {
public:
	static void paint(const vector<string> &board, vector<vector<int>> &cboard, int i, int j, int color) {
		const int rsz = board.size();
		const int csz = board[0].size();
		for (int r=0; r<rsz; r++) {
			if (board[r][j] == 'R' && cboard[r][j] == 0) {
				cboard[r][j] = color;
				paint(board, cboard, r, j, color);
			}
		}
		for (int c=0; c<csz; c++) {
			if (board[i][c] == 'R' && cboard[i][c] == 0) {
				cboard[i][c] = color;
				paint(board, cboard, i, c, color);
			}
		}
	}
	static int getMinFriendlyColoring(const vector<string> &board) {
		const int rsz = board.size();
		const int csz = board[0].size();
		vector<vector<int>> cboard(rsz, vector<int>(csz, 0));
		int col = 0;
		for (int i=0; i<rsz; i++)
			for (int j = 0; j < csz; j++)
				if (board[i][j] == 'R')
					if (cboard[i][j] == 0)
						paint(board, cboard, i, j, ++col);
		return col;
	}
};

TEST(TC, TC0) { EXPECT_EQ(2, FriendlyRooks::getMinFriendlyColoring({".R.R", "R.R.", ".R.R"})); }

TEST(TC, TC1) { EXPECT_EQ(1, FriendlyRooks::getMinFriendlyColoring({"RRRRRRRRRRRRRRR"})); }

TEST(TC, TC2) { EXPECT_EQ(0, FriendlyRooks::getMinFriendlyColoring({"...............", "...............", "...............", "...............", "...............", "..............."})); }

TEST(TC, TC3) { EXPECT_EQ(1, FriendlyRooks::getMinFriendlyColoring({"....R..........", ".R...........R.", "....R..........", ".R........R....", "....R..........", "....R.....R...."})); }

TEST(TC, TC4) { EXPECT_EQ(6, FriendlyRooks::getMinFriendlyColoring({"R.........R", ".R.......R.", "..R.....R..", "...R...R...", "....R.R....", ".....R.....", "....R.R....", "...R...R...", "..R.....R..", ".R.......R.", "R.........R"})); }
