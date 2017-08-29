#include <stdio.h>
#include <algorithm>
 
/* ACMP 112 */
 
/**
 * Multistage binary merge primitive for binary decomposition
 * Allows O(Nlog(N)) complexity for [0..pos) interval operations
 * Needs O(Nlog(N)) time to initialize
 * Needs O(Nlog(N)) space
 */
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
 
int main(int argc, char **argv) {
    int n, k;
    scanf("%d %d", &n, &k);
	unsigned long long ans = 0;
    using TMM = mmerge<unsigned short>;
    TMM solders(n);
    for (int ki=0; ki<k; ki++) {
        for (int i=0; i<n; i++)
            scanf("%hu", &solders[i]);
        solders.merge_merge();
        for (int i=1; i<n; i++) {
			struct CountGreater {
				unsigned long long &ans;
				unsigned short &el;
				CountGreater(unsigned long long &_a, unsigned short &_e):ans(_a),el(_e){}
				void operator()(TMM::cit bi, TMM::cit ei) {
                    auto it = std::upper_bound(bi, ei, el);
                    ans += ei-it;
				}
			};
            solders.reduce_lt(i, CountGreater(ans, solders[i]));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
