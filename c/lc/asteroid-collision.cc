// https://leetcode.com/problems/asteroid-collision/
class Solution {
public:
    static vector<int> asteroidCollision(const vector<int>& aa) {
        vector<int> res;
        for (auto a:aa) {
            if (res.empty()) {
                res.push_back(a);
            } else {
                if (a > 0) {
                    res.push_back(a);
                } else {
                    while (!res.empty() && res.back() > 0) {
                        if (res.back() < -a) {
                            res.pop_back();
                        } else if (res.back() == -a) {
                            res.pop_back();
                            a = 0;
                            break;
                        } else {
                            a = 0;
                            break;
                        }
                    }
                    if (a != 0) {
                        res.push_back(a);
                    }
                }
            }
        }
        return res;
    }
};

