#include <bits/stdc++.h>

using namespace std;

struct P {
	int r, c;
	int p;
	bool operator>(const P &o) const {
		return p > o.p;
	}
};

static const P MV[] = {{-1, 0, 0}, {+1, 0, 0}, {0, -1, 0}, {0, +1, 0}};

struct PoisonedSwamp {
	static string cross(const vector <string> &swamp) {
		int h = swamp.size();
		int w = swamp[0].size();
		vector<string> board(h+2, string(w+2, '#'));
		for (int r=0; r<h; r++)
			for (int c=0; c<w; c++)
				board[r+1][c+1] = swamp[r][c];
		priority_queue<P, vector<P>, greater<P>> qq;
		vector<vector<vector<bool>>> seen(h+2, vector<vector<bool>>(w+2, vector<bool>(10)));
		qq.push({1,1,0});
		while (!qq.empty()) {
			P top = qq.top();
			qq.pop();
			if (top.r == h && top.c == w)
				return "possible";
			if (!seen[top.r][top.c][top.p]) {
				seen[top.r][top.c][top.p] = true;
				for (const P &mv:MV) {
					P np(top);
					np.r += mv.r;
					np.c += mv.c;
					if (board[np.r][np.c] == '#') {
						continue;
					} else if (board[np.r][np.c] == 'S') {
						np.p = 0;
					} else if (board[np.r][np.c] != '.') {
						np.p += board[np.r][np.c] - '0';
					}
					if (np.p < 10)
						qq.push(np);
				 }
			}
		}
		return "impossible";
	}
};

