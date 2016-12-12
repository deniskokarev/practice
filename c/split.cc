/*
  split set into k parts 
 */

#include <iostream>
#include <list>

using namespace std;

/* each subset */
struct FN {
	virtual void operator()(const list<string> &s) = 0;
};

/* end of split */
struct FNN {
	virtual void operator()() = 0;
};

/* append element to each subset */
struct append_act : public FN {
	FN &parent;
	const string &el;
	int which;
	append_act(FN &p, string &e):parent(p),el(e),which(0){}
	virtual void operator()(const list<string> &s) override {
		//		for (auto i=s.begin(); i!=s.end(); i++){}
		list<string> ns;
		copy(s.begin(), s.end(), back_inserter(ns));
		ns.push_back(el);
		parent(ns);
	}
};

/* append a singular subset of only one element before ending the split */
struct append_actn : public FNN {
	FN &parent_a;
	FNN &parent_an;
	list<string> sinel;
	append_actn(FN &a, FNN &an, const string &e):parent_a(a),parent_an(an),sinel() {
		sinel.push_back(e);
	}
	virtual void operator()() override {
		parent_a(sinel);
		parent_an();
	}
};

void split(const list<string> &s, int k, FN &act, FNN &actn) {
	if (k<=1) {
		act(s);
		actn();
	} else if (s.size() >= 1) {
		string lst = s.back();
		append_actn an(act, actn, lst);
		append_act a(act, lst);
		list<string> ns;
		auto end = s.end();
		end--;
		ns.clear();
		copy(s.begin(), end, back_inserter(ns));
		split(ns, k-1, act, an);
		ns.clear();
		copy(s.begin(), end, back_inserter(ns));
		split(ns, k, a, actn);
	}
}

struct ps : public FN {
	virtual void operator()(const list<string> &s) override {
		for (auto i : s)
			cout << i << " ";
		cout << endl;
	}
};

struct psnl : public FNN {
	virtual void operator()() {
		cout << "====================" << endl;
	}
};

int main(int argc, char **argv) {
	list<string> s= {"1", "2", "3", "4", "5"};
	ps ps;
	psnl psnl;
	split(s, 2, ps, psnl);
}

