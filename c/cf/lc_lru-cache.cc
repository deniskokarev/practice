#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <list>
/* https://leetcode.com/problems/lru-cache */

using namespace std;

class LRUCache {
	using KV = struct { int k, v; };
	int capacity;
	list<KV> ord;
	unordered_map<int,list<KV>::iterator> hash;
public:
	LRUCache(int cap):capacity(cap),ord(),hash(10*cap) {
	}
	
	int get(int key) {
		auto fnd = hash.find(key);
		if (fnd == hash.end()) {
			return -1;
		} else {
			auto it = fnd->second;
			int v = it->v;
			ord.erase(it);
			ord.push_front(KV{key,v});
			hash[key] = ord.begin();
			return v;
		}
	}
	
	void put(int key, int value) {
		auto fnd = hash.find(key);
		if (fnd == hash.end()) {
			if (ord.size()+1 > capacity) {
				auto it = prev(ord.end());
				hash.erase(it->k);
				ord.erase(it);
			}
		} else {
			ord.erase(fnd->second);
		}
		ord.push_front(KV{key,value});
		hash[key] = ord.begin();
	}
};

void test1() {
	LRUCache cache( 2 /* capacity */ );
	cache.put(1, 1);
	cache.put(2, 2);
	cerr << cache.get(1) << endl;       // returns 1
	cache.put(3, 3);    // evicts key 2
	cerr << cache.get(2) << endl;       // returns -1 (not found)
	cache.put(4, 4);    // evicts key 1
	cerr << cache.get(1) << endl;       // returns -1 (not found)
	cerr << cache.get(3) << endl;       // returns 3
	cerr << cache.get(4) << endl;       // returns 4
}

void test4() {
	LRUCache cache(1);
	cache.put(2, 1);
	cerr << cache.get(2) << endl; // 1
	cache.put(3, 2);
	cerr << cache.get(2) << endl; // -1
	cerr << cache.get(3) << endl; // 2
}

int main(int argc, char **argv) {
	//test1();
	test4();
	return 0;
}
