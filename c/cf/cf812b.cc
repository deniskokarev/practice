#include <iostream>
/* CodeForces CF812B problem */
using namespace std;

struct LR {
	int l, r;
};

int onefl(const LR *glr, int n, int m, int x, int y) {
	int sc;
	if (y < n-1) {
		if (x == 0) {
			int sc1 = onefl(glr, n, m, 1, y+1) + m + 1;
			int sc2 = onefl(glr, n, m, 0, y+1) + glr[y].r*2;
			sc = min(sc1, sc2) + 1;
		} else {
			int sc1 = onefl(glr, n, m, 0, y+1) + m + 1;
			int sc2 = onefl(glr, n, m, 1, y+1) + glr[y].l*2;
			sc = min(sc1, sc2) + 1;
		}
	} else {
		if (x == 0) {
			sc = glr[y].r;
		} else {
			sc = glr[y].l;
		}
	}
	return sc;
}

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	int gr[n][m+2];
	LR glr[n];
	for (int i=n-1; i>=0; i--) {
		string s;
		cin >> s;
		glr[i].r = 0;
		for (int j=0; j<m+2; j++) {
			gr[i][j] = s[j]-'0';
			if (gr[i][j] == 1)
				glr[i].r = j;
		}
		glr[i].l = 0;
		for (int j=m+1; j>=0; j--)
			if (gr[i][j] == 1)
				glr[i].l = m+1-j;
	}
	while (n>0 && glr[n-1].l==0)
		n--;
	cout << onefl(glr, n, m, 0, 0) << endl;
	return 0;
}
