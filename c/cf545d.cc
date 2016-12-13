#include <iostream>
#include <list>
#include <vector>
#include <algorithm>    // std::copy

/*
 * Codeforces 545d
 * 
Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are n people in the queue. For each person we know time ti needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

Examples
Input

5
15 2 1 5 3

Output

4

 */

template <class T> void readInts(T &l, std::istream &is) {
	int k;
	is >> k;
	for (int i=0; i<k; i++) {
		int n;
		is >> n;
		l.push_back(n);
	}
}

template <class T> struct ListNode {
	T el;
	ListNode *next;
	ListNode(T &e):el(e),next(nullptr) {}
	ListNode(T &e, ListNode *n):el(e),next(n) {}
	ListNode(T &e, ListNode *n, ListNode *d):el(e),next(n) {}
	~ListNode() {
		std::cerr << "disposing " << el << std::endl;
		if (next)
			delete(next);
	}
};

template <class T, class IT> static ListNode<T> *buildRevList(const typename IT::iterator &b, const typename IT::iterator &e) {
	ListNode<T> *node(nullptr);
	for (auto i=b; i!=e; ++i) {
		node = new ListNode<T>(*i, node);
	}
	return node;
}	

int bestPlace(int w,
			  const std::vector<int>::iterator &bestDst,
			  std::vector<int>::iterator &bestDstEnd,
			  ListNode<int> *src,
			  int srcSz) {
	int maxScore = -1;
	auto i(src);
	if (i != nullptr) {
		auto j=i->next;
		std::vector<int>::iterator nextBestDst(bestDst+srcSz);
		std::vector<int>::iterator nextBestDstEnd;
		int el = i->el;
		maxScore = bestPlace(w+el, nextBestDst, nextBestDstEnd, j, srcSz-1);
		maxScore += (el >= w ? 1 : 0);
		*bestDst = el;
		std::copy(nextBestDst, nextBestDstEnd, bestDst+1);
		while (j != nullptr) {
			int el = j->el;
			i->next = j->next;
			int score = bestPlace(w+el, nextBestDst, nextBestDstEnd, src, srcSz-1);
			score += (el >= w ? 1 : 0);
			if (score > maxScore) {
				maxScore = score;
				*bestDst = el;
				std::copy(nextBestDst, nextBestDstEnd, bestDst+1);
			}
			i->next = j;
			j = j->next;
			i = i->next;
		}
		bestDstEnd = bestDst+srcSz;
		return maxScore;
	} else {
		bestDstEnd = bestDst;
		return 0;
	}
}

int main(int argc, char **argv) {
	std::list<int> lst;
	readInts(lst, std::cin);
	std::cout << "In: " << std::endl;
	for (auto el : lst)
		std::cout << el << " ";
	std::unique_ptr<ListNode<int>> ln(buildRevList<int, decltype(lst)>(lst.begin(), lst.end()));
	std::cout << std::endl;
	std::vector<int> tmp((lst.size()*lst.size()+1)/2);
	std::vector<int>::iterator bb = tmp.begin();
	std::vector<int>::iterator be;
	int score = bestPlace(0, bb, be, ln.get(), lst.size());
	std::cout << "Score: " << score << std::endl;
	std::cout << "Placement: " << std::endl;
	for (auto i=bb; i!=be; ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
	return 0;
}
