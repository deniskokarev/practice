package dk.struct;

/**
 * BinaryTree/Heap hybrid with Attrubute-aware values. I.e. each value has an attrubute, which aggregates
 * attributes of left and right children. If the attribute was simply the number of elements then
 * root would have the total count
 * @author kokarev
 *
 * @param <K> - type of key as in a normal binary tree
 * @param <V> - type of value
 */
public class AttrTreap<K extends Comparable<K>, V extends AttrValue<?>> {
	public int priority; // specifies which level on the tree the element is added to
	public K key;
	public V value;
	public AttrTreap<K,V> left, right;	// don't wonna use array 
	protected final static int LEFT = 0, RIGHT = 1;

	public String toString() {
		StringBuffer sb = new StringBuffer("[");
		if (left != null)
			sb.append("<+>");
		else
			sb.append("<>");
		sb.append("<");
		sb.append(priority);
		sb.append(":");
		sb.append(key);
		sb.append(":");
		sb.append(value);
		sb.append(">");
		if (right != null)
			sb.append("<+>");
		else
			sb.append("<>");
		sb.append("]");
		return sb.toString();
	}
	
	protected void treeToStringHelper(int level, StringBuffer sb) {
		if (left != null)
			left.treeToStringHelper(level+1, sb);
		for (int i=0; i<level; i++)
			sb.append("  ");
		sb.append("<");
		sb.append(priority);
		sb.append(":");
		sb.append(key);
		sb.append(":");
		sb.append(value);
		sb.append(">\n");
		if (right != null)
			right.treeToStringHelper(level+1, sb);
	}
	
	public String treeToString() {
		StringBuffer sb = new StringBuffer();
		treeToStringHelper(0, sb);
		return sb.toString();
	}

	static <K extends Comparable<K>, A, V extends AttrValue<A>> void updateNodeAttr(AttrTreap<K,V> node) {
		if (node.value != null)
			node.value.updateAttr((node.left!=null)?node.left.value:null, (node.right!=null)?node.right.value:null);
	}
	
	/**
	 * Merge l and r nodes into a common root node
	 * @param l
	 * @param r
	 * @return new root
	 */
	static <K extends Comparable<K>, A, V extends AttrValue<A>> AttrTreap<K,V> mergeNode(AttrTreap<K,V> l, AttrTreap<K,V> r) {
		if (l == null) {
			return r;
		} else if (r == null) {
			return l;
		} else if (l.priority > r.priority) {
			l.right = mergeNode(l.right, r);
			updateNodeAttr(l);
			return l;
		} else {
			r.left = mergeNode(l, r.left);
			updateNodeAttr(r);
			return r;
		}
	}

	/**
	 * Split root node into two subtrees depending on the key
	 * @param root - what we're splitting 
	 * @param splitKey - split criteria, i.e. what stays to the left and what stays to the right of key 
	 * @param l[lDir] - recipient for the left subtree 
	 * @param r[rDir] - recipient for right subtree
	 */
	static <K extends Comparable<K>, A, V extends AttrValue<A>> void splitNode(AttrTreap<K,V> root, K splitKey, AttrTreap<K,V> l, int lDir, AttrTreap<K,V> r, int rDir) {
		int cmp = root.key.compareTo(splitKey);
		if (cmp <= 0) {
			if (root.right != null) {
				splitNode(root.right, splitKey, root, RIGHT, r, rDir);
			} else {
				if (rDir == LEFT)
					r.left = null;
				else
					r.right = null;
				updateNodeAttr(r);
			}
			if (lDir == LEFT)
				l.left = root;
			else
				l.right = root;
			updateNodeAttr(l);
		} else {
			if (root.left != null) {
				splitNode(root.left, splitKey, l, lDir, root, LEFT);
			} else {
				if (lDir == LEFT)
					l.left = null;
				else
					l.right = null;
				updateNodeAttr(l);
			}
			if (rDir == LEFT)
				r.left = root;
			else
				r.right = root;
			updateNodeAttr(r);
		}
	}

	/**
	 * Split a tree into two subtrees depending on the key
	 * @param root - what we're splitting 
	 * @param splitKey - split criteria, i.e. what stays to the left and what stays to the right of key 
	 * @param newRoot.left - gets left part of the split where keys <= splitKey
	 * @param newRoot.right - gets right part of the split where keys > splitKey
	 */
	public static <K extends Comparable<K>, A, V extends AttrValue<A>> void splitTree(AttrTreap<K,V> root, K splitKey, AttrTreap<K,V> newRoot) {
		splitNode(root, splitKey, newRoot, LEFT, newRoot, RIGHT);
	}
	
	/**
	 * Add element into treap
	 * @param root - current root node
	 * @param node - node to be inserted
	 * @return new root node
	 */
	public static <K extends Comparable<K>,A, V extends AttrValue<A>> AttrTreap<K,V> insertNode(AttrTreap<K,V> root, AttrTreap<K,V> node) {
		if (root == null) {
			return node;
		} else {
			int cmp = root.key.compareTo(node.key);
			if (node.priority > root.priority) {
				// insert at this level
				splitTree(root, node.key, node);
				return node;
			} else {
				if (cmp > 0)
					root.left = insertNode(root.left, node);
				else
					root.right = insertNode(root.right, node);
				updateNodeAttr(root);
				return root;
			}
		}
	}
	
	/**
	 * Find node with key k and delete it
	 * @param root - root node
	 * @param k - search criteria
	 * @return new root node
	 */
	public static <K extends Comparable<K>, A, V extends AttrValue<A>> AttrTreap<K,V> deleteKey(AttrTreap<K,V> root, K k) {
		if (root == null) {
			return null;
		} else {
			int cmp = root.key.compareTo(k);
			if (cmp == 0) {
				return mergeNode(root.left, root.right);
			} else if (cmp > 0) {
				root.left = deleteKey(root.left, k);
				updateNodeAttr(root);
				return root;
			} else {
				root.right = deleteKey(root.right, k);
				updateNodeAttr(root);
				return root;
			}
		}
	}

	/**
	 * Find node
	 * @param root - root node
	 * @param k - search criteria
	 * @return any node with matching search criteria 
	 */
	public static <K extends Comparable<K>, A, V extends AttrValue<A>> AttrTreap<K,V> findNode(AttrTreap<K,V> root, K k) {
		if (root == null) {
			return null;
		} else {
			int cmp = root.key.compareTo(k);
			if (cmp == 0) {
				return root;
			} else if (root.key.compareTo(k) > 0) {
				return findNode(root.left, k);
			} else {
				return findNode(root.right, k);
			}
		}
	}

	public AttrTreap(int p, K k, V v) {
		priority = p;
		key = k;
		value = v;		
	}
	public AttrTreap(K k, V v) {
		this((int)(Math.random()*Integer.MAX_VALUE), k, v);
	}
}
