class NestedIterator {
    stack<pair<reference_wrapper<vector<NestedInteger>>,int>> stack;
    int curr;
public:
    // try to navigate from current node to first leaf
    bool goto_next_leaf() {
        bool found = false;
        if (!stack.empty()) {
            vector<NestedInteger> &list = stack.top().first;
            int &pos = stack.top().second;
            while (pos < list.size() && !found) {
                if (list[pos].isInteger()) {
                    curr = list[pos].getInteger();
                    found = true;
                } else {
                    stack.push({list[pos].getList(),0});
                    if (!goto_next_leaf())
                        stack.pop();
                    else
                        found = true;
                }
                pos++;
            }
        }
        return found;
    }
    
    NestedIterator(vector<NestedInteger> &nestedList):stack() {
        stack.push({nestedList,0});
        if (!goto_next_leaf())
            stack.pop();
    }
    
    int next() {
        int res = curr;
        while (!stack.empty() && !goto_next_leaf())
            stack.pop();
        return res;
    }
    
    bool hasNext() {
        return !stack.empty();
    }
};
