class CustomStack {
    int sz;
    vector<int> val;
    vector<int> inc;
    int sp;
public:
    CustomStack(int maxSize):sz(maxSize),val(maxSize+1),inc(maxSize+1),sp(0) {
    }
    
    void push(int x) {
        if (sp < sz)
            val[sp++] = x;
    }
    
    int pop() {
        if (sp > 0) {
            sp--;
            int a = inc[sp];
            if (sp > 0)
                inc[sp-1] += inc[sp];
            inc[sp] = 0;
            return val[sp]+a;
        } else {
            return -1;
        }
    }
    
    void increment(int k, int a) {
        if (k > 0) {
            if (k < sp)
                inc[k-1] += a;
            else if (sp > 0)
                inc[sp-1] += a;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
