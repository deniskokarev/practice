class Solution {
public:
    string reorderSpaces(const string &text) {
        vector<string> ww;
        string w;
        int len = 0;
        for (char c:text) {
            if (w.size() && c == ' ') {
                ww.push_back(w);
                w = "";
            }
            if (c != ' ') {
                w.push_back(c);
                len++;
            }
        }
        if (w.size())
            ww.push_back(w);
        string res;
        if (ww.size() > 1) {
            int wid = (text.size() - len)/(ww.size()-1);
            for (int i=0; i<ww.size()-1; i++)
                res += ww[i] + string(wid, ' ');
            res += ww.back();            
        } else {
            res = ww[0];
        }
        int rem = text.size() - res.size();
        while (rem--)
            res.push_back(' ');
        return res;
    }
};
