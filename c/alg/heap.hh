#include <cstdlib>
#include <algorithm>

inline size_t parent(size_t node) {
	return (node-1) >> 1;
}
inline size_t leftChild(size_t root) {
	return ((root+1) << 1) - 1;
}
inline size_t rightChild(size_t root) {
	return (root+1) << 1;
}
template <typename TI> inline TI smallest(TI left, TI right, TI end) {
	if (left < end) {
		if (right < end) {
			if (*left < *right)
				return left;
			else
				return right;
		} else {
			return left;
		}
	} else {
		return end;
	}
}
	
/**
 * when our root element increased we need to sieve it down to bring
 * the next smallest up
 * @param a - entire heap
 * @param root - increased element that you need to sieve
 * @param sz - size of the heap in array a
 */
template <typename TI> void siftDown(TI begin, TI root, TI end) {
	while (true) {
		size_t l = leftChild(root-begin);
		size_t r = rightChild(root-begin);
		TI sm = smallest(begin+l, begin+r, end);
		if (sm < end && *sm < *root) {
			std::swap(*sm, *root);
			root = sm;
		} else {
			break;
		}
	}
}

/**
 * Turn elements of array a into min-heap. The smallest element will be on top
 * @param a
 * @param sz
 */
template <typename TI> void heapify(TI begin, TI end) {
	size_t sz = end-begin;
	size_t root=(sz>>1);
	for (; root > 0; root--)
		siftDown(begin, begin+root, end);
	siftDown(begin, begin, end);
}

/**
 * Perform inverted sorting - greatest element will be first
 * @param a array to be sorted
 */
template <typename TI> void heapsort(TI begin, TI end) {
	heapify(begin, end);
	TI p = end;
	for (--p; p>begin; --p) {
		std::swap(*begin, *p);
		siftDown(begin, begin, p);
	}
}
