class UndergroundSystem {
    map<int,pair<int,string>> start;
    map<pair<string,string>, pair<int,double>> ave;
public:
    UndergroundSystem():start(),ave() {
        
    }
    
    void checkIn(int id, string stationName, int t) {
        start[id] = {t, stationName};
    }
    
    void checkOut(int id, string stationName, int t) {
        auto &sp = start[id];
        ave[{sp.second, stationName}].first++;
        ave[{sp.second, stationName}].second += t-sp.first;
    }
    
    double getAverageTime(string startStation, string endStation) {
        auto &el = ave[{startStation,endStation}];
        return el.second/el.first;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
