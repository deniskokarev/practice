// https://leetcode.com/problems/insert-delete-getrandom-o1/
class RandomizedSet {
    unordered_map<int,int> v2p;
    vector<int> vv;
public:
    /** Initialize your data structure here. */
    RandomizedSet():v2p(),vv() {
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (!v2p.count(val)) {
            v2p[val] = vv.size();
            vv.push_back(val);
            return true;
        } else {
            return false;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (v2p.count(val)) {
            int last = vv.back();
            int del_pos = v2p[val];
            swap(vv[del_pos], vv[vv.size()-1]);
            v2p[last] = del_pos;
            v2p.erase(val);
            vv.pop_back();
            return true;
        } else {
            return false;
        }
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int64_t r = rand();
        int r_pos = r * vv.size() / RAND_MAX;
        return vv[r_pos];
    }
};

