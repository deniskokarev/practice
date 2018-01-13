/* ACMP 130 */
#include <iostream>
#include <cstring>

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
	int dist[2][2][BSZ][BSZ];
	memset(dist, 0, sizeof(dist));
	string sp1, sp2;
	cin >> sp1 >> sp2;
	P pp[2] = {P {sp1[0]-'a', sp1[1]-'1'}, P {sp2[0]-'a', sp2[1]-'1'}};
	int ans = -1;
	int epoch = 0;
	for (int color=0; color<2; color++)
		dist[epoch][color][pp[color].y][pp[color].x] = 1;
	int sqc; // when all squares are filled we have no more hope to find solution
	do {
		epoch++;
		for (int color=0; color<2; color++) {
			sqc = 0;
			auto &td = dist[epoch&1][color];
			auto &od = dist[(epoch+1)&1][color];
			auto &alttd = dist[epoch&1][(color+1)&1];
			for (int i=0; i<BSZ; i++) {
				for (int j=0; j<BSZ; j++) {
					if (od[i][j] == epoch) {
						P p = P {j, i};
						for (const P &km:kmoves) {
							const P np = p+km;
							if (np) {
								td[np.y][np.x] = epoch+1;
								sqc++;
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
	} while(sqc < BSZ*BSZ);
 end:
	cout << ans << endl;
	return 0;
}
