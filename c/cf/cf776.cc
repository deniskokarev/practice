#include <iostream>
#include <vector>
#include <unordered_map>

/* CodeForces CF776C problem */
using namespace std;

static int64_t cnt(int64_t kp, const vector<int64_t> &ss) {
	int64_t sum = 0;
	unordered_map<int64_t, int64_t> r;
	for (int i=ss.size()-1; i>=0; i--) {
		auto v = r.find(kp+ss[i]);
		if (v != r.end())
			sum += v->second;
		r[ss[i]]++;
	}
	auto v = r.find(kp);
	if (v != r.end())
		sum += v->second;
	return sum;
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	vector<int64_t> aa(n);
	vector<int64_t> ss(n, 0);
	for (int i=0; i<n; i++)
		cin >> aa[i];
	ss[0] = aa[0];
	for (int i=1; i<n; i++)
		ss[i] = ss[i-1]+aa[i];
	int64_t sum = 0;
	if (abs(k) > 1) {
		for (int64_t kp=1; abs(kp)<=100000000000000; kp *= k)
			sum += cnt(kp, ss);
	} else if (k == -1) {
		sum += cnt(-1, ss);
		sum += cnt(1, ss);
	} else {
		sum += cnt(1, ss);
	}
	cout << sum << endl;
	return 0;
}
