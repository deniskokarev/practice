// https://leetcode.com/problems/smallest-number-in-infinite-set/
class SmallestInfiniteSet {
    std::priority_queue<int, std::vector<int>, std::greater<int>> mnq;
    int mx;
public:
    SmallestInfiniteSet() : mnq{}, mx{1} {
        mnq.push(1);
    }

    int popSmallest() {
        int v = mnq.top();
        mnq.pop();
        while (!mnq.empty() && mnq.top() == v) {
            mnq.pop();
        }
        if (v == mx) {
            mnq.push(v + 1);
            mx++;
        }
        return v;
    }

    void addBack(int num) {
        mnq.push(num);
    }
};
