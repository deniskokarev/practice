class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int sz = A.size();
        unordered_map<int,int> cnt_cd;
        for (int c:C)
            for (int d:D)
                cnt_cd[c+d]++;
        int ans = 0;
        unordered_map<int,int>::iterator it_cd;
        for (int a:A)
            for (int b:B)
                if ((it_cd = cnt_cd.find(-a-b)) != cnt_cd.end())
                    ans += it_cd->second;
        return ans;
    }
};
