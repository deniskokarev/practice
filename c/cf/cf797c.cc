#include <iostream>
#include <vector>
/* CodeForces CF797C problem */
using namespace std;

struct MM {
	char c;
	char mnc;
};

void append_t(vector<MM> &tmn, char c) {
	if (tmn.size() == 0 || tmn.back().mnc >= c) {
		tmn.push_back({c, c});
	} else {
		tmn.push_back(tmn.back());
		tmn.back().c = c;
	}
}

void output_t(vector<MM> &tmn, char upto_c) {
	while (tmn.size() > 0 && tmn.back().mnc <= upto_c) {
		cout << tmn.back().c;
		tmn.pop_back();
	}
}

int main(int argc, char **argv) {
	string s;
	cin >> s;
	int sl = s.size();
	vector<MM> smn(sl);
	smn[sl-1] = {s[sl-1], s[sl-1]};
	for (int i=sl-2; i>=0; i--) {
		if (s[i] <= smn[i+1].mnc) {
			smn[i] = {s[i], s[i]};
		} else {
			smn[i].mnc = smn[i+1].mnc;
			smn[i].c = s[i];
		}
	}
	vector<MM> tmn;
	int i=0;
	while (i<sl) {
		output_t(tmn, smn[i].mnc);
		while (i<sl && (tmn.size() <= 0 || tmn.back().mnc > smn[i].mnc)) {
			append_t(tmn, smn[i].c);
			i++;
		}
	}
	output_t(tmn, 127);
	cout << endl;
	return 0;
}
