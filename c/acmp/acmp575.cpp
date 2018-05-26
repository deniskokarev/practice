#include <iostream>
#include <iomanip>
#include <cstring>
/* ACMP 575 */
using namespace std;

struct P {
	int x, y;
};

// 4 points comparison 2 horiz, 2 vert and 2 diag
P ppcmp[6][2] {{{0,0},{0,1}}, {{1,0},{1,1}}, {{0,0},{1,0}}, {{0,1},{1,1}}, {{0,0},{1,1}}, {{0,1},{1,0}}};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int aa[n*10][m*10];
	for (int y=0; y<n; y++) {
		for (int x=0; x<m; x++) {
			int a;
			cin >> a;
			for (int dy=0; dy<10; dy++)
				for (int dx=0; dx<10; dx++)
					aa[y*10+dy][x*10+dx] = a;
		}
	}
	char res[n*10][m*10];
	memset(res, 0, sizeof(res));
	for (int y=0; y<n*10-1; y++)
		for (int x=0; x<m*10-1; x++)
			for (auto &pc:ppcmp)
				if (aa[y+pc[0].y][x+pc[0].x] != aa[y+pc[1].y][x+pc[1].x])
					res[y+pc[0].y][x+pc[0].x] = res[y+pc[1].y][x+pc[1].x] = 1;
	int cnt = 0;
	for (int y=1; y<n*10-1; y++)
		for (int x=1; x<m*10-1; x++)
			cnt += res[y][x];
	cout << fixed << setprecision(2) << cnt*3.0/100.0 << endl;
	return 0;
}
