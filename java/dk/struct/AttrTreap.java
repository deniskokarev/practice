package dk.struct;

/**
 * BinaryTree/Heap hybrid with Attrubute-aware values. I.e. each value has an attrubute, which aggregates
 * attributes of left and right nodes below. If the attribute was simply the number of elements then
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
	protected AttrTreap<K,V> left, right;
	
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
			l.value.updateAttr((l.left!=null)?l.left.value:null, l.right.value);
			return l;
		} else {
			r.left = mergeNode(l, r.left);
			r.value.updateAttr(r.left.value, (r.right!=null)?r.right.value:null);
			return r;
		}
	}

	/**
	 * Split root node into two subtrees - lr.left and lr.right depending on the key
	 * @param root - what we're splitting 
	 * @param splitKey - split criteria, i.e. what stays to the left and what stays to the right of key 
	 * @param lr - recipient node for for the split
	 */
	static <K extends Comparable<K>, A, V extends AttrValue<A>> void splitNode(AttrTreap<K,V> root, K splitKey, AttrTreap<K,V> lr) {
		if (root == null) {
			return;
		} else {
			int cmp = root.key.compareTo(splitKey);
			AttrTreap<K,V> llrr = new AttrTreap<K,V>(0, null, null);
			if (cmp < 0) {
				splitNode(root.right, splitKey, llrr);
				root.right = llrr.left;
				lr.left = root;
				lr.right = llrr.right;
			} else {
				splitNode(root.left, splitKey, llrr);
				root.left = llrr.right;
				lr.right = root;
				lr.left = llrr.left;
			}
			if (lr.left != null)
				lr.left.value.updateAttr((lr.left.left!=null)?lr.left.left.value:null, (lr.left.right!=null)?lr.left.right.value:null);
			if (lr.right != null)
				lr.right.value.updateAttr((lr.right.left!=null)?lr.right.left.value:null, (lr.right.right!=null)?lr.right.right.value:null);
		}
	}

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
				splitNode(root, node.key, node);
				node.value.updateAttr((node.left!=null)?node.left.value:null, (node.right!=null)?node.right.value:null);
				return node;
			} else {
				if (cmp > 0) {
					root.left = insertNode(root.left, node);
				} else {
					root.right = insertNode(root.right, node);
				}
				root.value.updateAttr((root.left!=null)?root.left.value:null, (root.right!=null)?root.right.value:null);
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
				root.value.updateAttr((root.left!=null)?root.left.value:null, (root.right!=null)?root.right.value:null);
				return root;
			} else {
				root.right = deleteKey(root.right, k);
				root.value.updateAttr((root.left!=null)?root.left.value:null, (root.right!=null)?root.right.value:null);
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
