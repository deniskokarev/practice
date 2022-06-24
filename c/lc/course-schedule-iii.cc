// https://leetcode.com/problems/course-schedule-iii/
class Solution {
public:
    static int scheduleCourse(const vector<vector<int>> &courses) {
        vector<vector<int>> sc(courses);
        sort(sc.begin(), sc.end(), [](auto &a, auto &b){return a[1] < b[1];});
        int mxd = sc.back()[1];
        vector<int> dp(mxd + 1);
        for (auto &c: sc) {
            int sz = c[0];
            int cend = c[1];
            int d = cend;
            while (d >= sz) {
                dp[d] = max(dp[d], dp[d-sz] + 1);
                d--;
            }
            for (int d=cend+1; d <= mxd; d++) {
                dp[d] = max(dp[d], dp[d-1]);
            }
        }
        return dp[mxd];
    }
};
