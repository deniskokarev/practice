/**
*Initial set: {(1, 10), (20, 30)}*
*Input interval: (5, 15)*
*Output set: {(1, 15), (20, 30)}*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

struct IV {
	int f, t;	 // [f, t), len = t-f
	bool operator<(const IV &o) const {
		return f<o.f;
	}
};

struct IVSet {
	set<IV> ivs;
	IVSet(const vector<IV> &aivs):ivs(aivs.begin(), aivs.end()) {
		ivs.insert({INT_MIN, INT_MIN});
		ivs.insert({INT_MAX, INT_MAX});
	}
	
	set<IV>::iterator begin() {
		return next(ivs.begin());
	}
	
	set<IV>::iterator end() {
		return prev(ivs.end());
	}

	void insert(const IV &iv) {
		auto first = prev(ivs.upper_bound(iv)); // hit first >= iv
		if (first->t >= iv.f) {
			if (iv.t <= first->t) {
				// [first......]
				//   [iv...]
			} else {
				// [first...]
				//	    [iv...]
				auto it = next(first);
				while (it->t <= iv.t) {
					// prune
					auto nit = next(it);
					ivs.erase(it);
					it = nit;
				}
				auto last = it;
				if (last->f > iv.t) {
					//	       [last...]
					// [iv...]
					IV niv = {first->f, iv.t};
					ivs.erase(first);
					ivs.insert(niv);
				} else {
					//	    [last...]
					// [iv...]
					IV niv {first->f, last->t};
					ivs.erase(first);
					ivs.erase(last);
					ivs.insert(niv);
				}
			}
		} else {
			// [first...]
			//		      [iv...]
			auto it = next(first);
			while (it->t <= iv.t) {
				// prune
				auto nit = next(it);
				ivs.erase(it);
				it = nit;
			}
			auto last = it;
			// potential overlap with last
			if (last->f > iv.t) {
				//	       [last...]
				// [iv...]
				ivs.insert(iv);
			} else {
				//	    [last...]
				// [iv...]
				IV niv {iv.f, last->t};
				ivs.erase(last);
				ivs.insert(niv);
			}
		}
	}
};


int main(int argc, char **argv) {
	IVSet ivs({{1,10},{20,30}});
	ivs.insert({5,15});
	for (auto iv:ivs) {
		cout << '[' << iv.f << ',' << iv.t << ']' << endl;
	}
	return 0;
}

