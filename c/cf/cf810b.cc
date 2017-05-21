#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF810B problem */
using namespace std;

struct RDay {
	int64_t k, l;
	int64_t sell() const {
		if (l>k)
			return k;
		else
			return l;
	}
	int64_t gain() const {
		if (l>k) {
			if (2*k>l)
				return l-k;
			else
				return k;
		} else {
			return 0;
		}
	}
};

int main(int argc, char **argv) {
	int n, f;
	cin >> n >> f;
	vector<RDay> dd(n);
	for (int i=0; i<n; i++)
		cin >> dd[i].k >> dd[i].l;
	sort(dd.begin(), dd.end(), [](const RDay &a, const RDay &b){ return a.gain()>b.gain(); });
	int64_t s = 0;
	int i;
	for (i=0; i<f; i++)
		s += dd[i].sell()+dd[i].gain();
	for (; i<n; i++)
		s += dd[i].sell();
	cout << s << endl;
	return 0;
}
