class Solution {
public:
	string simplifyPath(const string &path) {
		vector<char*> ss;
		char str[4096];
		strncpy(str, path.c_str(), 4096);
		char *r = nullptr;
		for (char *tok=strtok_r(str, "/", &r); tok; tok=strtok_r(nullptr, "/", &r)) {
			if (strcmp(tok, "..") == 0) {
				if (!ss.empty())
					ss.pop_back();
			} else if (strcmp(tok, ".") != 0 && *tok) {
				ss.push_back(tok);
			}
		}
		if (!ss.empty()) {
			string res;
			for (char *s:ss)
				res += string("/") + s;
			return res;
		} else {
			return "/";
		}
	}
};
