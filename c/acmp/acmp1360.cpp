/* ACMP 1360 */
#include <iostream>
#include <vector>

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
	cin >> n >> m;
	vector<int> color(n, 0);
	vector<vector<int>> mm(n);
	while (m-- > 0) {
		int i, j;
		cin >> i >> j;
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
	cout << c << endl;
	for (int i=0; i<c; i++) {
		cout << ncolor[i] << endl;
		for (auto &v:colvert[i])
			cout << v+1 << ' ';
		cout << endl;
	}
	return 0;
}
