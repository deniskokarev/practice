#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <algorithm>
/* CodeForces 782B problem */
using namespace std;

int can_meet_in_t(vector<int> &xx, vector<int> &vv, int n, double t) {
	vector<pair<double,int>> nx;
	for (int i=0; i<n; i++) {
		nx.push_back(make_pair(xx[i]-vv[i]*t, +1));
		nx.push_back(make_pair(xx[i]+vv[i]*t, -1));
	}
	sort(nx.begin(), nx.end(), [](const pair<double,int> &a, const pair<double,int> &b){return a.first<b.first;});
	int sum = 0;
	int mx = 0;
	for (auto &e:nx) {
		sum += e.second;
		mx = max(mx, sum);
	}
	return mx;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<int> xx(n);
	vector<int> vv(n);
	for (int i=0; i<n; i++)
		cin >> xx[i];
	for (int i=0; i<n; i++)
		cin >> vv[i];
	double tl = 0;
	double tr = 1.0+(*max_element(xx.begin(), xx.end()))/(*min_element(vv.begin(), vv.end()));
	double e = 0.0000001;
	while (fabs(tr-tl) > e) {
		double t = (tr+tl)/2;
		if (can_meet_in_t(xx, vv, n, t) < n) {
			tl = t;
		} else {
			tr = t;
		}
	}
	cout << setprecision(9) << tl << endl;
	return 0;
}
