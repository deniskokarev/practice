/* ACMP 38 */
#include <iostream>
#include <vector>

using namespace std;

struct SC {
	int score[2];
};

SC score(int p, const vector<int> &aa, int i, int j, vector<vector<vector<SC>>> &cache) {
	if (i == j) {
		if (p == 0)
			return SC {{aa[i], 0}};
		else
			return SC {{0, aa[i]}};
	} else {
		if (cache[p][i][j].score[0] == -1) {
			SC sl = score(!p, aa, i+1, j, cache);
			SC sr = score(!p, aa, i, j-1, cache);
			SC r;
			if (p == 0)
				if (sl.score[0]+aa[i] > sr.score[0]+aa[j])
					r = SC {{sl.score[0]+aa[i], sl.score[1]}};
				else
					r = SC {{sr.score[0]+aa[j], sr.score[1]}};
			else
				if (sl.score[1]+aa[i] > sr.score[1]+aa[j])
					r = SC {{sl.score[0], sl.score[1]+aa[i]}};
				else
					r = SC {{sr.score[0], sr.score[1]+aa[j]}};
			cache[p][i][j] = r;
		}
		return cache[p][i][j];
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> aa(n);
	for (auto &a:aa)
		cin >> a;
	vector<vector<vector<SC>>> cache(2, vector<vector<SC>>(n, vector<SC>(n, SC{{-1,-1}}))); // (player,i,j) -> (s1,s2)
	SC r = score(0, aa, 0, n-1, cache);
	if (r.score[0] == r.score[1])
		cout << 0 << endl;
	else if (r.score[0] > r.score[1])
		cout << 1 << endl;
	else
		cout << 2 << endl;
	return 0;
}
