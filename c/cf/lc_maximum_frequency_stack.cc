#include <map>
#include <list>
/* https://leetcode.com/problems/maximum-frequency-stack/ */

struct E {
	int freq;
	int ord;
	int num;
	E():freq(0),ord(0){}
	bool operator<(const E &o) const {
		return freq>o.freq || (freq==o.freq && ord>o.ord);
	}
};

class FreqStack {
	std::map<int,E> i2e;
	std::map<E,int> e2i;
    std::map<int,std::list<int>> i2ord;
	int ord;
public:
	FreqStack():i2e(),e2i(),i2ord(),ord{1} {
	}
	
	void push(int x) {
		E &e = i2e[x];
		if (e.ord != 0)
			e2i.erase(e);
		e.ord = ord;
		e.freq++;
		e.num = x;
		e2i[e] = x;
        i2ord[x].push_back(ord++);
	}
	
	int pop() {
		int x = e2i.begin()->first.num;
		E &e = i2e[x];
		e2i.erase(e);
		e.freq--;
        i2ord[x].pop_back();
        e.ord = i2ord[x].back();
		e2i[e] = x;
		return x;
	}
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
