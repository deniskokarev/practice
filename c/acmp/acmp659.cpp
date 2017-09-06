/* ACMP 659 */
#include <iostream>
#include <vector>

using namespace std;

struct SEL {
	const SEL *p;
	int i;
	int nftt;
};

struct SEL_CTX {
	const vector<vector<bool>> &ff;
	const vector<vector<int>> &ffcnt;
	vector<int> sel;
	int mn_nftt;
};

void choose_team(int k, int f, int t, const SEL *p, SEL_CTX &sc) {
	if (k>0) {
		SEL mysel = {p};
		for (int i=f; i<t; i++) {
			mysel.i = i;
			int ftt = 0; // friends in this team
			for (auto cn=p; cn->i >= 0; cn=cn->p) {
				if (sc.ff[i][cn->i])
					ftt++;
			}
			int nftt = sc.ffcnt[i][i] - ftt; // friends in other team
			mysel.nftt = p->nftt + nftt;
			choose_team(k-1, i+1, t, &mysel, sc);
		}
	} else {
		if (p->nftt <= sc.mn_nftt) {
			sc.mn_nftt = p->nftt;
			int i=0;
			for (auto cn=p; cn->i >= 0; cn=cn->p,i++)
				sc.sel[i] = cn->i;
		}
	}
}

int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	vector<vector<bool>> ff(n, vector<bool>(n, false));
	vector<vector<int>> ffcnt(n, vector<int>(n, 0));
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		ff[v1][v2] = ff[v2][v1] = true;
		ffcnt[v1][v2] = ffcnt[v2][v1] = 1;
	}
	for (auto &r:ffcnt)
		for (int i=0; i<n-1; i++)
			r[i+1] += r[i];
	SEL_CTX sc {ff,	ffcnt, vector<int>(k), INT_MAX};
	SEL ssel {NULL, -1, 0};
	choose_team(k, 0, n, &ssel, sc);
	for (auto &p:sc.sel)
		cout << p+1 << ' ';
	cout << endl;
	return 0;
}
