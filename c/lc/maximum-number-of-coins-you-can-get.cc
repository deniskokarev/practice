class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end(), std::greater<int>());
        int sz = piles.size();
        int sm = 0;
        for (int i=0; i<sz; i+=2,sz--)
            sm += piles[i+1];
        return sm;
    }
};
