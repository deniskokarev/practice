// https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/
class Solution {
public:
    double average(vector<int>& salary) {
        unsigned sz = salary.size();
        unsigned sm = accumulate(begin(salary), end(salary), 0U);
        unsigned mn = *min_element(begin(salary), end(salary));
        unsigned mx = *max_element(begin(salary), end(salary));
        return (double(sm) - mn - mx) / (sz - 2);
    }
};
