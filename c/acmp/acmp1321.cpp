#include <iostream>
#include <vector>
/* ACMP 1321 */
using namespace std;

int res(vector<int> &rr, int k, int n) {
	if (n<k)
		return 0;
	if (!rr[n]) {
		rr[n] = -1;
		for (int l=0,r=n-k; r>=0; l++,r--) {
			int cl = res(rr, k, l);
			int cr = res(rr, k, r);
			if (cl == 0 && cr == 0)
				return (rr[n] = 1);
			else if (cl == 0 && cr == -1)
				return (rr[n] = 1);
			else if (cl == 1 && cr == 1)
				return (rr[n] = 1);
		}
	}
	return rr[n];
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	string b;
	cin >> b;
	// matrix that tell us if we can win for the
	// specified win/lose sub-intervals 
	vector<vector<int>> wl(n, vector<int>(n));
	wl[0][0] = -1;
	for (int i=1; i<n; i++)
		wl[i][0] = -wl[i-1][0]; 
	wl[0][0] = 1;
	for (int i=1; i<n; i++)
		wl[0][i] = -wl[0][i-1];
	wl[0][0] = 0;
	for (int i=1; i<n; i++)
		for (int j=1; j<n; j++)
			if (wl[i-1][j] < 0 || wl[i][j-1] < 0)
				wl[i][j] = 1;
			else
				wl[i][j] = -1;
	// outcome on the unobstructed sequencial interval
	vector<int> rr(n+1);
	for (int i=0; i<k; i++)
		rr[i] = 0;
	rr[k] = 1;
	for (int i=k+1; i<=n; i++)
		(void)res(rr, k, i);
	int nw = 0;
	int nl = 0;
	int i=0;
	while (i<n) {
		int len = 0;
		while (i<n && b[i++] == 'O')
			len++;
		if (rr[len]>0)
			nw++;
		else if (rr[len]<0)
			nl++;
	}
	const char *ans[3] = {"2", "0", "1"};
	printf("%s\n", ans[wl[nw][nl]+1]);
	return 0;
}
