// https://leetcode.com/problems/insert-delete-getrandom-o1/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

class RandomizedSet {
    vector<int> ord;
    unordered_map<int,int> v2o;
    mt19937 rnd;
public:
    RandomizedSet():ord(),v2o(),rnd(0) {
    }

    bool insert(int val) {
        bool is_there = (v2o.find(val) != v2o.end());
        if (!is_there) {
            v2o[val] = ord.size();
            ord.push_back(val);
        }
        return !is_there;
    }

    bool remove(int val) {
        auto fnd = v2o.find(val);
        bool is_there = (fnd != v2o.end());
        if (is_there) {
            int p = fnd->second;
            v2o.erase(fnd);
            if (p < ord.size() - 1) {
                // if we're deleting not the last element
                v2o[ord.back()] = p;
                ord[p] = ord.back();
            }
            ord.pop_back();
        }
        return is_there;
    }

    int getRandom() {
        int rp = rnd() % ord.size();
        return ord[rp];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
int main(int argc, char **argv) {
    RandomizedSet r;
    cout << r.remove(0) << endl;
    cout << r.remove(0) << endl;
    cout << r.insert(0) << endl;
    cout << r.getRandom() << endl;
    cout << r.remove(0) << endl;
    cout << r.insert(0) << endl;
    return 0;
}

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

