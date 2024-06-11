// https://leetcode.com/problems/relative-sort-array
class Solution {
public:
    vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
        vector<int> map(1001, INT_MAX);
        for (int p = 0; p < arr2.size(); p++) {
            map[arr2[p]] = p;
        }
        sort(begin(arr1), end(arr1), [&map](int a, int b) { return map[a] < map[b] || map[a] == map[b] && a < b; });
        return arr1;
    }
};
