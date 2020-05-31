//https://leetcode.com/problems/online-stock-span/
class StockSpanner {
    struct V {
        int price;
        int day;
    };
    vector<V> vv;
    int day;
public:
    StockSpanner():vv(),day(0) {
        vv.push_back(V{INT_MAX, day++});
    }
    
    int next(int price) {
        while (vv.back().price <= price)
            vv.pop_back();
        int res = day-vv.back().day;
        vv.push_back(V{price,day++});
        return res;
    }
};

