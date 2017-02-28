#include <iostream>
#include <vector>
/* CodeForces CF778A problem */
/* full solution (peeked at the hint) */
using namespace std;

bool is_subsec(const string &a, const string &b) {
	auto ai = a.begin();
	auto bi = b.begin();
	while (ai != a.end() && bi != b.end()) {
		if (*ai == *bi)
			++bi;
		++ai;
	}
	return bi == b.end();
}

string crossout(const string &a, const vector<int> &r, int sz) {
	string b(a);
	for (int i=0; i<sz; i++)
		b[r[i]] = '_';
	return b;
}

int main(int argc, char **argv) {
	string t;
	string p;
	cin >> t;
	cin >> p;
	vector<int> a(t.size());
	for (auto &ai:a) {
		cin >> ai;
		ai--;
	}
	int i = 0;
	int j = t.size();
	while (i<j) {
		int m = (i+j)/2;
		if (!is_subsec(crossout(t, a, m), p))
			j = m;
		else
			i = m+1;
	}
	cout << i-1 << endl;
	return 0;
}
