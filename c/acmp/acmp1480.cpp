#include <iostream>
#include <set>
#include <unordered_map>

/* ACMP 1480 */
using namespace std;

int main(int argc, char **argv) {
	unordered_map<string,int> n2cnt;
	set<string> nms;
	int mx = 0;
	int n;
	cin >> n;
	while (n--) {
		string nm;
		cin >> nm;
		nms.insert(nm);
		auto &cnt = n2cnt[nm];
		cnt++;
		mx = max(mx, cnt);
	}
	while (mx--) {
		for (auto &nm:nms) {
			char o = (n2cnt[nm] > mx) ? 'X' : '.';
			cout << o;
		}
		cout << '\n';
	}
	return 0;
}
