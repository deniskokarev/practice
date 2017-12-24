/* ACMP 1083 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

struct Bucket {
	int64_t sum;
	int min;
	int inc;
	int set;
};

struct Data {
	int len;
	vector<int> data;
	vector<Bucket> bucket;
	Data(int sz):len(sqrt(sz)),data(sz),bucket((sz+len-1)/len) {
	}
	int get(int i) const {
		int b = i/len;
		if (bucket[b].set >= 0)
			return bucket[b].set+bucket[b].inc;
		else
			return data[i]+bucket[b].inc;
	}
	// set individual elements and zero out .set and .inc
	void scatter_bucket(int b) {
		if (bucket[b].set >= 0) {
			for (int i=b*len; i<(b+1)*len && i<data.size(); i++)
				data[i] = bucket[b].set;
			bucket[b].set = -1;
		}
		for (int i=b*len; i<(b+1)*len && i<data.size(); i++)
			data[i] += bucket[b].inc;
		bucket[b].inc = 0;
	}
	// may be invoked only after scatter
	void recalc_bucket(int b) {
		bucket[b].sum = 0;
		bucket[b].min = INT_MAX;
		bucket[b].inc = 0;
		bucket[b].set = -1;
		for (int i=b*len; i<(b+1)*len && i<data.size(); i++) {
			bucket[b].sum += data[i];
			bucket[b].min = min(bucket[b].min, data[i]);
		}
	}
	void recalc_all_buckets() {
		for (int b=0; b<bucket.size(); b++)
			recalc_bucket(b);
	}
	void set(int l, int r, int x) {
		int lb = l/len;
		int rb = r/len;
		if (lb<rb) {
			for (int b=lb+1; b<rb; b++) {
				bucket[b].sum = x*len;
				bucket[b].min = x;
				bucket[b].inc = 0;
				bucket[b].set = x;
			}
			scatter_bucket(lb);
			for (int i=l; i<(lb+1)*len; i++)
				data[i] = x;
			recalc_bucket(lb);
			scatter_bucket(rb);
			for (int i=rb*len; i<=r; i++)
				data[i] = x;
			recalc_bucket(rb);
		} else {
			scatter_bucket(lb);
			for (int i=l; i<=r; i++)
				data[i] = x;
			recalc_bucket(lb);
		}
	}
	void inc(int l, int r, int x) {
		int lb = l/len;
		int rb = r/len;
		if (lb<rb) {
			for (int b=lb+1; b<rb; b++) {
				bucket[b].sum += x*len;
				bucket[b].min += x;
				bucket[b].inc += x;
			}
			scatter_bucket(lb);
			for (int i=l; i<(lb+1)*len; i++)
				data[i] += x;
			recalc_bucket(lb);
			scatter_bucket(rb);
			for (int i=rb*len; i<=r; i++)
				data[i] += x;
			recalc_bucket(rb);
		} else {
			scatter_bucket(lb);
			for (int i=l; i<=r; i++)
				data[i] += x;
			recalc_bucket(lb);
		}
	}
	int64_t getSum(int l, int r) {
		int64_t sum = 0;
		int lb = l/len;
		int rb = r/len;
		if (lb<rb) {
			for (int b=lb+1; b<rb; b++)
				sum += bucket[b].sum;
			scatter_bucket(lb);
			for (int i=l; i<(lb+1)*len; i++)
				sum += data[i];
			scatter_bucket(rb);
			for (int i=rb*len; i<=r; i++)
				sum += data[i];
		} else {
			scatter_bucket(lb);
			for (int i=l; i<=r; i++)
				data[i] += data[i];
		}
		return sum;
	}
	int getMin(int l, int r) {
		int mn = INT_MAX;
		int lb = l/len;
		int rb = r/len;
		if (lb<rb) {
			for (int b=lb+1; b<rb; b++)
				mn = min(mn, bucket[b].min);
			scatter_bucket(lb);
			for (int i=l; i<(lb+1)*len; i++)
				mn = min(mn, data[i]);
			scatter_bucket(rb);
			for (int i=rb*len; i<=r; i++)
				mn = min(mn, data[i]);
		} else {
			scatter_bucket(lb);
			for (int i=l; i<=r; i++)
				mn = min(mn, data[i]);
		}
		return mn;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	Data dd(n);
	for (int i=0; i<n; i++)
		cin >> dd.data[i];
	dd.recalc_all_buckets();
	int m;
	cin >> m;
	while (m-- > 0) {
		string cmd;
		cin >> cmd;
		if (cmd == "get") {
			int i;
			cin >> i;
			i--;
			cout << dd.get(i) << "\n";
		} else if (cmd == "update") {
			int l, r, x;
			cin >> l >> r >> x;
			l--, r--;
			dd.set(l, r, x);
		} else if (cmd == "add") {
			int l, r, x;
			cin >> l >> r >> x;
			l--, r--;
			dd.inc(l, r, x);
		} else if (cmd == "rsq") {
			int l, r;
			cin >> l >> r;
			l--, r--;
			cout << dd.getSum(l, r) << "\n";
		} else if (cmd == "rmq") {
			int l, r;
			cin >> l >> r;
			l--, r--;
			cout << dd.getMin(l, r) << "\n";
		} else {
			assert(false && "unknown command");
		}
	}
	return 0;
}
