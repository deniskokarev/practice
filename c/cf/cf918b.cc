#include <iostream>
#include <map>

/* CodeForces CF918B problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	map<string, string> ip2name;
	for (int i=0; i<n; i++) {
		string name, ip;
		cin >> name >> ip;
		ip2name[ip] = name;
	}
	for (int i=0; i<m; i++) {
		string cmd, ips;
		cin >> cmd >> ips;
		cout << cmd << ' ' << ips << " #" << ip2name[ips.substr(0, ips.length()-1)] << endl;
	}
	return 0;
}
