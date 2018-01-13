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
	vector<vector<vector<int>>> dist(2, vector<vector<int>>(BSZ, vector<int>(BSZ, 0)));
	string sp1, sp2;
	cin >> sp1 >> sp2;
	P pp[2] = {P{(short)(sp1[0]-'a'), (short)(sp1[1]-'1')}+P{2,2}, P{(short)(sp2[0]-'a'), (short)(sp2[1]-'1')}+P{2,2}};
	queue<P> qq[2];
	for (int i=0; i<2; i++) {
		qq[i].push(pp[i]);
		dist[i][pp[i].y][pp[i].x] = 0;
	}
	int ans = -1;
	int epoch = 0;
	while (qq[0].size() < BSZ*BSZ*BSZ) {
		epoch++;
		for (int i=0; i<2; i++) {
			for (int qsz = qq[i].size(); qsz>0; qsz--) {
				const P &np = qq[i].front();
				for (const P &km:kmoves) {
					const P nnp = np+km;
					if (nnp.y >= 0 && nnp.y < BSZ && nnp.x >= 0 && nnp.x < BSZ) {
						dist[i][nnp.y][nnp.x] = epoch;
						if (i == 1 && dist[1][nnp.y][nnp.x] == dist[0][nnp.y][nnp.x]) {
							ans = epoch;
							goto end;
						}
					}
				}
				qq[i].pop();
			}
		}
	}
 end:
	cout << ans << endl;
	return 0;
}
