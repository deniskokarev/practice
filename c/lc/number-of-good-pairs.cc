// https://leetcode.com/problems/number-of-good-pairs/
class Solution {
public:
    int numIdenticalPairs(const vector<int>& nums) {
        int hh[101]{};
        int a = 0;
        for (auto n: nums) {
            a += hh[n];
            hh[n]++;
        }
        return a;
    }
};

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int sz = nums.size();
        int cnt = 0;
        for (int i=0; i<sz; i++)
            for (int j=i+1; j<sz; j++)
                cnt += (nums[i] == nums[j]);
        return cnt;
    }
};
