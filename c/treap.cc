#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef string KEY;
typedef int LVL;
typedef string VAL;

struct Node {
	KEY key;
	VAL val;
	Node *l, *r;
	LVL lvl;
	Node(const KEY &k, const VAL &v):key(k),val(v),l(nullptr),r(nullptr),lvl(rand()%100){}
	virtual ~Node() {
		if (l)
			delete l;
		if (r)
			delete r;
	}
};

Node *merge(Node *l, Node *r) {
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->lvl < r->lvl) {
		l->r = merge(l->r, r);
		return l;
	} else {
		r->l = merge(l, r->l);
		return r;
	}
}

void split(Node *n, string &key, Node *&pl, Node *&pr) {
	Node *l, *r;
	if (!n) {
		pl = nullptr;
		pr = nullptr;
	} else if (key > n->key) {
		split(n->r, key, l, r);
		n->r = l;
		pl = n;
		pr = r;
	} else {
		split(n->l, key, l, r);
		n->l = r;
		pl = l;
		pr = n;
	}
}

Node *remove(Node *n) {
	Node *r = n->r;
	Node *l = n->l;
	n->l = n->r = nullptr;
	return merge(l, r);
}

Node *insert(Node *o, Node *n) {
	if (!o)
		return n;
	if (n->lvl > o->lvl) {
		if (o->key < n->key)
			o->r = insert(o->r, n);
		else
			o->l = insert(o->l, n);
		return o;
	} else {
		split(o, n->key, n->l, n->r);
		return n;
	}
}

void prn(Node *n, int lvl) {
	if (!n)
		return;
	prn(n->l, lvl+1);
	for (int i=0; i<lvl; i++)
		cout << " ";
	cout << "[" << n->lvl << ":" << n->key << "]->" << n->val << endl;
	prn(n->r, lvl+1);
}

void prn_keys(Node *n) {
	if (!n)
		return;
	prn_keys(n->l);
	cout << n->key << endl;
	prn_keys(n->r);
}

int main(int argc, char **argv) {
	Node *root = nullptr;
	vector<string> keys = {"1", "2", "3", "4", "5"};
	srand(time(NULL));
	for (int i=0; i<31; i++) {
		int rnd = rand() % keys.size();
		root = insert(root, new Node(keys[rnd], to_string(i)));
	}
	cout << ">>> sorted keys <<<" << endl;
	prn_keys(root);
	cout << ">>> whole tree <<<" << endl;
	prn(root, 0);
	delete root;
	return 0;
}

