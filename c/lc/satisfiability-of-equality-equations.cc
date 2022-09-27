// https://leetcode.com/problems/satisfiability-of-equality-equations/
#include <iostream>
#include <vector>
#include <array>

using namespace std;

constexpr int SZ = 26;

class Solution {
    static int get_parent(array<int, SZ> &pp, int c) {
        if (pp[c] == c)
            return c;
        else
            return pp[c] = get_parent(pp, pp[c]);
    }

    static inline void set_parent(array<int, SZ> &pp, int p, int c) {
        pp[get_parent(pp, c)] = get_parent(pp, p);
    }

public:
    static bool equationsPossible(const vector<string> &ee) {
        array<int, SZ> pp;
        for (int i = 0; i < SZ; i++)
            pp[i] = i;
        for (auto &e: ee) {
            int a = (e[0] - 'a') % SZ;
            int b = (e[3] - 'a') % SZ;
            if (e[1] == '=')
                set_parent(pp, a, b);
        }
        for (auto &e: ee) {
            int a = get_parent(pp, (e[0] - 'a') % SZ);
            int b = get_parent(pp, (e[3] - 'a') % SZ);
            if (e[1] == '!' && a == b)
                return false;
        }
        return true;
    }
};

int main() {
}
