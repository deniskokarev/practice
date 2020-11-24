class ThroneInheritance {
    vector<vector<int>> ee;
    vector<string> nn;
    map<string,int> n2id;
    vector<bool> is_dead;
public:
    ThroneInheritance(string kingName):nn{kingName},ee{{}},n2id{{kingName,0}},is_dead{false} {
    }
    
    void birth(const string &parentName, const string &childName) {
        int pid = n2id[parentName];
        ee.push_back({});
        n2id[childName] = nn.size();
        ee[pid].push_back(nn.size());
        is_dead.push_back(false);
        nn.push_back(childName);
    }
    
    void death(const string &name) {
        is_dead[n2id[name]] = true;
    }
    
    void getInheritanceOrder(vector<string> &res, int root) {
        if (!is_dead[root])
            res.push_back(nn[root]);
        for (int c:ee[root])
            getInheritanceOrder(res, c);
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> res;
        getInheritanceOrder(res, 0);
        return res;
    }
};
