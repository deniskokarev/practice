#include <iostream>
#include <algorithm>

#if 0
static int parent(int node) {
	return (node-1) >> 1;
}
#endif

static int leftChild(int root) {
	return ((root+1) << 1) - 1;
}
static int rightChild(int root) {
	return (root+1) << 1;
}
static void swap(long a[], int i, int j) {
	long c = a[j];
	a[j] = a[i];
	a[i] = c;
}
static int smallest(long a[], int left, int right, int sz) {
	if (left < sz) {
		if (right < sz) {
			if (a[left] < a[right])
				return left;
			else
				return right;
		} else {
			return left;
		}
	} else {
		return -1;
	}
}
	
/**
 * when our root element increased we need to sieve it down to bring
 * the next smallest up
 * @param a - entire heap
 * @param root - increased element that you need to sieve
 * @param sz - size of the heap in array a
 */
static void sift(long a[], int root, int sz) {
	while (true) {
		int l = leftChild(root);
		int r = rightChild(root);
		int sm = smallest(a, l, r, sz);
		if (sm > 0 && a[sm] < a[root]) {
			swap(a, sm, root);
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
static void heapify(long a[], int sz) {
	for (int root=(sz>>1); root >= 0; root--)
		sift(a, root, sz);
}
	
/**
 * Perform inverted sorting - greatest element will be first
 * @param a array to be sorted
 */
void heapsort(long a[], int sz) {
	heapify(a, sz);
	for (int i=sz-1; i>0; i--) {
		swap(a, 0, i);
		sift(a, 0, i);
	}
}

int main(int argc, char **argv) {
	int sz = 1<<28;
	long *a = new long[sz];
	for (int i=0; i<sz; i++)
		a[i] = sz-i;
	//std::make_heap(a, a+sz);
	//std::sort_heap(a, a+sz);
	//std::sort(a, a+sz);
	heapsort(a, sz);
	delete[] a;
}
