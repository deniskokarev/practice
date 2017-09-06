/* ACMP 659 */
#include <iostream>
#include <vector>

using namespace std;

struct SEL {
	SEL *p;
	int i;
	int ftt;
	int nftt;
};

struct SEL_CTX {
	vector<vector<bool>> ff;
	vector<vector<int>> ffcnt;
	vector<int> sel;
	int ans;
};

void choose_team(int k, int f, int t, SEL *p, int m, SEL_CTX &sc) {
	if (k>0) {
		SEL mysel = {p};
		for (int i=f; i<t; i++) {
			int ftt = 0; // friends in this team
			for (SEL *cn=p; cn!=NULL; cn=cn->p) {
				if (sc.ff[cn->i][i])
					ftt++;
			}
			int nftt = sc.ffcnt[i][i-1] - ftt; // friends in other team
			mysel.i = i;
			if (p) {
				mysel.ftt = p->ftt + ftt;
				mysel.nftt = p->nftt + nftt;
			} else {
				mysel.ftt = ftt;
				mysel.nftt = nftt;
			}
			choose_team(k-1, i+1, t, &mysel, m, sc);
		}
	} else {
		int cnt = m-p->nftt;
		if (cnt > sc.ans) {
			sc.ans = cnt;
			vector<int> sel;
			for (SEL *cn=p; cn!=NULL; cn=cn->p)
				sel.push_back(cn->i);
			swap(sc.sel, sel);
		}
		sc.ans = max(sc.ans, cnt);
	}
}

int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	SEL_CTX sc {
		vector<vector<bool>>(n, vector<bool>(n, false)),
		vector<vector<int>>(n, vector<int>(n, 0)),
		vector<int>(k),
		0
	};
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		sc.ff[v1][v2] = sc.ff[v2][v1] = true;
		sc.ffcnt[v1][v2] = sc.ffcnt[v2][v1] = 1;
	}
	for (auto &r:sc.ffcnt)
		for (int i=0; i<n-1; i++)
			r[i+1] += r[i];
	choose_team(k, 0, n, NULL, m, sc);
	for (auto &p:sc.sel)
		cout << p+1 << ' ';
	cout << endl;
	return 0;
}
