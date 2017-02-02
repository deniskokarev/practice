package dk.alg;

/**
 * Array-based min heap for long type
 * Root element will be the smallest
 * @author kokarev
 *
 */
public class Heap {
	static int parent(int node) {
		return (node-1) >> 1;
	}
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
	 * Turn elements of array a into min-heap. The smallest element will be on top
	 * @param a
	 * @param sz
	 */
	public static void heapify(long a[], int sz) {
		for (int root=(sz>>1)-1; root >= 0; root--)
			siftDown(a, root, sz);
	}
	
	/**
	 * when our root element increased we need to sieve it down to bring
	 * the next smallest up
	 * @param a - entire heap
	 * @param root - increased element that you need to sieve
	 * @param sz - size of the heap in array a
	 */
	public static void siftDown(long a[], int root, int sz) {
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
	 * when our node element decreased we need to bubble it up
	 * @param a - entire heap
	 * @param node - increased element that you need to sieve
	 */
	public static void siftUp(long a[], int node) {
		while (node > 0) {
			int parent = parent(node);
			if (a[node] < a[parent])
				swap(a, node, parent);
			else
				break;
			node = parent;
		}
	}
	
	/**
	 * Perform inverted sorting - greatest element will be first
	 * @param a array to be sorted
	 */
	public static void heapsort(long a[]) {
		heapify(a, a.length);
		for (int i=a.length-1; i>0; i--) {
			swap(a, 0, i);
			siftDown(a, 0, i);
		}
	}
}
