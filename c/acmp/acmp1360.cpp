/* ACMP 1360 */
#include <vector>
#include <stdio.h>

using namespace std;

int walk(const vector<vector<int>> &mm, vector<int> &seen, vector<int> &vert, int r, int color) {
	if (seen[r])
		return 0;
	seen[r] = color;
	vert.push_back(r);
	int cnt = 1;
	for (int i:mm[r])
		cnt += walk(mm, seen, vert, i, color);
	return cnt;
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> color(n, 0);
	vector<vector<int>> mm(n);
	while (m-- > 0) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		mm[i].push_back(j);
		mm[j].push_back(i);
	}
	int c = 0;
	vector<int> ncolor(n, 0);
	vector<vector<int>> colvert;
	for (int i=0; i<n; i++) {
		if (color[i] == 0) {
			colvert.push_back(vector<int>());
			ncolor[c] = walk(mm, color, colvert.back(), i, c+1);
			c++;
		}
	}
	printf("%d\n", c);
	for (int i=0; i<c; i++) {
		printf("%d\n", ncolor[i]);
		for (auto &v:colvert[i])
			printf("%d ", v+1);
		printf("\n");
	}
	return 0;
}
