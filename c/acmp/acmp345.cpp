/* ACMP 345 */
#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

enum {
	EMPTY = 0,
	VISITING = 1,
	END = 2
};

bool walk2end(const vector<vector<int>> &mm, int node, vector<int> &seen) {
	for (auto i:mm[node]) {
		if (seen[i] == END)
			return true;
		else if (seen[i] == VISITING)
			continue;
		seen[i] = VISITING;
		if (walk2end(mm, i, seen))
			return true;
	}
	return false;
}

struct Nm2Idx {
	map<string, int> nmidx;
	int nxt = 1;
	Nm2Idx():nmidx(),nxt(1) {
	}
	int operator()(const string &nm) {
		int &i = nmidx[nm];
		if (i == 0)
			i = nxt++;
		return i-1;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<vector<int>> mm(n);
	vector<int> plst;
	Nm2Idx nm2idx;
	for (int p=0; p<n; p++) {
		string nm;
		cin >> nm;
		int i = nm2idx(nm);
		plst.push_back(i);
		int sz;
		cin >> sz;
		while (sz--) {
			cin >> nm;
			int j = nm2idx(nm);
			mm[i].push_back(j);
			//cerr << i << " -> " << j << endl;
		}
		cin >> nm; // separator
	}
	assert(nm2idx.nxt == n+1);
	for (auto p:plst) {
		vector<int> seen(n, EMPTY);
		seen[p] = END;
		cout << (walk2end(mm, p, seen)?"YES":"NO") << endl;
	}
	return 0;
}
