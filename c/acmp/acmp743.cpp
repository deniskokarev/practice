/* ACMP 743 */
#include <iostream>
#include <queue>
#include <map>
#include <vector>

using namespace std;

struct Name2Index {
	int idx;
	map<string, int> m2i;
	Name2Index():idx(1),m2i() {
	}
	int operator()(const string &s) {
		auto &e = m2i[s];
		if (e == 0)
			e = idx++;
		return e-1;
	}
};

int main(int argc, char **argv) {
	vector<vector<int>> mm;
	int n;
	cin >> n;
	Name2Index n2i;
	while (n--) {
		string fr, dum, to;
		cin >> fr >> dum >> to;
		int i = n2i(fr);
		int j = n2i(to);
		int mxsz = max(i+1, j+1);
		if (mm.size() < mxsz)
			mm.resize(mxsz);
		mm[i].push_back(j);
	}
	string fr, to;
	cin >> fr >> to;
	int i = n2i(fr);
	int j = n2i(to);
	int mxsz = max(i+1, j+1);
	if (mm.size() < mxsz)
		mm.resize(mxsz);
	vector<int> dist(mm.size(), INT_MAX);
	dist[i] = 0;
	queue<int> qq;
	qq.push(i);
	int ans = (i!=j)?-1:0;
	while (qq.size() > 0 && ans < 0) {
		const auto &n = qq.front();
		for (auto t:mm[n]) {
			if (t == j) {
				ans = dist[n]+1;
				break;
			} if (dist[t] > dist[n]+1) {
				dist[t] = dist[n]+1;
				qq.push(t);
			}
		}
		qq.pop();
	}
	cout << ans << endl;
	return 0;
}
