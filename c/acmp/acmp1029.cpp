/* ACMP 1029 */
#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

using P = tuple<int,int,int>;

int &x(P &p) { return get<0>(p); }
int &y(P &p) { return get<1>(p); }
int &z(P &p) { return get<2>(p); }

// @return intersection point of two axises if they collide
bool match2(P &p1, P &p2, P &o) {
	if (x(p1) == x(p2) && y(p1)*y(p2) + z(p1)*z(p2) == 0) {
		o = P {x(p1), y(p1)+y(p2), z(p1)+z(p2)};
		return true;
	} else if (y(p1) == y(p2) && x(p1)*x(p2) + z(p1)*z(p2) == 0) {
		o = P {x(p1)+x(p2), y(p1), z(p1)+z(p2)};
		return true;		
	} else if (z(p1) == z(p2) && x(p1)*x(p2) + y(p1)*y(p2) == 0) {
		o = P {x(p1)+x(p2), y(p1)+y(p2), z(p1)};
		return true;
	} else {
		return false;
	}
}

int main(int argc, char **argv) {
	int n, np;
	cin >> n >> np;
	vector<P> pp(np);
	int ans = 0;
	for (auto &p:pp) {
		cin >> x(p) >> y(p) >> z(p);
		ans += n;
	}
	map<P, int> oo; // intersection points
	for (int i=0; i<np-1; i++) {
		for (int j=i+1; j<np; j++) {
			P o;
			if (match2(pp[i], pp[j], o))
				oo[o]++;
		}
	}
	for (auto &o:oo) {
		if (o.second == 1)
			ans -= 1; // 2 axis
		else
			ans -= 2; // 3 axis
	}
	cout << n*n*n-ans << endl;
	return 0;
}
