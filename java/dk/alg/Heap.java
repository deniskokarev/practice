package dk.draft;

public class Heap {
	static int root(int node) {
		return (node-1)/2;
	}
	static int left(int root) {
		return ((root+1) << 1) - 1;
	}
	static int right(int root) {
		return (root+1) << 1;
	}
	static void swap(int a[], int i, int j) {
		int c = a[j];
		a[j] = a[i];
		a[i] = c;
	}
	static void heapify(int a[], int sz) {
		for (int i=sz-1; i>0; i--)
			if (a[i] < a[root(i)])
				swap(a, i, root(i));
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
	static void seave(int a[], int sz) {
		int root = 0;
		while (true) {
			int l = left(root);
			int r = right(root);
			int sm = smallest(a, l, r, sz);
			if (sm > 0 && a[sm] < a[root]) {
				swap(a, sm, root);
				root = sm;
			} else {
				break;
			}
		}
	}
	static void heapsort(int a[]) {
		heapify(a, a.length);
		for (int i=a.length-1; i>=0; i--) {
			swap(a, 0, i);
			seave(a, i);
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
