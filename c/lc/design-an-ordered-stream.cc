class OrderedStream {
    vector<string> ord;
    int ptr = 0;
public:
    OrderedStream(int n):ord(n) {
    }
    
    vector<string> insert(int id, const string &value) {
        id--;
        ord[id] = value;
        vector<string> res;
        if (id == ptr)
            while (ptr < ord.size() && ord[ptr] != "")
                res.push_back(ord[ptr++]);
        return res;
    }
};
