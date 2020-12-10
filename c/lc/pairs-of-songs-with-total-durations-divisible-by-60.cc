class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> rem(60);
        int cnt = 0;
        for (int t:time) {
            int wanted_rem = (60 - (t % 60)) % 60;
            cnt += rem[wanted_rem];
            rem[t % 60]++;
        }
        return cnt;
    }
};
