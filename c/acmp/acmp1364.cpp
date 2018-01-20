/* ACMP 1364 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct S {
	int parent;
	const char *op;
	int a, b;
	int depth;
	size_t hash() const {
		return size_t(a)*20000+b;
	}
	bool operator==(const S &b) const {
		return a == b.a && b == b.b;
	}
	bool operator==(int n) const {
		return a == n || b == n;
	}
};

struct SHash {
	size_t operator()(const S &s) const {
		return s.hash();
	}
};

inline void optadd(const S &s, vector<S> &path, unordered_set<S, SHash> &seen) {
	if (seen.find(s) == seen.end()) {
		path.push_back(s);
		seen.insert(s);
	}
}

inline int generate(int srcidx, vector<S> &path, int va, int vb, unordered_set<S, SHash> &seen) {
	int rc = (int)path.size();
	const S src = path[srcidx];
	optadd(S {srcidx, ">A", va, src.b, src.depth+1}, path, seen);
	optadd(S {srcidx, ">B", src.a, vb, src.depth+1}, path, seen);
	optadd(S {srcidx, "A>", 0, src.b, src.depth+1}, path, seen);
	optadd(S {srcidx, "B>", src.a, 0, src.depth+1}, path, seen);
	int por = min(src.a, vb-src.b);
	optadd(S {srcidx, "A>B", src.a-por, src.b+por, src.depth+1}, path, seen);
	por = min(src.b, va-src.a);
	optadd(S {srcidx, "B>A", src.a+por, src.b-por, src.depth+1}, path, seen);
	return (int)path.size()-rc;
}

int main(int argc, char **argv) {
	int va, vb, vn;
	cin >> va >> vb >> vn;
	unordered_set<S, SHash> seen; // all visited states
	vector<S> path; // all visited states with indexes for backtracking
	queue<int> qq;  // wave-front of the states to visit (index points to path element)
	path.push_back(S {-1, "start", 0, 0, 0});
	qq.push(0);
	while (qq.size() > 0) {
		int curr = qq.front();
		const S s = path[curr];
		if (s == vn)
			break;
		int nsz = generate(curr, path, va, vb, seen);
		for (int i=1; i<=nsz; i++)
			qq.push((int)path.size()-i);
		qq.pop();
	}
	if (qq.size() > 0) {
		deque<string> da;
		int curr = qq.front();
		while (curr > 0) {
			const S &s = path[curr];
			//cerr << "op: " << s.op << " par: " << s.parent << " dep: " << s.depth << " a: " << s.a << " b: " << s.b << endl;
			da.push_front(s.op);
			curr = s.parent;
		}
		for (auto s:da)
			cout << s << endl;
	} else {
		cout << "Impossible" << endl;
	}
	return 0;
}
