class Solution {
public:
    string reformatDate(const string &date) {
        static const vector<string> MON {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        int p1 = date.find(' ');
        int p2 = date.find(' ', p1+1);
        int day = stoi(date);
        string smon = date.substr(p1+1, p2-p1-1);
        int mon;
        for (mon=0; mon<MON.size(); mon++)
            if (MON[mon] == smon)
                break;
        int year = stoi(date.substr(p2+1));
        char bf[32];
        snprintf(bf, 32, "%d-%02d-%02d", year, mon+1, day);
        return bf;
    }
};
