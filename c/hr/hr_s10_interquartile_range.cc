#include <cstdio>
#include <cinttypes>
#include <algorithm>
#include <vector>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-interquartile-range */
using namespace std;

// median with 1 dec digit
int get_median10(const vector<int> &srt, int b, int e) {
	int median10;
	int l = e-b;
	int m = b+l/2;
	if (l & 1)
		median10 = srt[m]*10;
	else
		median10 = (((srt[m-1]+srt[m])*10+1)/2);
	return median10;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> ee(n);
	vector<int> aa;
	for (int i=0; i<n; i++)
		scanf("%d", &ee[i]);
	for (int i=0; i<n; i++) {
		int f;
		scanf("%d", &f);
		for (int j=0; j<f; j++)
			aa.push_back(ee[i]);
	}
	n = aa.end()-aa.begin();
	sort(aa.begin(), aa.end());
	int q1 = get_median10(aa, 0, n/2);
	int q3 = get_median10(aa, n/2+(n&1), n);
	int ans = q3-q1;
	printf("%d.%d\n", ans/10, ans%10);
	return 0;
}
