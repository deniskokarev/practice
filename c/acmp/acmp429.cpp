#include <iostream>
#include <iomanip>
#include <vector>
/* ACMP 429 */
using namespace std;

struct G {
	vector<int> score;
	vector<vector<int>> ee;
};

int score(const G &g, int root, int sign) {
	int cnt[3] {0, 0, 0};
	if (g.ee[root].size() > 0) {
		for (int c:g.ee[root])
			cnt[score(g, c, -sign)+1]++;
		if (cnt[sign+1] > 0)
			return sign;
		else if (cnt[0+1] > 0)
			return 0;
		else
			return -sign;
	} else {
		return g.score[root];
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	G g { vector<int>(n+1), vector<vector<int>>(n+1) };
	for (int i=1; i<n; i++) {
		string s;
		cin >> s;
		int p;
		switch(s[0]) {
		case 'N':
			cin >> p;
			g.ee[p-1].push_back(i);
			break;
		case 'L':
			cin >> p;
			g.ee[p-1].push_back(i);
			cin >> g.score[i];
			break;
		}
	}
	const char *res[] = {"-1", "0", "+1"};
	cout << res[score(g, 0, +1)+1] << endl;
	return 0;
}
