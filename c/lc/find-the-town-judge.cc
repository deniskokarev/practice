// https://leetcode.com/problems/find-the-town-judge
class Solution {
    struct P {
        int f, t;
    };
public:
    int findJudge(int n, const vector<vector<int>>& trust) {
        vector<P> pp(n, {0,0});
        for (auto &t:trust) {
            pp[t[0]-1].f++;
            pp[t[1]-1].t++;
        }
        for (int i=0; i<n; i++) {
            if (pp[i].t == n-1 && pp[i].f == 0) {
                return i+1;
            }
        }
        return -1;
    }
};


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
