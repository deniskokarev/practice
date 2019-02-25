#include <iostream>
#include <vector>
#include <queue>
/* CodeForces CF1130C problem */
using namespace std;


struct P {
	int x, y;
	P operator+(const P &o) const {
		return P {x+o.x, y+o.y};
	}
	int dist2(const P &o) const {
		return (x-o.x)*(x-o.x) + (y-o.y)*(y-o.y);
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	P f, t;
	cin >> f.y >> f.x;
	cin >> t.y >> t.x;
	vector<string> mm(n+2);
	mm[0] = string(n+2, '1');
	for (int i=1; i<=n; i++) {
		string s;
		cin >> s;
		mm[i] = "1"+s.substr(0,n)+"1";
	}
	mm[n+1] = string(n+2, '1');
	static P ofs[4] {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
	queue<P> qq;
	qq.push(f);
	mm[f.y][f.x] = '*';
	while (!qq.empty()) {
		P top = qq.front();
		qq.pop();
		for (auto o:ofs) {
			P np = top+o;
			if (mm[np.y][np.x] == '0') {
				mm[np.y][np.x] = '*';
				qq.push(np);
			}
		}
	}
	int ans;
	if (mm[t.y][t.x] == '*')
		ans = 0;
	else
		ans = INT_MAX;
	qq.push(t);
	mm[t.y][t.x] = '+';
	while (!qq.empty()) {
		P top = qq.front();
		qq.pop();
		for (auto o:ofs) {
			P np = top+o;
			if (mm[np.y][np.x] == '0') {
				mm[np.y][np.x] = '+';
				qq.push(np);
			}
		}
	}
	P i, j;
	for (i.x=1; i.x<=n; i.x++)
		for (i.y=1; i.y<=n; i.y++)
			for (j.x=1; j.x<=n; j.x++)
				for	(j.y=1; j.y<=n; j.y++)
					if (mm[i.y][i.x] == '*' && mm[j.y][j.x] == '+')
						ans = min(ans, i.dist2(j));
	cout << ans << endl;
	return 0;
}
