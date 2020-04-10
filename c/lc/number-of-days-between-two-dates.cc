class Solution {
public:
    int daysBetweenDates(const string &date1, const string &date2) {
        time_t rawtime;
        struct tm tm;
        time(&rawtime);
        gmtime_r(&rawtime, &tm);
        tm.tm_year = stoi(date1.substr(0, 4))-1900;
        tm.tm_mon = stoi(date1.substr(5, 2))-1;
        tm.tm_mday = stoi(date1.substr(8, 2));
        time_t t1 = timegm(&tm);
        tm.tm_year = stoi(date2.substr(0, 4))-1900;
        tm.tm_mon = stoi(date2.substr(5, 2))-1;
        tm.tm_mday = stoi(date2.substr(8, 2));
        time_t t2 = timegm(&tm);
        return (max(t1,t2)-min(t1,t2))/24/60/60;
    }
};
