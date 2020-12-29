class Solution {
    bool odd(int n) {
        return n&1;
    }
public:
    int reachNumber(int target) {
        if (target < 0)
            target = -target;
        int sm = 1;
        int steps = 1;
        while (sm < target) {
            steps++;
            sm += steps;
        }
        if (!odd(sm - target))
            return steps; // direct hit or overshot by even diff, just change sign on diff/2 element
        else if (!odd(steps))
            return steps + 1; // odd diff, but we can still correct parity on next step
        else
            return steps + 2; // odd diff and we cannot correct parity in one shot
    }
};
