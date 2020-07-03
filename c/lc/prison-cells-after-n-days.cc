// https://leetcode.com/problems/prison-cells-after-n-days/
class Solution {
    static inline unsigned next(unsigned cells) {
        constexpr unsigned MID = 0b01111110;
        return (~((cells>>1) ^ (cells<<1))) & MID;
    }
public:
    static vector<int> prisonAfterNDays(const vector<int>& cells, int N) {
        unsigned start = 0;
        for (auto c:cells)
            start = (start<<1) + c;
        unsigned cycle[256];
        int csz = 0;
        cycle[csz++] = start;
        start = next(start);
        unsigned u = start;
        do {
            cycle[csz++] = u;
            u = next(u);
        } while(u != start);
        unsigned end = cycle[(N-1)%(csz-1)+1];
        vector<int> res(8);
        for (int i=0,msk=1<<7; msk>0; i++,msk>>=1)
            res[i] = ((end&msk) != 0);
        return res;
    }
};
