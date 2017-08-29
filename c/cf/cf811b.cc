/* CodeForces CF811B problem */

/**
 * Multistage binary merge primitive for binary decomposition
 * Allows O(Nlog(N)) complexity for [0..pos) interval operations
 * Needs O(Nlog(N)) time to initialize
 * Needs O(Nlog(N)) space
 */
#include <algorithm>
#include <vector>
#include <cmath>
 
template<typename T>
struct mmerge {
    int sz;
    int l2;	// ilog2(sz)
    std::vector<std::vector<T>> mm; // our 2D array [l2+1][sz]
    using value_type = T;
    using it = typename std::vector<T>::iterator;
    using cit = typename std::vector<T>::const_iterator;
	/**
	 * @param sz - number of elements we need to deal with
	 */
    mmerge(int _sz):sz(_sz),l2(int(ceil(log2(sz)))),mm(l2+1, std::vector<T>(sz)) {
    }
	/**
	 * use [] operator to populate the main level
	 */
    T& operator[](int i) {
        return mm[0][i];
    }
	/**
	 * Run multistage merge using std::merge at each stage
	 * Each level gets sorted bins. The bin sizes double with each level
	 */
    template<class Cmp = std::less<T>> void merge_merge() {
        Cmp cmp;
        for (int l=0,p2=1,dp2=p2*2; l<l2 && dp2<sz; l++,p2=dp2,dp2*=2)
            for (int x=0; x+dp2<=sz; x+=dp2)
                std::merge(mm[l].begin()+x, mm[l].begin()+x+p2, mm[l].begin()+x+p2, mm[l].begin()+x+dp2, mm[l+1].begin()+x, cmp);
    }
	/**
	 * Run ReduceOp for every sorted binary bin to the left of the element pos
	 */
    template<class ReduceOp> void reduce_lt(int pos, ReduceOp &&rop) const {
        for (int b=pos,l=0; b>0; b>>=1,l++) {
            if ((b&1)) {
                auto bi = mm[l].cbegin()+(((pos>>l)-1)<<l);
                auto ei = mm[l].cbegin()+((pos>>l)<<l);
                rop(bi, ei);
            }
        }
    }
};

#include <stdio.h>

int main(int argc, char **argv) {
	int n, m;
	scanf("%d %d", &n, &m);
	using TMM = mmerge<uint16_t>;
	TMM pp(n);
	for (int i=0; i<n; i++)
		scanf("%hu", &pp[i]);
	pp.merge_merge();
	for (int i=0; i<m; i++) {
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		struct CountGreater {
			int &cnt;
			uint16_t el;
			CountGreater(int &_c,uint16_t _e):cnt(_c),el(_e){cnt=0;}
			void operator()(TMM::cit b, TMM::cit e) {
				auto it = std::upper_bound(b, e, el);
				cnt += e-it;
			}
		};
		int lc, rc;
		pp.reduce_lt(l-1, CountGreater(lc, pp[x-1]));
		pp.reduce_lt(r, CountGreater(rc, pp[x-1]));
		if (r-(rc-lc) == x)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
