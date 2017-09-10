/* ACMP 1029 */
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct P {
	int x, y, z;
	bool operator==(const P &b) const {
		return x==b.x && y==b.y && z==b.z;
	}
};

namespace std {
	template<> struct hash<P> {
		size_t operator()(const P &p) const {
			return 1000003*p.x+1009*p.y+p.z;
		}
	};
}

bool match2(const P &p1, const P &p2, P &o) {
	if (p1.x == p2.x && p1.y*p2.y + p1.z*p2.z == 0) {
		o = P {p1.x, p1.y+p2.y, p1.z+p2.z};
		return true;
	} else if (p1.y == p2.y && p1.x*p2.x + p1.z*p2.z == 0) {
		o = P {p1.x+p2.x, p1.y, p1.z+p2.z};
		return true;		
	} else if (p1.z == p2.z && p1.x*p2.x + p1.y*p2.y == 0) {
		o = P {p1.x+p2.x, p1.y+p2.y, p1.z};
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
		cin >> p.x >> p.y >> p.z;
		ans += n;
	}
	unordered_map<P, int> oo;
	for (int i=0; i<np-1; i++) {
		for (int j=i+1; j<np; j++) {
			P o;
			if (match2(pp[i], pp[j], o))
				oo[o]++;
		}
	}
	for (auto &o:oo) {
		//cerr << o.first.x << ',' << o.first.y << ',' << o.first.z << " : " << o.second << endl;
		if (o.second == 1)
			ans -= 1;
		else
			ans -= 2;
	}
	cout << n*n*n-ans << endl;
	return 0;
}
