package dk.alg;

/**
 * Array-based min heap for int, long and T extends Comparable<T> types
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
	static void swap(int a[], int i, int j) {
		int c = a[j];
		a[j] = a[i];
		a[i] = c;
	}
	/**
	 * Turn elements of array a into min-heap. The smallest element will be on top
	 * @param a
	 * @param sz
	 */
	public static void heapify(int a[], int sz) {
		for (int i=sz-1; i>0; i--)
			if (a[i] < a[parent(i)])
				swap(a, i, parent(i));
	}
	static int smallest(int a[], int i, int j, int sz) {
		if (i < sz) {
			if (j < sz) {
				if (a[i] < a[j])
					return i;
				else
					return j;
			} else {
				return i;
			}
		} else {
			return -1;
		}
	}
	/**
	 * when our root element increased we need to sieve it to the bottom
	 * @param a - entire heap
	 * @param root - increased element that you need to sieve
	 * @param sz - size of the heap in array a
	 */
	public static void sift(int a[], int root, int sz) {
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
	 * Perform inverted sorting - greatest element will be first
	 * @param a array to be sorted
	 */
	public static void heapsort(int a[]) {
		heapify(a, a.length);
		for (int i=a.length-1; i>0; i--) {
			swap(a, 0, i);
			sift(a, 0, i);
		}
	}
	static void swap(long a[], int i, int j) {
		long c = a[j];
		a[j] = a[i];
		a[i] = c;
	}
	/**
	 * Turn elements of array a into min-heap. The smallest element will be on top
	 * @param a
	 * @param sz
	 */
	static void heapify(long a[], int sz) {
		for (int i=sz-1; i>0; i--)
			if (a[i] < a[parent(i)])
				swap(a, i, parent(i));
	}
	static int smallest(long a[], int i, int j, int sz) {
		if (i < sz) {
			if (j < sz) {
				if (a[i] < a[j])
					return i;
				else
					return j;
			} else {
				return i;
			}
		} else {
			return -1;
		}
	}
	/**
	 * when our root element increased we need to sieve it to the bottom
	 * @param a - entire heap
	 * @param root - increased element that you need to sieve
	 * @param sz - size of the heap in array a
	 */
	public static void sift(long a[], int root, int sz) {
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
	 * Perform inverted sorting - greatest element will be first
	 * @param a array to be sorted
	 */
	static void heapsort(long a[]) {
		heapify(a, a.length);
		for (int i=a.length-1; i>=0; i--) {
			swap(a, 0, i);
			sift(a, 0, i);
		}
	}
	static <T> void swap(T a[], int i, int j) {
		T c = a[j];
		a[j] = a[i];
		a[i] = c;
	}
	/**
	 * Turn elements of array a into min-heap. The smallest element will be on top
	 * @param a
	 * @param sz
	 */
	public static <T extends Comparable<T>> void heapify(T a[], int sz) {
		for (int i=sz-1; i>0; i--)
			if (a[i].compareTo(a[parent(i)]) < 0)
				swap(a, i, parent(i));
	}
	static <T extends Comparable<T>> int smallest(T a[], int i, int j, int sz) {
		if (i < sz) {
			if (j < sz) {
				if (a[i].compareTo(a[j]) < 0)
					return i;
				else
					return j;
			} else {
				return i;
			}
		} else {
			return -1;
		}
	}
	/**
	 * when our root element increased we need to sieve it to the bottom
	 * @param a - entire heap
	 * @param root - increased element that you need to sieve
	 * @param sz - size of the heap in array a
	 */
	static <T extends Comparable<T>> void sift(T a[], int root, int sz) {
		while (true) {
			int l = leftChild(root);
			int r = rightChild(root);
			int sm = smallest(a, l, r, sz);
			if (sm > 0 && a[sm].compareTo(a[root]) < 0) {
				swap(a, sm, root);
				root = sm;
			} else {
				break;
			}
		}
	}
	/**
	 * Perform inverted sorting - greatest element will be first
	 * @param a array to be sorted
	 */
	static <T extends Comparable<T>> void heapsort(T a[]) {
		heapify(a, a.length);
		for (int i=a.length-1; i>=0; i--) {
			swap(a, 0, i);
			sift(a, 0, i);
		}
	}
	public static void main(String args[]) {
		int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		heapsort(a);
		for (int i:a) {
			System.out.println(i);
		}
	}
}
