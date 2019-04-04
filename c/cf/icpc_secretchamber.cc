#include <iostream>
#include <iomanip>
#include <vector>
/* ICPC https://judge.icpc.global/problems/secretchamber */
using namespace std;

constexpr int SZ = 'z'-'a'+1;
constexpr int INF = 1024;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> mm(SZ, vector<int>(SZ, INF));
	for (int i=0; i<SZ; i++)
		mm[i][i] = 0;
	while (n--) {
		string f, t;
		cin >> f >> t;
		int fi = f[0]-'a';
		int ti = t[0]-'a';
		mm[fi][ti] = 1;
	}
	// floyd
	for (int k=0; k<SZ; k++)
		for (int i=0; i<SZ; i++)
			for (int j=0; j<SZ; j++)
				mm[i][j] = min(mm[i][j], mm[i][k]+mm[k][j]);
	while (m--) {
		string f, t;
		cin >> f >> t;
		bool ans = true;
		if (f.size() == t.size()) {
			for (auto &c:f)
				c -= 'a';
			for (auto &c:t)
				c -= 'a';
			for (int i=0; i<f.size(); i++)
				ans &= (mm[f[i]][t[i]] < INF);
		} else {
			ans = false;
		}
		cout << (ans ? "yes" : "no") << "\n";
	}
	return 0;
}
