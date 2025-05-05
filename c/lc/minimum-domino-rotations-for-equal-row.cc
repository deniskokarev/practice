// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row
class Solution {
    static constexpr int D = 6; 
public:
    int minDominoRotations(const vector<int>& tops, const vector<int>& bottoms) {
        int sz = tops.size();
        int ctop[D+1]{};
        int cbot[D+1]{};
        int id[D+1]{};
        for (int i=0; i<sz; i++) {
            ctop[tops[i]]++;
            cbot[bottoms[i]]++;
            if (tops[i] == bottoms[i]) {
                id[tops[i]]++;
            };
        }
        int mn = INT_MAX;
        for (int d=1; d<=D; d++) {
            if (ctop[d] + cbot[d] - id[d] == sz) {
                mn = min({mn, ctop[d] - id[d], cbot[d] - id[d]});
            }
        }
        return mn == INT_MAX ? -1 : mn;
    }
};
