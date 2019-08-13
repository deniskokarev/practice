#include <cstdio>
#include <vector>
/* ACMP 365 */
using namespace std;

static void solve_r(FILE *fout, vector<int> &ans, int hi, int n) {
	if (n>0) {
		for (int i=min(hi, n); i>=1; i--) {
			ans.push_back(i);
			solve_r(stdout, ans, i, n-i);
			ans.pop_back();
		}
	} else {
		char buf[128];
		char *s = buf;
		int i;
		for (i=0; i<ans.size()-1; i++)
			s += sprintf(s, "%d+", ans[i]);
		s += sprintf(s, "%d\n", ans[i]);
		fwrite(buf, s-buf, 1, fout);
	}
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> ans;
	ans.reserve(n+1);
	for (int i=n-1; i>=1; i--) {
		ans.push_back(i);
		solve_r(stdout, ans, i, n-i);
		ans.pop_back();
	}
	return 0;
}
