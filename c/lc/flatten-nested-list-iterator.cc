class NestedIterator {
    stack<pair<reference_wrapper<vector<NestedInteger>>,int>> stack;
    int curr;
public:
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
                    found |= goto_next_leaf();
                }
                pos++;
            }
            if (!found)
                stack.pop();
        }
        return found;
    }
    
    NestedIterator(vector<NestedInteger> &nestedList):stack() {
        stack.push({nestedList,0});
        goto_next_leaf();
    }
    
    int next() {
        int res = curr;
        while (!stack.empty() && !goto_next_leaf());
        return res;
    }
    
    bool hasNext() {
        return !stack.empty();
    }
};
