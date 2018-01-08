/* ACMP 1317 */
#include <vector>
#include <stdio.h>

using namespace std;

int walk(vector<vector<int>> &page, int x, int y, int color) {
	if (page[y][x] != 0)
		return 0;
	int cnt = 1;
	page[y][x] = color;
	cnt += walk(page, x-1, y, color);
	cnt += walk(page, x+1, y, color);
	cnt += walk(page, x, y-1, color);
	cnt += walk(page, x, y+1, color);
	return cnt;
}

int main(int argc, char **argv) {
	int y, x;
	scanf("%d%d", &y, &x);
	vector<vector<int>> page(y+2, vector<int>(x+2, -1));
	for (int i=0; i<y; i++) {
		auto &row = page[i+1];
		char ln[128];
		scanf("%101s", ln);
		for (int j=0; ln[j] != 0; j++)
			row[j+1] = (ln[j] == '.')?-1:0;
	}
	int c = 1;
	for (int i=1; i<=y; i++)
		for (int j=1; j<=x; j++)
			if (walk(page, j, i, c) > 0)
				c++;
	printf("%d\n", c-1);
	return 0;
}
