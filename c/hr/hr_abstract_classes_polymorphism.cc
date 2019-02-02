/* Hackerrank https://www.hackerrank.com/challenges/abstract-classes-polymorphism */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

#include <list>
class LRUCache: public Cache {
	size_t cap;
	std::list<pair<int,int>> cache;
	std::map<int, std::list<pair<int,int>>::iterator> map;
public:
	LRUCache(size_t cap):cap{cap},cache(cap),map() {}
	virtual void set(int k, int v) {
		auto fnd = map.find(k);
		if (fnd != map.end()) {
			cache.erase(fnd->second);
		} else {
			if (cache.size() >= cap) {
				auto &e = cache.back();
				map.erase(e.first);
				cache.erase(prev(cache.end()));
			}
		}
		cache.push_front(make_pair(k,v));
		map[k] = cache.begin();
	}
	virtual int get(int k) {
		auto fnd = map.find(k);
		if (fnd != map.end()) {
			return fnd->second->second;
		} else {
			return -1;
		}
	}
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
