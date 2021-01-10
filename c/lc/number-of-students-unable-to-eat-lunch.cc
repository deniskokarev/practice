class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        deque<int> st(students.begin(), students.end());
        reverse(sandwiches.begin(), sandwiches.end());
        int dsz = sandwiches.size();
        for (int i=0; !st.empty() && i<dsz*dsz; i++) {
            if (st.front() == sandwiches.back()) {
                sandwiches.pop_back();
                st.pop_front();
            } else {
                int fst = st.front();
                st.pop_front();
                st.push_back(fst);
            }
        }
        return st.size();
    }
};
