/* ACMP 130 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct P {
	short x, y;
};

inline P operator+(const P a, const P b) {
	return P {(short)(a.x+b.x), (short)(a.y+b.y)};
}

static const P kmoves[] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

constexpr int BSZ = 8;

int main(int argc, char **argv) {
	vector<vector<vector<int>>> dist(2, vector<vector<int>>(BSZ+4, vector<int>(BSZ+4, 0)));
	for (int i=0; i<2; i++)
		for (int j=2; j<BSZ+2; j++)
			for (int k=2; k<BSZ+2; k++)
				dist[i][j][k] = INT_MAX;
	string sp1, sp2;
	cin >> sp1 >> sp2;
	P pp[2] = {P{(short)(sp1[0]-'a'), (short)(sp1[1]-'1')}+P{2,2}, P{(short)(sp2[0]-'a'), (short)(sp2[1]-'1')}+P{2,2}};
	for (int i=0; i<2; i++) {
		queue<P> qq;
		qq.push(pp[i]);
		dist[i][pp[i].y][pp[i].x] = 0;
		while (qq.size() > 0) {
			const P &np = qq.front();
			for (const P &km:kmoves) {
				const P nnp = np+km;
				if (dist[i][np.y][np.x]+1<dist[i][nnp.y][nnp.x]) {
					dist[i][nnp.y][nnp.x] = dist[i][np.y][np.x]+1;
					qq.push(nnp);
				}
			}
			qq.pop();
		}
	}
	int mn = INT_MAX;
	for (int i=2; i<BSZ+2; i++)
		for (int j=2; j<BSZ+2; j++)
			mn = min(mn, max(dist[0][i][j], dist[1][i][j]));
	cout << mn << endl;
	return 0;
}
