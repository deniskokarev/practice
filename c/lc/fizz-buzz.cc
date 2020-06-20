// https://leetcode.com/problems/fizz-buzz
using F = void (*)(vector<string> &out, int n);

static void f(vector<string> &out, int i) {
	out[i] = "Fizz";
}
static void b(vector<string> &out, int i) {
	out[i] = "Buzz";
}
static void fb(vector<string> &out, int i) {
	out[i] = "FizzBuzz";
}
static void n(vector<string> &out, int i) {
	out[i] = to_string(i+1);
}

constexpr int SZ = 15;
constexpr F CYCLE[SZ] {&fb, &n, &n, &f, &n, &b, &f, &n, &n, &f, &b, &n, &f, &n, &n};

class Solution {
public:
	static vector<string> fizzBuzz(int n) {
		vector<string> out(n);
		for (int i=1; i<=n; i++)
			CYCLE[i%SZ](out, i-1);
		return out;
	}
};

