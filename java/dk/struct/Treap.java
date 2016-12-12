package dk.struct;

/**
 * BinaryTree/Heap hybrid
 * @author kokarev
 *
 * @param <K> - type of key as in a normal binary tree
 * @param <V> - type of value
 */
public class Treap<K extends Comparable<K>, V> {
	int priority; // specifies which level on the tree the element is added to
	K key;
	V value;
	Treap<K,V> left, right;
	
	static <K extends Comparable<K>,V> Treap<K,V> mergeNode(Treap<K,V> l, Treap<K,V> r) {
		if (l == null) {
			return r;
		} else if (r == null) {
			return l;
		} else if (l.priority > r.priority) {
			l.right = mergeNode(l.right, r);
			return l;
		} else {
			r.left = mergeNode(l, r.left);
			return r;
		}
	}

	static <K extends Comparable<K>,V> void splitNode(Treap<K,V> root, K k, Treap<K,V> lr) {
		if (root == null) {
			return;
		} else {
			int cmp = root.key.compareTo(k);
			Treap<K,V> llrr = new Treap<K,V>(0,null,null);
			if (cmp > 0) {
				splitNode(root.right, k, llrr);
				lr.left = root;
				root.right = llrr.left;
				lr.right = llrr.right;
			} else {
				splitNode(root.left, k, llrr);
				lr.right = root;
				root.left = llrr.right;
				lr.left = llrr.left;
			}
		}
	}

	/**
	 * Add element into treap
	 * @param p
	 * @param v
	 * @return
	 */
	static <K extends Comparable<K>,V> Treap<K,V> insertNode(Treap<K,V> root, Treap<K,V> node) {
		if (root == null) {
			return node;
		} else {
			int cmp = root.key.compareTo(node.key);
			if (node.priority > root.priority) {
				// insert at this level
				splitNode(root, node.key, node);
				return node;
			} else {
				if (cmp > 0) {
					root.left = insertNode(root.left, node);
				} else {
					root.right = insertNode(root.right, node);
				}
				return root;
			}
		}
	}
	/**
	 * delete root
	 * @param root
	 * @return new root node
	 */
	static <K extends Comparable<K>,V> Treap<K,V> deleteNode(Treap<K,V> root) {
		if (root != null) {
			return mergeNode(root.left, root.right);
		} else {
			return null;
		}
	}

	static <K extends Comparable<K>,V> Treap<K,V> findNode(Treap<K,V> root, K k) {
		if (root == null) {
			return null;
		} else if (root.key.equals(k)) {
			return root;
		} else if (root.key.compareTo(k) > 0) {
			return findNode(root.left, k);
		} else {
			return findNode(root.right, k);
		}
	}

	protected Treap(int p, K k, V v) {
		priority = p;
		key = k;
		value = v;		
	}
}
