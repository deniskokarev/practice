#include <stdio.h>
#include <math.h>
#include <algorithm>
 
/* ACMP 112 */
 
int main(int argc, char **argv) {
    int n, k;
    scanf("%d %d", &n, &k);
    int l2 = int(ceil(log2(n)));
    unsigned long long ans = 0;
    for (int ki=0; ki<k; ki++) {
        unsigned short ss[l2+1][n]; // for multistage binary search
        for (int i=0; i<n; i++)
            scanf("%hu", &ss[0][i]);
        for (int l=0,p2=1,dp2=p2*2; l<l2 && dp2<n; l++,p2=dp2,dp2*=2)
            for (int x=0; x+dp2<=n; x+=dp2)
                std::merge(&ss[l][x], &ss[l][x+p2], &ss[l][x+p2], &ss[l][x+dp2], &ss[l+1][x]);
        for (int i=1; i<n; i++) {
            int el = ss[0][i];
            for (int b=i,l=0; b>0; b>>=1,l++) {
                if ((b&1)) {
                    auto bi = &ss[l][((i>>l)-1)<<l];
                    auto ei = &ss[l][(i>>l)<<l];
                    auto it = std::upper_bound(bi, ei, el);
                    ans += ei-it;
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
