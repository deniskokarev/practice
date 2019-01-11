#include <cstdio>
#include <cinttypes>
#include <algorithm>
#include <list>
/* Hakerrank https://www.hackerrank.com/challenges/waiter */

void seave_primes(char *is_prime, int sz) {
	std::fill(is_prime, is_prime+sz, 1);
	for (int s=2; s<sz; s++)
		for (int i=2*s; i<sz; i+=s)
			is_prime[i] = 0;
}

int primes1200(int *primes) {
	char seave[10000];
	seave_primes(seave, 10000);
	int sz = 0;
	for (int i=2; i<10000 && sz<1200; i++)
		if (seave[i])
			primes[sz++] = i;
	return sz;
}

void fwd(std::list<int> &lst, int p) {
	for (auto t=next(lst.begin()),nt=next(t); *t != -1; t=nt,nt=next(t)) {
		if (*t % p == 0) {
			printf("%d\n", *t);
			lst.erase(t);
		}
	}
}

void bwd(std::list<int> &lst, int p) {
	for (auto t=prev(prev(lst.end())),nt=prev(t); *t != -1; t=nt,nt=prev(t)) {
		if (*t % p == 0) {
			printf("%d\n", *t);
			lst.erase(t);
		}
	}
}

int main(int argc, char **argv) {
	int primes[1201];
	primes1200(primes);
	int n, q;
	scanf("%d%d", &n, &q);
	std::list<int> aa;
	aa.push_back(-1);
	for (int i=0; i<n; i++) {
		int a;
		scanf("%d", &a);
		aa.push_back(a);
	}
	aa.push_back(-1);
	for (int i=0; i<q && aa.size()>1; i++)
		if (!(i&1))
			fwd(aa, primes[i]);
		else
			bwd(aa, primes[i]);
	if (q&1)
		fwd(aa, 1);
	else
		bwd(aa, 1);
	return 0;
}
