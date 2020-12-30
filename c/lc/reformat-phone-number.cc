class Solution {
public:
    string reformatNumber(string number) {
        string nn;
        for (char c:number)
            if (isdigit(c))
                nn += c;
        int sz = nn.size();
        int rem = sz % 3;
        int g3 = sz / 3;
        if (rem == 1) {
            g3--;
            rem += 3;
        }
        string res;
        int i;
        for (i=0; i<g3; i++)
            res += nn.substr(i*3, 3) + '-';
        if (rem == 4)
            res += nn.substr(i*3, 2) + '-' + nn.substr(i*3+2);
        else if (rem == 0)
            res.pop_back();
        else
            res += nn.substr(i*3);
        return res;
    }
};
