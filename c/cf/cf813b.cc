#include <iostream>
#include <algorithm>
/* CodeForces CF813B problem */
using namespace std;

int main(int argc, char **argv) {
	uint64_t x, y, l, r;
	cin >> x >> y >> l >> r;
	int64_t ab[65][65];
	ab[0][0] = 1+1;
	ab[1][0] = x+1;
	for (int a=1; a<65; a++)
		if (LLONG_MAX/x > (ab[a-1][0]-1))
			ab[a][0] = (ab[a-1][0]-1)*x+1;
		else
			ab[a][0] = -1;
	ab[0][1] = 1+y;
	for (int b=1; b<65; b++)
		if (LLONG_MAX/y > (ab[0][b-1]-1))
			ab[0][b] = (ab[0][b-1]-1)*y+1;
		else
			ab[0][b] = -1;
	for (int a=1; a<65; a++)
		for (int b=1; b<65; b++)
			if (ab[a-1][0] > 0 && ab[0][b-1] > 0)
				ab[a][b] = (ab[a][0]-1)+(ab[0][b]-1);
			else
				ab[a][b] = -1;
	int64_t seq[65*65+2];
	int nseq = 0;
	seq[nseq++] = l;
	for (int a=0; a<65; a++)
		for (int b=0; b<65; b++)
			if (ab[a][b] >= l && ab[a][b] <= r)
				seq[nseq++] = ab[a][b];
	seq[nseq++] = r;
	sort(seq, seq+nseq);
	nseq = unique(seq, seq+nseq)-seq;
#if 1
	copy(seq, seq+nseq, ostream_iterator<int64_t>(cerr, " "));
	cerr << endl;
#endif
	int64_t mx = 0;
	for (int i=1; i<nseq; i++)
		mx = max(mx, seq[i]-seq[i-1]);
	cout << mx << endl;
	return 0;
}
