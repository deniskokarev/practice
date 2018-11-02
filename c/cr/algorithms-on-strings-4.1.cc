#include <iostream>
#include <vector>

using namespace std;

// suffix function (z function)
// compute suffix sizes for string s of size sz
// zz random access iterator should have the same size
// implementation from wikipedia
template <typename RIC, typename RIN> void suffix_function(const RIC s, size_t len, RIN z) {
	using T = typename std::iterator_traits<RIN>::value_type;
    z[0] = 0;
    for (T j,i=1,l=0,r=0; i < len; i++) {
        if (i > r) {
            for (j = 0; ((j + i) < len) && (s[i + j] == s[j]); j++);
            z[i] = j;
            l = i;
            r = (i + j - 1);
        } else {
            if (z[i - l] < (r - i + 1)) {
                z[i] = z[i - l];
            } else {
                for (j = 1; ((j + r) < len) && (s[r + j] == s[r - i + j]); j++);
                z[i] = (r - i + j);
                l = i;
                r = (r + j - 1);
            }
        }
    }
}

int main(int argc, char **argv) {
	string pat, txt;
	cin >> pat;
	cin >> txt;
	string ss = pat + '#' + txt;
	vector<int> sfx(ss.size());
	suffix_function(ss.begin(), ss.size(), sfx.begin());
	int sz = pat.size();
	for (int i=sz+1; i<sfx.size(); i++)
		if (sfx[i] == sz)
			cout << i-sz-1 << ' ';
	cout << endl;
	return 0;
}
