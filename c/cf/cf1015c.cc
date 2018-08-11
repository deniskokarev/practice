#include <iostream>
#include <algorithm>
/* CodeForces CF1015C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	struct S {
		int64_t a, b, sa;
	} ss[n+1];
	for (int i=0; i<n; i++)
		cin >> ss[i].a >> ss[i].b;
	sort(ss,ss+n,[](const S &a, const S &b){return ((a.a-a.b)>(b.a-b.b));});
	ss[n].sa = 0;
	for (int i=n-1; i>=0; i--)
		ss[i].sa = ss[i].a+ss[i+1].sa;
	int ans = 0;
	int64_t sb=0;
	for (ans=0; ans<n; ans++) {
		if (sb+ss[ans].sa <= m)
			break;
		sb += ss[ans].b;
	}
	if (ans == n && sb > m)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}
