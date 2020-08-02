class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        list<int> ll(arr.begin(), arr.end());
        auto hd = ll.begin();
        int w = 0;
        int sz = arr.size();
        k = min(k, sz);
        int r = k;
        while (r) {
            int sc = *next(hd);
            if (*hd < sc) {
                ll.push_back(*hd);
                *hd = sc;
                r = k-1;
            } else {
                ll.push_back(sc);
                r--;
            }
            ll.erase(next(hd));
        }
        return *hd;
    }
};
