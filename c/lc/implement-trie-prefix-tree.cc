class Trie {
    struct N {
        int chld[26]{0};
        bool end{false};
    };
    vector<N> trie;
public:
    /** Initialize your data structure here. */
    Trie():trie(2) {
        trie[1].end = true; // make startsWith("") == true
    }
    
    /** Inserts a word into the trie. */
    void insert(const string &word) {
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
    
    /** Returns if the word is in the trie. */
    bool search(const string &word) const {
        int root = 1;
        for (char c:word) {
            int i = c-'a';
            root = trie[root].chld[i];
        }
        return trie[root].end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string &prefix) const {
        int root = 1;
        for (char c:prefix) {
            int i = c-'a';
            root = trie[root].chld[i];
        }
        return root;
    }
};
