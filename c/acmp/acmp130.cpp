/* ACMP 130 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int BSZ = 8;

struct P {
	int x, y;
	P operator+(const P b) const {
		return P {x+b.x, y+b.y};
	}
	operator bool() const {
		return x>=0 && x<BSZ && y>=0 && y<BSZ;
	}
};

static const P kmoves[] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

int main(int argc, char **argv) {
	// epoch,color,row,col -> dist
	vector<vector<vector<vector<int>>>> dist(2, vector<vector<vector<int>>>(2, vector<vector<int>>(BSZ, vector<int>(BSZ, 0))));
	string sp1, sp2;
	cin >> sp1 >> sp2;
	P pp[2] = {P {sp1[0]-'a', sp1[1]-'1'}, P {sp2[0]-'a', sp2[1]-'1'}};
	int ans = -1;
	int epoch = 0;
	for (int color=0; color<2; color++)
		dist[epoch][color][pp[color].y][pp[color].x] = 1;
	// we know there will be a solution
	while (true) {
		epoch++;
		for (int color=0; color<2; color++) {
			auto &td = dist[epoch][color];
			auto &od = dist[(epoch+1)&1][color];
			auto &alttd = dist[epoch][(color+1)&1];
			for (int i=0; i<BSZ; i++) {
				for (int j=0; j<BSZ; j++) {
					if (od[i][j] == epoch) {
						P p = P {j, i};
						for (const P &km:kmoves) {
							const P np = p+km;
							if (np) {
								td[np.y][np.x] = epoch+1;
								if (td[np.y][np.x] == alttd[np.y][np.x]) {
									ans = epoch;
									goto end;
								}
							}
						}
					}
				}
			}
		}
	}
 end:
	cout << ans << endl;
	return 0;
}
