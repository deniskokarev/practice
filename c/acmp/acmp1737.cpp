/* ACMP 1737 */
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

struct lnum10 {
	constexpr static int base = 1000*1000*1000;
	using VEC = std::vector<int>;
	VEC a;
	lnum10(short n):a() {
		a.push_back(n);
	}
	std::string to_string() const {
		char buf[11];
		buf[10] = 0;
		snprintf(buf, 10, "%d", a.empty() ? 0 : a.back());
		std::string s(buf);
		for (int i=(int)a.size()-2; i>=0; --i) {
			snprintf(buf, 10, "%09d", a[i]);
			s.append(buf);
		}
		return s;
	}
	void operator*=(unsigned b) {
		assert(b<base);
		int carry = 0;
		for (size_t i=0; i<a.size() || carry; ++i) {
			if (i == a.size())
				a.push_back (0);
			long long cur = carry + a[i] * 1ll * b;
			a[i] = int (cur % base);
			carry = int (cur / base);
		}
		while (a.size() > 1 && a.back() == 0)
			a.pop_back();
	}
};

int main(int argc, char **argv) {
	char word[20001];
	scanf("%s", word);
	short len = strlen(word);
	lnum10 f(1);
	for (short i=2; i<=len; i++)
		f *= i;
	printf("%s\n", f.to_string().c_str());
	return 0;
}
