package dk.struct.test;

import static org.junit.Assert.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import org.junit.Test;
import dk.struct.*;

public class AttrTreapTest {

	/**
	 * mutable integer attribute where we will keep total children count
	 * @author kokarev
	 *
	 */
	static class IntBox {
		public int intValue;
		public IntBox(int n) {
			intValue = n;
		}
		public String toString() {
			return Integer.toString(intValue);
		}
	}
	
	/**
	 * our value is simply a string with attribute containing number of chld nodes
	 * @author kokarev
	 */
	static class Val implements AttrValue<IntBox> {
		String val;
		IntBox num;
		
		@Override
		public IntBox getAttr() {
			return num;
		}

		/**
		 * this hook will be invoked when tree needs to update chld nodes
		 * we simply update number of children
		 */
		@Override
		public void updateAttr(AttrValue<IntBox> l, AttrValue<IntBox> r) {
			int n = 1;
			if (l != null)
				n += l.getAttr().intValue;
			if (r != null)
				n += r.getAttr().intValue;
			num.intValue = n;
		}
		
		public Val(String v) {
			val = v;
			num = new IntBox(1);
		}
		
		public String toString() {
			StringBuffer sb = new StringBuffer("[");
			sb.append(val);
			sb.append(":");
			sb.append(num);
			sb.append("]");
			return sb.toString();
		}
	};
	
	protected BufferedReader getResourceBufferedReader(String resource) {
		return new BufferedReader(new InputStreamReader(getClass().getResourceAsStream(resource)));
	}
	
	protected BufferedReader getResource1() {
		return getResourceBufferedReader("/dk/struct/test/AttrTreapTest1.data");
	}
	
	@Test
	public void createAndCount() {
		try (BufferedReader reader = getResource1()) {
			String line;
			AttrTreap<Integer, Val> root = null;
			int i=0;
			while ((line = reader.readLine()) != null) {
				AttrTreap<Integer, Val> node = new AttrTreap<>(i++, new Val(line));
				root = AttrTreap.insertNode(root, node);
			}
			//System.out.println(root.treeToString());
			assertEquals("root node must have correct count of members", i, root.value.getAttr().intValue);
		} catch(IOException ex) {
			fail(ex.toString());
		}
	}

	@Test
	public void findAll() {
		try (BufferedReader reader = getResource1()) {
			String line;
			AttrTreap<Integer, Val> root = null;
			int i=0;
			while ((line = reader.readLine()) != null) {
				AttrTreap<Integer, Val> node = new AttrTreap<>(i++, new Val(line));
				root = AttrTreap.insertNode(root, node);
			}
			//System.out.println(root.treeToString());
			for (i--; i>=0; i--) {
				AttrTreap<Integer, Val> node = AttrTreap.findNode(root, Integer.valueOf(i));
				assertNotNull("must find", node);
			}
		} catch(IOException ex) {
			fail(ex.toString());
		}
	}
	@Test
	public void deleteAndNotFind() {
		try (BufferedReader reader = getResource1()) {
			String line;
			AttrTreap<Integer, Val> root = null;
			int i=0;
			while ((line = reader.readLine()) != null) {
				AttrTreap<Integer, Val> node = new AttrTreap<>(i++, new Val(line));
				root = AttrTreap.insertNode(root, node);
			}
			//System.out.println("Original Tree:");
			//System.out.println(root.treeToString());
			for (i--; i>0; i--) {
				AttrTreap<Integer, Val> node = AttrTreap.findNode(root, Integer.valueOf(i));
				assertNotNull("must find before deletion", node);
				root = AttrTreap.deleteKey(root, Integer.valueOf(i));
				assertNotNull("tree must stay populated until last node gets deleted", root);
				assertEquals("total count must reduce", i, root.value.getAttr().intValue);
				node = AttrTreap.findNode(root, Integer.valueOf(i));
				assertNull("must not find after deletion", node);
			}
			root = AttrTreap.deleteKey(root, Integer.valueOf(i));
			assertNull("root must be null after we delete everything", root);
		} catch(IOException ex) {
			fail(ex.toString());
		}
	}
	@Test
	public void deleteInRandomOrder() {
		AttrTreap<Integer, Val> root = null;
		final int size = 1<<18;		// 256K
		int i;
		ArrayList<Integer> keysToDel = new ArrayList<>();
		for (i=0; i<size; i++) {
			Integer key = Integer.valueOf(i);
			keysToDel.add(key);
			AttrTreap<Integer, Val> node = new AttrTreap<>(key, new Val(Integer.toString(i)));
			root = AttrTreap.insertNode(root, node);
		}
		Collections.shuffle(keysToDel);
		for (Integer k:keysToDel) {
			assertNotNull("tree must stay populated until last node gets deleted", root);
			assertEquals("root node must have correct count of members", i, root.value.getAttr().intValue);
			root = AttrTreap.deleteKey(root, k);
			AttrTreap<Integer, Val> node = AttrTreap.findNode(root, k);
			assertNull("must not find after deletion", node);
			i--;
		}
		root = AttrTreap.deleteKey(root, Integer.valueOf(i));
		assertNull("root must be null after we delete everything", root);
	}

	// building a perfectly symmetrical tree with [from, to-1] values using nodes level for balancing
	AttrTreap<Integer, Val> addSymmetric(AttrTreap<Integer, Val> root, int from, int to, int level) {
		if (to>from) {
			int mid = (from+to)/2;
			Integer key = Integer.valueOf(mid);
			AttrTreap<Integer, Val> node = new AttrTreap<>(level, key, new Val(Integer.toString(mid)));
			root = addSymmetric(root, from, mid, level-1);
			root = AttrTreap.insertNode(root, node);
			root = addSymmetric(root, mid+1, to, level-1);
		}
		return root;
	}
	@Test
	public void addManySymmetric() {
		AttrTreap<Integer, Val> root = null;
		final int size = (1<<20)-1;
		root = addSymmetric(root, 0, size, 1000);
		//System.out.println("Original Tree:");
		//System.out.println(root.treeToString());
		assertEquals("root node must have correct count of members", root.value.getAttr().intValue, size);
	}
	@Test
	public void addAndDeleteSymmetric() {
		AttrTreap<Integer, Val> root = null;
		final int size = (1<<20)-1;
		root = addSymmetric(root, 0, size, 1000);
		assertEquals("root node must have correct count of members", root.value.getAttr().intValue, size);
		int i;
		for (i=0; i<size-1; i++)
			root = AttrTreap.deleteKey(root, Integer.valueOf(i));
		assertEquals("only one node must remain", 1, root.value.getAttr().intValue);
		root = AttrTreap.deleteKey(root, Integer.valueOf(i));
		assertNull("root must be null after we delete everything", root);
	}
}
