#include <iostream>
#include <vector>
#include <unordered_map>

/* CodeForces CF776C problem */
using namespace std;

/* GNU stdlibc++ is so lousy that you have to customize hash functions for ints */
struct myhashi64 {
	size_t operator()(int64_t x) const {
		x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
		x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
		x = x ^ (x >> 31);
		return x;
	}
};

static int64_t cnt(const vector<int64_t> &ss, const vector<int64_t> &vkp) {
	int64_t sum = 0;
	unordered_map<int64_t, int64_t, myhashi64> r;
	for (int i=ss.size()-1; i>=0; i--) {
		for (auto kp:vkp) {
			auto v = r.find(kp+ss[i]);
			if (v != r.end())
				sum += v->second;
		}
		r[ss[i]]++;
	}
	for (auto kp:vkp) {
		auto v = r.find(kp);
		if (v != r.end())
			sum += v->second;
	}
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
		vector<int64_t> vkp;
		for (int64_t kp=1; abs(kp)<=100000000000000; kp *= k)
			vkp.push_back(kp);
		sum = cnt(ss, vkp);
	} else if (k == -1) {
		sum = cnt(ss, vector<int64_t>{-1, 1});
	} else {
		sum = cnt(ss, vector<int64_t>{1});
	}
	cout << sum << endl;
	return 0;
}
