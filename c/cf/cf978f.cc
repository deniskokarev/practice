#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF978F problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	struct VK {
		int score;
		int n;
		bool operator<(const VK &b) const {
			return score<b.score;
		}
	};
	vector<VK> aa(n);
	for (int i=0; i<n; i++) {
		int v;
		cin >> v;
		aa[i] = VK {v, i};
	}
	sort(aa.begin(), aa.end());
	vector<int> map(n);
	for (int i=0; i<n; i++)
		map[aa[i].n] = i;
	struct CC {
		int gt{0};
		int eq{0};
		int minus{0};
	};
	vector<CC> cnt(n);
	while (k--) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		if (aa[map[i]].score > aa[map[j]].score)
			cnt[map[i]].minus++;
		else if (aa[map[i]].score < aa[map[j]].score)
			cnt[map[j]].minus++;
	}
	for (int i=1; i<n; i++) {
		if (aa[i].score > aa[i-1].score) {
			cnt[i].gt = cnt[i-1].gt+cnt[i-1].eq+1;
		} else {
			cnt[i].gt = cnt[i-1].gt;
			cnt[i].eq = cnt[i-1].eq+1;
		}
	}
	vector<int> ans(n);
	for (int i=0; i<n; i++)
		ans[i] = cnt[map[i]].gt-cnt[map[i]].minus;
	for (auto &a:ans)
		cout << a << ' ';
	cout << endl;
	return 0;
}
