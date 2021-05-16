#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <list>
#include <functional>

/* ACMP 1282 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	scanf("%d\n", &n);
	unordered_map<string,int> nm2cnt;
	list<string> nms;
	int mx = 0;
	while (n--) {
		char ln[100];
		fgets(ln, sizeof(ln), stdin);
		char *p;
		int tok_sz = 0;
		const char *tok[4];
		for (const char *t=strtok_r(ln, " \n", &p); t; t=strtok_r(NULL, " \n", &p))
			tok[tok_sz++] = t;
		const char *nm = tok[1];
		const char *sex = tok[tok_sz-1];
		if (sex[0] == 'w') {
			auto fnd = nm2cnt.find(nm);
			if (fnd == nm2cnt.end())
				nms.push_back(nm);
			int &cnt = nm2cnt[nm];
			cnt++;
			mx = max(mx, cnt);
		}
	}
	if (mx == 0) {
		printf("NO DATA!\n");
	} else if (mx == 1) {
		printf("UNIQUE!\n");
	} else {
		list<reference_wrapper<string>> out;
		for (string &nm:nms)
			if (nm2cnt[nm] == mx)
				out.push_back(nm);
		auto it = out.begin();
		while (next(it) != out.end()) {
			string &s = *it;
			printf("%s,", s.c_str());
			it = next(it);
		}
		string &s = *it;
		printf("%s\n", s.c_str());
	}
	return 0;
}
