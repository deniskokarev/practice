#include <iostream>
#include <vector>
#include <list>
/* CodeForces CF1141D problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<list<int>> ll(256);
	vector<list<int>> rr(256);
	string l;
	cin >> l;
	for (int i=0; i<l.size(); i++)
		ll[l[i]].push_back(i);
	string r;
	cin >> r;
	for (int i=0; i<r.size(); i++)
		rr[r[i]].push_back(i);
	vector<pair<int,int>> out;
	for (int i='a'; i<='z'; i++) {
		while (ll[i].size() > 0 && rr[i].size() > 0) {
			out.push_back(make_pair(ll[i].front(), rr[i].front()));
			ll[i].pop_front();
			rr[i].pop_front();
		}
	}
	for (int i='a'; i<='z'; i++) {
		while (ll[i].size() > 0 && rr['?'].size() > 0) {
			out.push_back(make_pair(ll[i].front(), rr['?'].front()));
			ll[i].pop_front();
			rr['?'].pop_front();
		}
	}
	for (int i='a'; i<='z'; i++) {
		while (ll['?'].size() > 0 && rr[i].size() > 0) {
			out.push_back(make_pair(ll['?'].front(), rr[i].front()));
			ll['?'].pop_front();
			rr[i].pop_front();
		}
	}
	while (ll['?'].size() > 0 && rr['?'].size() > 0) {
		out.push_back(make_pair(ll['?'].front(), rr['?'].front()));
		ll['?'].pop_front();
		rr['?'].pop_front();
	}
	cout << out.size() << '\n';
	for (auto o:out)
		cout << o.first+1 << ' ' << o.second+1 << '\n';
	return 0;
}
