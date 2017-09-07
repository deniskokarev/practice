/* ACMP 659 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct SEL {
	const SEL *p;
	int i;
};

struct SEL_CTX {
	const vector<vector<bool>> &ff;
	vector<int> sel;
	int mxf;
};

void choose_team(int k, int f, int t, const SEL *p, SEL_CTX &sc) {
	if (k>0) {
		SEL mysel = {p};
		for (int i=f; i<t; i++) {
			mysel.i = i;
			choose_team(k-1, i+1, t, &mysel, sc);
		}
	} else {
		vector<int> tt(sc.sel.size()); // this team
		vector<int> ot(t-tt.size()); // other team
		int i=(int)tt.size()-1;
		for (auto cn=p; cn->i >= 0; cn=cn->p,i--)
			tt[i] = cn->i;
		int j = 0;
		int oti = 0;
		for (auto &t:tt) {
			while (j<t)
				ot[oti++] = j++;
			j++;
		}
		while(j<t)
			ot[oti++] = j++;
		int ttcnt = 0;
		for (int i=0; i<tt.size()-1; i++)
			for (int j=i+1; j<tt.size(); j++)
				if (sc.ff[tt[i]][tt[j]])
					ttcnt++;
		int otcnt = 0;
		for (int i=0; i<ot.size()-1; i++)
			for (int j=i+1; j<ot.size(); j++)
				if (sc.ff[ot[i]][ot[j]])
					otcnt++;
		if (ttcnt+otcnt >= sc.mxf) {
			sc.sel = tt;
			sc.mxf = ttcnt+otcnt;
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
	SEL_CTX sc {ff,	vector<int>(k), 0};
	SEL ssel {NULL, -1};
	choose_team(k, 0, n, &ssel, sc);
	for (auto &p:sc.sel)
		cout << p+1 << ' ';
	cout << endl;
	return 0;
}
