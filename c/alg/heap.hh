#include <cstdlib>
#include <algorithm>

/**
 * when our root element increased we need to sieve it down to bring
 * the next smallest up
 * @param n - the node that we need to bring down 
 * @param begin - vector (random access iterator) of values
 * @param sz - vector size
 */
template <typename TI> void sift_node(
	  typename std::iterator_traits<TI>::difference_type n,
	  TI const begin,
	  const typename std::iterator_traits<TI>::difference_type sz
) {
	auto c = n*2+1;	// left child
	while (c+1 < sz) { // while right child available
		if (begin[c+1] < begin[c])
			c++; // switch to right child
		if (begin[c] < begin[n])
			std::swap(begin[c], begin[n]);
		else
			break;
		n = c;
		c = n*2+1; // left child
	}
	if (c < sz && begin[c] < begin[n])
		std::swap(begin[c], begin[n]);
}

/**
 * Turn elements of random access container into min-heap. The smallest element will be at pos 0
 * @param begin
 * @param end
 * expecting (end-begin) > 0
 */
template <typename TI> void heapify(TI begin, TI end) {
	const auto sz = end-begin;
	const auto hsz = sz/2-1;
	for (auto r=hsz; r>=0; r--)
		sift_node(r, begin, sz);
}

/**
 * Perform inverted sorting - greatest element will be first
 * @param begin, end - the vector to be sorted
 * expecting (end-begin) > 0
 */
template <typename TI> void heapsort(TI begin, TI end) {
	heapify(begin, end);
	TI p(end);
	auto sz = end-begin;
	for (--p,--sz; p>begin; --p,--sz) {
		std::swap(*begin, *p);
		sift_node(0, begin, sz);
	}
}
