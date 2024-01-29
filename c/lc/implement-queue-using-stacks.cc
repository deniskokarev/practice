// https://leetcode.com/problems/implement-queue-using-stacks
class MyQueue {
    vector<int> in, out;

    void mv() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push_back(in.back());
                in.pop_back();
            }
        }
    }

public:
    MyQueue() : in{}, out{} {
    }

    void push(int x) {
        in.push_back(x);
    }

    int pop() {
        mv();
        auto v = out.back();
        out.pop_back();
        return v;
    }

    int peek() {
        mv();
        return out.back();
    }

    bool empty() {
        return in.empty() && out.empty();
    }
};

