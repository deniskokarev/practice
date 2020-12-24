// https://www.hackerrank.com/challenges/candies/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> aa(n);
	for (auto &a:aa)
		scanf("%d", &a);
	vector<int> ll(n);
	ll[0] = 1;
	for (int i=1; i<n; i++) {
		if (aa[i] <= aa[i-1])
			ll[i] = 1;
		else
			ll[i] = ll[i-1]+1;
	}
	vector<int> rr(n);
	rr[n-1] = 1;
	for (int i=n-2; i>=0; i--) {
		if (aa[i] <= aa[i+1])
			rr[i] = 1;
		else
			rr[i] = rr[i+1]+1;
	}
	long sm = 0;
	for (int i=0; i<n; i++)
		sm += max(ll[i], rr[i]);
	printf("%ld\n", sm);
	return 0;
}
