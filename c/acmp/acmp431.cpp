#include <iostream>
#include <vector>
#include <queue>
/* ACMP 431 */
using namespace std;

struct P {
	int x, y;
	bool operator==(const P &o) const {
		return x == o.x && y == o.y;
	}
};

const static P mv[8] = {{+2, +1}, {+1, +2}, {-1, +2}, {-2, +1}, {-2, -1}, {-1, -2}, {+1, -2}, {+2, -1}};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<string> bb(n+4);
	bb[0] = bb[1] = bb[n+2] = bb[n+3] = string(n+4, '#');
	for (int i=2; i<=n+1; i++) {
		string s;
		cin >> s;
		bb[i] = "##"+s+"##";
		
	}
	P pp[2];
	int ip = 0;
	for (int y=0; y<n+4; y++)
		for (int x=0; x<n+4; x++)
			if (bb[y][x] == '@')
				pp[ip++] = P {x, y};
	const P &s = pp[0];
	const P &e = pp[1];
	// bfs
	vector<vector<P>> bt(n+4, vector<P>(n+4, P {0, 0}));
	queue<P> qq;
	qq.push(s);
	bt[s.y][s.x] = s;
	while (!qq.empty()) {
		P p = qq.front();
		if (p == e)
			break;
		qq.pop();
		for (auto m:mv) {
			if (bb[p.y+m.y][p.x+m.x] != '#' && bt[p.y+m.y][p.x+m.x] == P {0, 0}) {
				qq.push(P {p.x+m.x, p.y+m.y});
				bt[p.y+m.y][p.x+m.x] = p;
			}
		}
	}
	if (qq.empty()) {
		cout << "Impossible\n";
	} else {
		for (P p=e; !(p == s); p=bt[p.y][p.x])
			bb[p.y][p.x] = '@';
		for (int i=2; i<n+2; i++)
			cout << bb[i].substr(2, n) << '\n';
	}
	return 0;
}
