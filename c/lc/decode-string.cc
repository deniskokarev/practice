class Solution {
	enum {
		M, S
	};
	struct T {
		int t;
		int m;
		string s;
	};
	static void eval_once(stack<T> &stack) {
		string s;
		while (stack.size() > 1) {
			s = stack.top().s;
			stack.pop();
			if (stack.top().t == M) {
				int m = stack.top().m;
				string sm = s;
				m--;
				while (m--)
					s += sm;
				stack.pop();
				stack.push({S,-1,s});
				break;
			} else {
				s = stack.top().s + s;
				stack.pop();
				stack.push({S,-1,s});
			}
		}
	}
public:
	static string decodeString(const string &s) {
		stack<T> stack;
		string num;
		for (char c:s) {
			if (c == '[') {
				stack.push({M,stoi(num),""});
				num = "";
			} else if (c == ']') {
				eval_once(stack);
			} else if ('0' <= c && c <= '9') {
				num += c;
			} else {
				stack.push({S,-1,string(1,c)});
			}
		}
		eval_once(stack);
		return stack.top().s;
	}
};

