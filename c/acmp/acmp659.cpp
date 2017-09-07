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
	const vector<vector<int>> &ff;
	const vector<vector<int>> &ffcnt;
	const int m;
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
		int i=(int)tt.size()-1;
		int fr = 2*sc.m; // total friend pairs
		for (auto cn=p; cn->i>=0; cn=cn->p) {
			tt[i--] = cn->i;
			fr -= sc.ffcnt[cn->i][t-1];
		}
		for (int i=0; i<tt.size()-1; i++)
			for (int j=i+1; j<tt.size(); j++)
				fr += 2*sc.ff[tt[i]][tt[j]];
		if (fr >= sc.mxf) {
			sc.sel = tt;
			sc.mxf = fr;
		}
	}
}
 
int main(int argc, char **argv) {
	int n, k, m;
	cin >> n >> k >> m;
	vector<vector<int>> ff(n, vector<int>(n, 0));
	vector<vector<int>> ffcnt(n, vector<int>(n, 0));
	for (int i=0; i<m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		ff[v1][v2] = ff[v2][v1] = 1;
		ffcnt[v1][v2] = ffcnt[v2][v1] = 1;
	}
	for (auto &r:ffcnt)
		for (int i=0; i<n-1; i++)
			r[i+1] += r[i];
	SEL_CTX sc {ff, ffcnt, m, vector<int>(k), 0};
	SEL ssel {NULL, -1};
	choose_team(k, 0, n, &ssel, sc);
	for (auto &p:sc.sel)
		cout << p+1 << ' ';
	cout << endl;
	return 0;
}
