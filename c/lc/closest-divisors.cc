class Solution {
    pair<int,int> f(int num) {
        int a, b;
        for (int i=1; i*i<=num; i++) {
            if ((num % i) == 0) {
                a = i;
                b = num/i;
            }
        }
        return {a,b};
    }
public:
    vector<int> closestDivisors(int num) {
        auto a1 = f(num+1);
        auto a2 = f(num+2);
        if (abs(a1.first-a1.second) < abs(a2.first-a2.second))
            return {a1.first, a1.second};
        else
            return {a2.first, a2.second};
    }
};
