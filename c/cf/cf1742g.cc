#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1742G problem */
using namespace std;

int main(int argc, char **argv) {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> aa(n);
        for (auto &a:aa)
            cin >> a;
        int head = 0;
        int msk = 0;
        int tail = n;
        // sort aa
        while (head < tail) {
            // find remaining max and place it into aa[head]
            for (int i=head; i<tail; i++)
                if ((aa[head] & ~msk) < (aa[i] & ~msk))
                    swap(aa[head], aa[i]);
            msk |= aa[head];
            head++;
            // move non-essential elements to the back
            int i = head;
            while (i < tail)
                if (!(aa[i] & ~msk))
                    swap(aa[i], aa[--tail]);
                else
                    i++;
        }
        // print sorted aa
        for (auto a:aa)
            cout << a << ' ';
        cout << '\n';
    }
    return 0;
}
