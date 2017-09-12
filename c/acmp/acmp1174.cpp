/* ACMP 1174 */
#include <unordered_map>
#include <vector>
#include <string>
#include <stdio.h>
 
using namespace std;
 
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	char sc[n];
	char *sp = sc;
	scanf("%s", sp);
	string s(sp);
	int l = s.length()/m;
	unordered_map<string, vector<int>> mm;
	for (int i=0; i<m; i++) {
		char ms[l];
		scanf("%s", ms);
		mm[ms].push_back(i);
	}
	for (int i=0; i<s.length()/l; i++) {
		string seg = s.substr(i*l, l);
		auto &vv = mm[seg];
		printf("%d ", vv.back()+1);
		vv.pop_back();
	}
	printf("\n");
	return 0;
}
