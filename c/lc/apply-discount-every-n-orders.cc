class Cashier {
    int n;
    int cnt;
    int discount;
    unordered_map<int,int> p2p;
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices):n(n),cnt(0),discount(discount),p2p() {
        int sz = products.size();
        for (int i=0; i<sz; i++)
            p2p[products[i]] = prices[i];
    }
    
    double getBill(vector<int> product, vector<int> amount) {
        int sz = product.size();
        int64_t sm = 0;
        for (int i=0; i<sz; i++)
            sm += int64_t(p2p[product[i]]) * amount[i];
        cnt++;
        if (!(cnt%n))
            return double(sm) * (100.0-discount)/100.0;
        else
            return sm;
    }
};

