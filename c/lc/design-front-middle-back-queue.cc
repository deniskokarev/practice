class FrontMiddleBackQueue {
    deque<int> l, r;
public:
    FrontMiddleBackQueue():l(),r() {
    }
    
    void balance() {
        int sz = l.size() + r.size();
        if (sz&1) {
            if (l.size() < r.size()) {
                l.push_back(r.front());
                r.pop_front();
            } else if (l.size()-1 > r.size()) {
                r.push_front(l.back());
                l.pop_back();
            }
        } else {
            if (l.size() < r.size()) {
                l.push_back(r.front());
                r.pop_front();
            } else if (l.size() > r.size()) {
                r.push_front(l.back());
                l.pop_back();
            }
        }
    }
    
    void pushFront(int val) {
        l.push_front(val);
        balance();
    }
    
    void pushMiddle(int val) {
        int sz = l.size() + r.size();
        if (sz&1) {
            r.push_front(l.back());
            l.pop_back();
        }
        l.push_back(val);
        balance();
    }
    
    void pushBack(int val) {
        r.push_back(val);
        balance();
    }
    
    int popFront() {
        if (!l.empty()) {
            int v = l.front();
            l.pop_front();
            balance();
            return v;
        } else {
            return -1;
        }
    }
    
    int popMiddle() {
        if (!l.empty()) {
            int v = l.back();
            l.pop_back();
            balance();
            return v;
        } else {
            return -1;
        }
    }
    
    int popBack() {
        if (!r.empty()) {
            int v = r.back();
            r.pop_back();
            balance();
            return v;
        } else if (!l.empty()) {
            int v = l.back();
            l.pop_back();
            balance();
            return v;
        } else {
            return -1;
        }
    }
};
