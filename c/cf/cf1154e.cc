#include <iostream>
#include <vector>
#include <map>
/* CodeForces CF1154E problem */
using namespace std;

struct P {
	int score;
	int pos;
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	map<int,P> p2s; // pos -> score,pos
	p2s[0] = P{-1,-1};
	map<int,map<int,P>::iterator> s2p; // score -> p2s element
	s2p[-1] = p2s.find(0);
	for (int i=1; i<=n; i++) {
		int a;
		cin >> a;
		p2s[i] = P {a, i};
		s2p[a] = p2s.find(i);
	}
	int team = 0;
	vector<int> pp(n+1, -1);
	while (s2p.size() > 1) {
		auto it = prev(s2p.end())->second;
		auto rit = next(it);
		for (int i=0; i<k && rit != p2s.end(); i++) {
			//cerr << "t=" << team+1 << " taking pos=" << rit->second.pos << " score=" << rit->second.score << endl;
			s2p.erase(rit->second.score);
			pp[rit->second.pos] = team;
			auto nit = next(rit);
			p2s.erase(rit);
			rit = nit;
		}
		rit = it;
		for (int i=0; i<=k && rit->second.pos >= 0; i++) {
			//cerr << "t=" << team+1 << " taking pos=" << rit->second.pos << " score=" << rit->second.score << endl;
			s2p.erase(rit->second.score);
			pp[rit->second.pos] = team;
			auto nit = prev(rit);
			p2s.erase(rit);
			rit = nit;
		}
		team ^= 1;
	}
	for (int i=1; i<=n; i++)
		cout << pp[i]+1;
	cout << '\n';
	return 0;
}
