// https://leetcode.com/problems/find-the-town-judge
class Solution {
    using N_CNT = struct {
        int f, t; 
    };
public:
    int findJudge(int sz, vector<vector<int>>& trust) {
        vector<N_CNT> cnts(sz, {0,0});
        for (auto &e: trust) {
            cnts[e[0]-1].f++;
            cnts[e[1]-1].t++;
        }
        for (int i=0; i<sz; i++) {
            auto &c = cnts[i];
            if (c.f == 0 && c.t == sz-1) {
                return i+1;
            }
        }
        return -1;
    }
};
