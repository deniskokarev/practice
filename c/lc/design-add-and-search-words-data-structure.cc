class WordDictionary {
    struct N {
        int chld[26]{0};
        bool end{false};
    };
    vector<N> trie;
public:
    /** Initialize your data structure here. */
    WordDictionary():trie(2) {
    }
    
    void addWord(const string &word) {
        int root = 1;
        for (char c:word) {
            int i = c-'a';
            if (!trie[root].chld[i]) {
                trie.push_back(N{});
                trie[root].chld[i] = trie.size()-1;
            }
            root = trie[root].chld[i];
        }
        trie[root].end = true;
    }
    
    bool search_impl(const string &word, int root, int pos) const {
        if (pos < word.size()) {
            if (word[pos] == '.') {
                for (int chld:trie[root].chld)
                    if (chld && search_impl(word, chld, pos+1))
                        return true;
            } else {
                int i = word[pos] - 'a';
                root = trie[root].chld[i];
                return search_impl(word, root, pos+1);
            }
            return false;
        } else {
            return trie[root].end;
        }
    }
    
    bool search(const string &word) const {
        return search_impl(word, 1, 0);
    }
};
