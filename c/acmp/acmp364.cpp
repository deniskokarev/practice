/* ACMP 364 */
#include <iostream>
#include <vector>

using namespace std;

vector<uint64_t> perf {
	6,
	28,
	496,
	8128,
	33550336,
	8589869056,
	137438691328,
	2305843008139952128
};

int main(int argc, char **argv) {
	uint64_t m, n;
	cin >> m >> n;
	int i;
	bool ans = false;
	for (i=0; i<perf.size() && perf[i]<m; i++);
	for (; i<perf.size() && perf[i]<=n; i++) {
		cout << perf[i] << '\n';
		ans = true;
	}
	if (!ans)
		cout << "Absent\n";
	return 0;
}

