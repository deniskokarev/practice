// https://leetcode.com/problems/orderly-queue/
// O(L^2) solution where L is s.length
class Solution {
public:
    string orderlyQueue(const string &s, int k) {
        if (k > 1) {
            // swapping an arbitrary pair allows sorting
            string o(s);
            sort(begin(o), end(o));
            return o;
        } else {
            // building suffix array should be O(L) :-(
            int sz = s.size();
            string r = s + s;
            string a = r.substr(0, sz);
            for (int i=1; i<sz; i++)
                a = min(a, r.substr(i, sz));
            return a;
        }
    }
};
