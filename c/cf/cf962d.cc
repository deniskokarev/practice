#include <iostream>
#include <map>
#include <set>
/* CodeForces CF962D problem */
using namespace std;

int main(int argc, char **argv) {
	map<int64_t,set<int>> mm;
	int n;
	cin >> n;
	int64_t aa[n];
	for (int i=0; i<n; i++) {
		auto &a = aa[i];
		cin >> a;
		mm[a].insert(i);
	}
	int del = 0;
	for (auto m:mm) {
		while (m.second.size()>1) {
			auto p = m.second.begin();
			aa[*p] = -1;
			m.second.erase(p);
			p = m.second.begin();
			aa[*p] = m.first*2;
			mm[m.first*2].insert(*p);
			m.second.erase(p);
			del++;
		}
	}
	cout << n-del << endl;
	for (auto &a:aa)
		if (a>=0)
			cout << a << " ";
	cout << endl;
	return 0;
}
