/* ACMP 415 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// NB!: more complicated solution

// n*m statistics a-la longest common substring
struct sstat {
	const string &n1, &n2;
	vector<vector<int>> mm;
	// O(n*m) space and complexity
	sstat(const string &_n1, const string &_n2):n1(_n1),n2(_n2),mm(n1.size()+1, vector<int>(n2.size()+1, 0)) {
		for (int i=0; i<n1.size(); i++)
			for (int j=0; j<n2.size(); j++)
				if (n1[i] == n2[j])
					mm[i+1][j+1] = mm[i][j]+1;
				else
					mm[i+1][j+1] = 0;
	}
	// find biggest overlap where
	// 2 is a continuation of 1 starting at this position
	int cat12() const {
		int pos = 0;
		int i = n1.size();
		for (int j=1; j<=n2.size(); j++)
			if (mm[i][j] == j)
				pos = j;
		return n1.size()-pos;
	}
	// find biggest overlap where
	// 1 is a continuation of 2 starting at this position
	int cat21() const {
		int pos = 0;
		int j = n2.size();
		for (int i=1; i<=n1.size(); i++)
			if (mm[i][j] == i)
				pos = i;
		return n2.size()-pos;
	}
	// find earliest occurence where
	// 2 is entirerly enveloped by 1
	int in12() const {
		int pos = n1.size();
		int j = n2.size();
		for (int i=n1.size()-1; i>j; i--)
			if (mm[i][j] == j)
				pos = i-j;
		return pos;
	}
	// find earliest occurence where
	// 1 is entirerly enveloped by 2
	int in21() const {
		int pos = n2.size();
		int i = n1.size();
		for (int j=n2.size()-1; j>i; j--)
			if (mm[i][j] == i)
				pos = j-i;
		return pos;
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
	// need to consider 4 scenarios
	p = ss.cat12();
	s = n1.substr(0, p) + n2;
	oo.push_back(s);
	p = ss.cat21();
	s = n2.substr(0, p) + n1;
	oo.push_back(s);
	p = ss.in12();
	s = n1.substr(0, p) + n2 + n1.substr(min(n1.size(), p+n2.size()));
	oo.push_back(s);
	p = ss.in21();
	s = n2.substr(0, p) + n1 + n2.substr(min(n2.size(), p+n1.size()));
	oo.push_back(s);
#if 0
	cerr << "p12: " << ss.cat12() << " p21: " << ss.cat21() << " in12: " << ss.in12() << " in21: " << ss.in21() << endl;
	for (auto &o:oo)
		cerr << "o: " << o << endl;
#endif
	sort(oo.begin(), oo.end(), [](const string &a, const string &b){ return a.size()<b.size() || (a.size()==b.size() && a<b);});
	cout << oo.front() << endl;
	return 0;
}
