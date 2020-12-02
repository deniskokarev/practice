class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int mx = 0;
        string pat(word);
        while (sequence.find(pat) != std::string::npos) {
            mx++;
            pat += word;
        }
        return mx;
    }
};
