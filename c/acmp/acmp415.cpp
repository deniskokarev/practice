/* ACMP 415 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	string n1, n2;
	cin >> n1 >> n2;
	n1[0] = tolower(n1[0]);
	n2[0] = tolower(n2[0]);
	vector<vector<int>> mm(n1.size()+1, vector<int>(n2.size()+1, 0));
	int i, j;
	for (i=0; i<n1.size(); i++)
		for (j=0; j<n2.size(); j++)
			if (n1[i] == n2[j])
				mm[i+1][j+1] = mm[i][j]+1;
			else
				mm[i+1][j+1] = 0;
	int pe1 = -1, pe2 = -1;
	i = n1.size()-1;
	for (j=0; j<n2.size(); j++)
		if (mm[i+1][j+1] == j+1)
			pe2 = j;
	j = n2.size()-1;
	for (i=0; i<n1.size(); i++)
		if (mm[i+1][j+1] == i+1)
			pe1 = i;
	vector<string> oo;
	oo.push_back(string(1, toupper(n1[0])) + n1.substr(1) + string(1, toupper(n2[0])) + n2.substr(1));
	oo.push_back(string(1, toupper(n2[0])) + n2.substr(1) + string(1, toupper(n1[0])) + n1.substr(1));
	if (pe2 >= 0) {
		string s = n1.substr(0, n1.size()-pe2-1) + n2;
		s[0] = toupper(s[0]);
		s[s.size()-n2.size()] = toupper(s[s.size()-n2.size()]);
		oo.push_back(s);
	}
	if (pe1 >= 0) {
		string s = n2.substr(0, n2.size()-pe1-1) + n1;
		s[0] = toupper(s[0]);
		s[s.size()-n1.size()] = toupper(s[s.size()-n1.size()]);
		oo.push_back(s);
	}
#if 0
	cerr << "pe1: " << pe1 << " pe2: " << pe2 << endl;
	for (auto &o:oo)
		cerr << "o: " << o << endl;
#endif
	sort(oo.begin(), oo.end(), [](const string &a, const string &b){ return a.size()<b.size() || (a.size()==b.size() && a<b);});
	cout << oo.front() << endl;
	return 0;
}
