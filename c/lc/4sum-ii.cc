class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int sz = A.size();
        unordered_map<int,int> cnt_ab;
        unordered_map<int,int> cnt_cd;
        for (int i=0; i<sz; i++) {
            for (int j=0; j<sz; j++) {
                cnt_ab[A[i]+B[j]]++;
                cnt_cd[C[i]+D[j]]++;
            }
        }
        int ans = 0;
        for (auto ab:cnt_ab)
            ans += ab.second * cnt_cd[-ab.first];
        return ans;
    }
};
