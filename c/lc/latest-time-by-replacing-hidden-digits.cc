class Solution {
public:
    string maximumTime(string &time) {
        string res(time);
        if (res[4] == '?')
            res[4] = '9';
        if (res[3] == '?')
            res[3] = '5';
        if (res[1] == '?')
            if (res[0] == '2' || res[0] == '?')
                res[1] = '3';
            else
                res[1] = '9';
        if (res[0] == '?')
            if (res[1] < '4')
                res[0] = '2';
            else
                res[0] = '1';
        return res;
    }
};
