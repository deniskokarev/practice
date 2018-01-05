/* ACMP 1357 */
#include <iostream>

using namespace std;

void out_zero_counts(int *aa, int n, ostream &os) {
	int zc = 0;
	for (int i=0; i<n; i++)
		if (aa[i] == 0)
			zc++;
	os << zc << ' ';
	for (int i=0; i<n; i++)
		if (aa[i] == 0)
			os << i+1 << ' ';
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mm[n][n];
	for (auto &mr:mm)
		for (auto &m:mr)
			cin >> m;
	int cnt[n];
	fill(cnt, cnt+n, 0);
	for (int j=0; j<n; j++)
		for (int i=0; i<n; i++)
			cnt[j] += mm[i][j];
	out_zero_counts(cnt, n, cout);
	cout << endl;
	fill(cnt, cnt+n, 0);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cnt[i] += mm[i][j];
	out_zero_counts(cnt, n, cout);
	cout << endl;
	return 0;
}
