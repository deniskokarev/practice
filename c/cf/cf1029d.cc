#include <cstdio>
#include <map>
#include <cmath>
#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cinttypes>
/* CodeForces CF1029D problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	int aa[n];
	for (auto &a:aa)
		scanf("%d", &a);
	map<pair<int,int>, int64_t> mm;
	int64_t ans = 0;
	for (int i=0; i<n; i++) {
		int needsfx = ceil(log10(aa[i]+1));
		int needk = (k-aa[i]%k)%k;
		auto fnd = mm.find(make_pair(needk, needsfx));
		if (fnd != mm.end())
			ans += fnd->second;
		uint64_t d=10;
		for (int l=1; l<=10; l++,d*=10) {
			uint64_t ad = aa[i]*d;
			mm[make_pair(ad%k, l)]++;
		}
	}
	mm.clear();
	for (int i=n-1; i>=0; i--) {
		int needsfx = ceil(log10(aa[i]+1));
		int needk = (k-aa[i]%k)%k;
		auto fnd = mm.find(make_pair(needk, needsfx));
		if (fnd != mm.end())
			ans += fnd->second;
		uint64_t d=10;
		for (int l=1; l<=10; l++,d*=10) {
			uint64_t ad = aa[i]*d;
			mm[make_pair(ad%k, l)]++;
		}
	}
	printf("%" PRId64 "\n", ans);
	return 0;
}
