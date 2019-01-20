#include <iostream>
#include <vector>
/* Hackerrank https://www.hackerrank.com/challenges/common-child */

using namespace std;

int main(int argc, char **argv) {
	string s1, s2;
	cin >> s1;
	cin >> s2;
	vector<vector<int>> mm(s1.length()+1, vector<int>(s2.length()+1));
	for (int i=1; i<=s1.length(); i++)
		for (int j=1; j<=s2.length(); j++)
			if (s1[i-1] == s2[j-1])
				mm[i][j] = max(mm[i-1][j-1]+1, max(mm[i-1][j], mm[i][j-1]));
			else
				mm[i][j] = max(mm[i-1][j], mm[i][j-1]);
	cout << mm[s1.length()][s2.length()] << endl;
	return 0;
}
