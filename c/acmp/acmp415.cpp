/* ACMP 415 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// longest common substring
struct sstat {
	const string &n1, &n2;
	vector<vector<int>> mm;
	sstat(const string &_n1, const string &_n2):n1(_n1),n2(_n2),mm(n1.size()+1, vector<int>(n2.size()+1, 0)) {
		for (int i=0; i<n1.size(); i++)
			for (int j=0; j<n2.size(); j++)
				if (n1[i] == n2[j])
					mm[i+1][j+1] = mm[i][j]+1;
				else
					mm[i+1][j+1] = 0;
	}
	// 2 may be a continuation of 1 starting at this position
	int maycat12() const {
		int pos = 0;
		int i = n1.size();
		for (int j=1; j<=n2.size(); j++)
			if (mm[i][j] == j)
				pos = j;
		return n1.size()-pos;
	}
	// 1 may be a continuation of 2 starting at this position
	int maycat21() const {
		int pos = 0;
		int j = n2.size();
		for (int i=1; i<=n1.size(); i++)
			if (mm[i][j] == i)
				pos = i;
		return n2.size()-pos;
	}
};

int main(int argc, char **argv) {
	string n1, n2;
	cin >> n1 >> n2;
	string lc1(n1), lc2(n2);
	transform(lc1.begin(), lc1.end(), lc1.begin(), ::tolower);
	transform(lc2.begin(), lc2.end(), lc2.begin(), ::tolower);
	sstat ss(lc1, lc2);
	vector<string> oo;
	int p;
	string s;
	p = ss.maycat12();
	s = n1.substr(0, p) + n2;
	oo.push_back(s);
	p = ss.maycat21();
	s = n2.substr(0, p) + n1;
	oo.push_back(s);
#if 1
	cerr << "p12: " << ss.maycat12() << " p21: " << ss.maycat21() << endl;
	for (auto &o:oo)
		cerr << "o: " << o << endl;
#endif
	sort(oo.begin(), oo.end(), [](const string &a, const string &b){ return a.size()<b.size() || (a.size()==b.size() && a<b);});
	cout << oo.front() << endl;
	return 0;
}
