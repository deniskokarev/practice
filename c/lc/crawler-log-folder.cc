class Solution {
public:
    int minOperations(vector<string>& logs) {
        int dep = 0;
        for (auto &s:logs) {
            if (s == "../")
                dep--;
            else if (s != "./")
                dep++;
            dep = max(0, dep);
        }
        return dep;
    }
};
