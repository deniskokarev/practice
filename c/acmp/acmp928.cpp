/**
   ACMP 928 birch alley: https://acmp.ru/asp/do/index.asp?main=task&id_course=2&id_section=20&id_topic=45&id_problem=612

   N - number of left-side trees
   M - number of right-side trees

   CPU: O(N * M * log(N) * log(N + M))
   Mem: O(N * (N + M))

   l|--A-----B---------------
   r|---C---------D----------

   Lets consider only right-angled trapezoids aligned to origin l| and r|
   If RightTP(B,D) is trapezoid perimiter l| -> B -> D -> r|
   and S(A,C) - length of segment(A,C)
   then we need to consider all trapezoids A,B,C,D such that:

   band_len >= RightTP(B,D) - RightTP(A,C) + S(A,C)

   let's call RightTP(A,C) - S(A,C) = V(A,C), then
   V(A,C) >= RightTP(B,D) - band_len

   Algorithm:
   for D in [rr]
       compute and store V() for all |-aligned trapzs where right point == D and any left point A
       for B in [ll]
           find best V() that have left point <= B

   V(A,C) must be stored indexed by left point A - so we can consider only V(A,C)s where A <= B
   (we know that C is always <= D because we populate V(A,C) structure in the order of right points D)

   Although, we may use any V such that [ V(A,C) >= RightTP(B,D) - band_len ], we would need only one entry with smallest number of
   cnt_points_left_of(A) + cnt_points_left_of(C), therefore we should consider non-decreasing V(cnt_points)
   function, wich may be stored in max Fenwick tree

   Since we need to limit ourselves to only such Vs that left point A is no greater than B that gives us two-dimensional
   Fenwick tree structure. 1st dimension is indexed by A point of trapezoid, 2nd dimesnion is max perimeter Fenwick tree indexed by
   cnt_points where cnt_points = cnt_points_left_of(A) + cnt_points_left_of(C)
	 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <cmath>
#include <array>
#include <climits>

using namespace std;

constexpr int INF = INT_MAX/2;

// Since the V(cnt_points) function is non-decreasing we can use max Fenwick tree
// Using 2^n nodes for simplified binary search
// So this dimension stores real max(perimiter) values and is indexed by
// cnt_points
using TV = array<double, 4096>;

// 1st dimension is position of point A
using TVS = array<TV, 2001>;

void register_max_v(TV &fw, unsigned cnt, double v) {
	for (; cnt < fw.size(); cnt |= cnt+1)	// fw inc walk
		fw[cnt] = max(fw[cnt], v);
}

void register_max_v(TVS &fw2d, unsigned pos, unsigned cnt, double v) {
	for (; pos < fw2d.size(); pos |= pos+1)	// fw inc walk
		register_max_v(fw2d[pos], cnt, v);
}

// lower bound binary search in Max Fenwick tree
// @return min position for which v is no less than given
// NB!: this trick works only with 2^n FW trees
int fw_lower_bound(const TV &fw, double v) {
	int f = 0, t = fw.size() - 1;
	while (f < t) {
		int m = f+(t-f)/2;
		if (fw[m] >= v)
			t = m;
		else
			f = m+1;
	}
	return t;
}

// find best trapezoid aligned to origin with smallest number of points
// the trapezoid has its left A-vertice less than pos
// and has perimiter no greater than v
// @return min number of points such trapezoid may encircle
int get_min_cnt(const TVS &fw2d, int pos, double v) {
	int mn = INF;
	for (; pos >= 0; pos = (pos & (pos+1)) - 1) // fw sum walk
		mn = min(mn, fw_lower_bound(fw2d[pos], v));
	return mn;
}

inline double diag(const vector<int> &ll, const vector<int> &rr, int l, int r, int w) {
	int64_t d = ll[l] - rr[r];
	return sqrt(w*w + d*d);
}

int main(int argc, char **argv) {
	// read input
	double len;
	int w, n;
	cin >> len >> w;
	cin >> n;
	len += 1e-5; // offsetting band length for rounding errors
	vector<int> ll(n);
	for (auto &l:ll)
		cin >> l;
	cin >> n;
	vector<int> rr(n);
	for (auto &r:rr)
		cin >> r;

	// solve using
	// 2D Fenwick tree to store V() function
	// 1st dimension - point A location
	// 2nd dimension - Max Perimiter for cnt_points
	TVS fw;
	for (unsigned i=0; i<fw.size(); i++)
		fill(begin(fw[i]), end(fw[i]), -INF);
	int ans = 0;
	// iterate by right point D
	for (unsigned r=0; r<rr.size(); r++) {
		// pre-calculate V function for each left point A
		for (unsigned l=0; l<ll.size(); l++) {
			int cnt = r + l;
			double v = ll[l] + rr[r] - diag(ll, rr, l, r, w);
			register_max_v(fw, l, cnt, v);
		}
		// iterate over point B and use best V() to find greatest trapezoid A,B,C,D
		for (unsigned l=0; l<ll.size(); l++) {
			int cnt = r + l + 2;
			double tp = ll[l] + rr[r] + diag(ll, rr, l, r, w);
			int mn_sub_cnt = get_min_cnt(fw, l, tp - len);
			ans = max(ans, cnt - mn_sub_cnt);
		}
	}
	cout << ans << endl;
	return 0;
}
