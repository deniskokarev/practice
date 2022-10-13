// https://leetcode.com/problems/largest-perimeter-triangle/

class Solution {
public:
    int largestPerimeter(vector<int>& nn) {
        const int sz = nn.size();
        sort(nn.begin(), nn.end());
        for (int i=sz-3; i>=0; i--)
            if (nn[i] + nn[i+1] > nn[i+2])
                return nn[i] + nn[i+1] + nn[i+2];
        return 0;
    }
};
