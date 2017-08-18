#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/* CodeForces CF831C problem */
using namespace std;

int main(int argc, char **argv) {
	int k, n;
	cin >> k >> n;
	int64_t aa[k];
	cin >> aa[0];
	for (int i=1; i<k; i++) {
		cin >> aa[i];
		aa[i] += aa[i-1];
	}
	int64_t bb[n];
	for (auto &b:bb)
		cin >> b;
	// make both sorted 0-based absolute scores
	sort(aa, aa+k);
	sort(bb, bb+n);
	int mn;
	mn = aa[0];
	for (auto &a:aa)
		a -= mn;
	mn = bb[0];
	for (auto &b:bb)
		b -= mn;
	// diff at node -> next node
	vector<unordered_map<int, int>> ss(k);
	for (int i=0; i<k-1; i++)
		for (int j=k-1; j>i; j--)
			ss[i][aa[j]-aa[i]] = j;
	int ans = 0;
	for (int ai=0; ai<k; ai++) {
		if (ai>0 && aa[ai] == aa[ai-1])
			continue;
		// layout [b] elements into [a] graph staring node ai
		ans++;
		for (int bi=1,p=ai; bi<n; bi++) {
			int d = bb[bi]-bb[bi-1];
			if (ss[p].find(d) == ss[p].end()) {
				ans--;
				break;
			} else {
				p = ss[p][d];
			}
		}
	}
	cout << ans << endl;
	return 0;
}
