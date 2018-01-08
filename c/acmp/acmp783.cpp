/* ACMP 783 */
#include <iostream>
#include <vector>

/*
 * в описании задачи отсутствует важное замечание что область каждого рабочего не прямоугольная
 * а просто непрерывная
 */

using namespace std;

enum {
	B = 1,
	W = 2,
	Z = 3,
};

inline int alt(int color) {
	return color%2+1;
}

int walk(vector<vector<int>> &board, int x, int y, int color, int fill) {
	if (board[y][x] < Z && board[y][x] == color) {
		int cnt = 1;
		board[y][x] = fill;
		cnt += walk(board, x-1, y, alt(color), fill);
		cnt += walk(board, x+1, y, alt(color), fill);
		cnt += walk(board, x, y-1, alt(color), fill);
		cnt += walk(board, x, y+1, alt(color), fill);
		return cnt;
	} else {
		return 0;
	}
}

int main(int argc, char **argv) {
	vector<vector<int>> board(10, vector<int>(10, Z));
	for (int i=0; i<8; i++) {
		string s;
		cin >> s;
		for (int j=0; j<s.length(); j++)
			board[i+1][j+1] = (s[j]=='B')?B:W;
	}
	int n = 0;
	for (int i=1; i<=8; i++)
		for (int j=1; j<=8; j++)
			if (walk(board, j, i, board[i][j], Z+n+1) > 0)
				n++;
	cout << n << endl;
	for (int i=1; i<=8; i++) {
		for (int j=1; j<=8; j++)
			cerr << board[i][j]-Z << ' ';
		cerr << endl;
	}
	return 0;
}
