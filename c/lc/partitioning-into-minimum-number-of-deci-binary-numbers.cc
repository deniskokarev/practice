class Solution {
public:
    // there is no need in more than 9 numbers, thus
    // carryover doesn't apply, therefore the solution is trivial
    int minPartitions(string n) {
        return *max_element(n.begin(), n.end()) - '0';
    }
};
