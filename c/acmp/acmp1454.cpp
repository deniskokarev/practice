/* ACMP 1454 */
#include <queue>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdio.h>

using namespace std;

enum {
	DIR_OUT = 0, // <IN
	DIR_IN = 1
};

enum {
	P_SIT = 0, // <STAND
	P_STAND,
	P_SZ
};

struct P {
	int stop;
	bool dir;
	int pass;
	bool operator<(const P&b) const {
		return stop<b.stop || (stop == b.stop && (dir < b.dir || (dir == b.dir && (pass < b.pass))));
	}
};

struct S {
	int sbusy;	// sum busy
	int on; // since what stop
};

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	vector<P> pp(k+k);		// stop-> <out/in, pass>
	for (int i=0; i<k; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		pp[i*2] = {t, DIR_OUT, i};
		pp[i*2+1] = {f, DIR_IN, i};
	}
	sort(pp.begin(), pp.end());
	priority_queue<int, vector<int>, greater<int>> free_place[P_SZ]; // sit/stand -> first free place
	for (int i=0; i<m-1; i++)
		free_place[P_SIT].emplace(i);
	for (int i=0; i<m; i++)
		free_place[P_STAND].emplace(i);
	vector<pair<int,int>> p_place(k, make_pair(-1, -1)); // moving bus pass-><sit/stand, place>
	vector<S> s_s[P_SZ] = {
		vector<S>(m, {0, -1}), // sit->stat
		vector<S>(m, {0, -1})	// stand->stat
	};
	for (auto &p:pp) {
		if (p.dir == DIR_OUT) {
			int s = p_place[p.pass].first;
			int place = p_place[p.pass].second;
			if (s == -1 && place == -1)
				continue; // this guy never sat
			assert(s != -1 && place != -1);
			assert(s_s[s][place].on != -1);
			s_s[s][place].sbusy += p.stop-s_s[s][place].on;
			s_s[s][place].on = -1;
			free_place[s].push(place);
			p_place[p.pass] = make_pair(-1, -1);
		} else {
			// IN
			int s;
			for (s=P_SIT; s<=P_STAND; s++) {
				if (free_place[s].size() > 0) {
					int place = free_place[s].top();
					free_place[s].pop();
					assert(s_s[s][place].on == -1);
					s_s[s][place].on = p.stop;
					p_place[p.pass] = make_pair(s, place);
					break;
				}
			}
			// no room - ignore
			//assert(s<P_SZ);
		}
	}
	// it's good to be paranoid
	assert(free_place[P_SIT].size() == m-1);
	assert(free_place[P_STAND].size() == m);
	for (int i=0; i<k; i++)
		assert(p_place[i] == make_pair(-1,-1));
	for (int s=P_SIT; s<=P_STAND; s++)
		for (int i=0; i<m; i++)
			assert(s_s[s][i].on == -1);
	// print result
	int mni = 0;
	for (int i=0; i<m; i++) {
		if (s_s[P_STAND][i].sbusy < s_s[P_STAND][mni].sbusy)
			mni = i;
	}
	printf("%d %d\n", s_s[P_STAND][mni].sbusy, mni+1);
	return 0;
}
