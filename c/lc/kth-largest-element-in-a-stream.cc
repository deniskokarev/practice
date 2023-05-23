// https://leetcode.com/problems/kth-largest-element-in-a-stream/

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> minh;
public:
    KthLargest(int k, const vector<int>& nums): k{k}, minh{begin(nums),end(nums)} {
        while (minh.size() > k) {
            minh.pop();
        }
    }
    
    inline int add(int val) {
        if (minh.size() < k) {
            minh.push(val);
        } else {
            if (val > minh.top()) {
                minh.pop();
                minh.push(val);
            }
        }
        return minh.top();
    }
};

