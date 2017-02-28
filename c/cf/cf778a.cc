#include <iostream>
#include <vector>
/* CodeForces CF778A problem */
using namespace std;

struct A {
	int a;
	int i;
};

struct bloom {
	const int sz = 'z'-'a';
	vector<int> a;
	vector<int> b;
	bloom(const string &_a, const string &_b):a(sz, 0),b(sz, 0) {
		for (char c:_a)
			a[(c-'a')%sz]++;
		for (char c:_b)
			b[(c-'a')%sz]++;
	}
	bool can_remove(char c) {
		int i = (c-'a')%sz;
		if (a[i] > b[i]) {
			a[i]--;
			return true;
		} else {
			return false;
		}
	}
};

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
	bloom b(t, p);
	int i=0;
	for (auto &ai:a) {
		if (!b.can_remove(t[ai]))
			break;
		t[ai] = '_';
		if (!is_subsec(t, p))
			break;
		i++;
		//cerr << i << ':' << t << endl;
	}
	cout << i << endl;
	return 0;
}
