/* ACMP 1361 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Generator {
	string in;
	int sz;
	string out[4];
	Generator(const string &s):in(s),sz(0) {
		{
			string ns(s);
			ns[0] = s[s.length()-1];
			for (int i=0; i<s.length()-1; i++)
				ns[i+1] = s[i];
			out[sz++] = ns;
		}
		{
			string ns(s);
			ns[s.length()-1] = s[0];
			for (int i=0; i<s.length()-1; i++)
				ns[i] = s[i+1];
			out[sz++] = ns;
		}
		if (s[0] < '9') {
			string ns(s);
			ns[0]++;
			out[sz++] = ns;
		}
		if (s[s.length()-1] > '1') {
			string ns(s);
			ns[s.length()-1]--;
			out[sz++] = ns;
		}
	}
};

int main(int argc, char **argv) {
	string beg, end;
	cin >> beg >> end;
	vector<pair<string,int>> hist;
	hist.push_back(make_pair(end, -1));
	hist.push_back(make_pair(beg, -1));
	int idx = 1;
	unordered_map<string, int> s2i;
	s2i[beg] = idx;
	queue<int> qq;
	qq.push(idx);
	idx++;
	while (qq.size() > 0) {
		const string &s = hist[qq.front()].first;
		if (s == end)
			break;
		Generator g(s);
		for (int i=0; i<g.sz; i++) {
			int &fi = s2i[g.out[i]];
			if (fi == 0) {
				hist.push_back(make_pair(g.out[i], qq.front()));
				fi = idx;
				qq.push(idx);
				idx++;
			}
		}
		qq.pop();
	}
	if (qq.size() > 0) {
		deque<string> ans;
		for (int i=qq.front(); i>0; i=hist[i].second)
			ans.push_front(hist[i].first);
		for (auto &s:ans)
			cout << s << endl;
	}
	return 0;
}
