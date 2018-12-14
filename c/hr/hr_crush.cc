#include <cstdio>
#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cinttypes>
#include <algorithm>
/* Hakerrank https://www.hackerrank.com/challenges/crush/problem */
using namespace std;

struct Q {
    int idx;
    int64_t inc;
};

int main(int argc, char **argv) {
    int n, m;
    scanf("%d%d", &n, &m);
    int sz = m+m;
    Q qq[sz];
    for (int i=0; i<m; i++) {
        Q &qb = qq[i*2];
        Q &qe = qq[i*2+1];
        scanf("%d%d%" PRId64 "", &qb.idx, &qe.idx, &qb.inc);
        qe.inc = -qb.inc;
        qe.idx++;
    }
    sort(qq, qq+sz, [](const Q &a, const Q &b){return a.idx < b.idx;});
    int64_t mx = 0;
    int64_t sum = 0;
    int idx = -1;
    int i = 0;
    while (i < sz) {
        while (i < sz && idx == qq[i].idx)
            sum += qq[i++].inc;
        idx = qq[i].idx;
        mx = max(mx, sum);
    }
    printf("%" PRId64 "\n", mx);
    return 0;
}
