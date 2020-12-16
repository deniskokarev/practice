class Solution {
    struct P {
        const string &s;
        int b, e;
        operator bool() const {
            int res = true;
            int f = b, t = e-1;
            while (res && f<=t) {
                res &= (s[f] == s[t]);
                f++, t--;
            }
            return res;
        }
        operator const string() const {
            return s.substr(b, e-b);
        }
    };
    void cut_next(vector<vector<P>> &res, vector<P> &curr, const string &s, int b) {
        int sz = s.size();
        if (b == sz) {
            res.push_back(curr);
        } else {
            for (int e=b+1; e<=sz; e++) {
                P pol {s, b, e};
                if (pol) {
                    curr.push_back(pol);
                    cut_next(res, curr, s, e);
                    curr.pop_back();
                }
            }
        }
    }
public:
    vector<vector<string>> partition(const string &s) {
        vector<vector<P>> part;
        vector<P> curr;
        cut_next(part, curr, s, 0);
        vector<vector<string>> res;
        for (auto &s:part)
            res.push_back({s.begin(), s.end()});
        return res;
    }
};
