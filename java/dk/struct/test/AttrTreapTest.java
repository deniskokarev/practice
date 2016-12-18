package dk.struct.test;

import static org.junit.Assert.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.junit.Test;
import dk.struct.*;
public class AttrTreapTest {

	/**
	 * our attribute is simply a number of nodes
	 * @author kokarev
	 */
	static class Val implements AttrValue<Integer> {
		static final Integer one = Integer.valueOf(1);
		String val;
		Integer num;
		
		@Override
		public Integer getAttr() {
			return num;
		}

		@Override
		public void updateAttr(AttrValue<Integer> l, AttrValue<Integer> r) {
			int n = 1;
			if (l != null)
				n += l.getAttr();
			if (r != null)
				n += r.getAttr();
			num = new Integer(n);
		}
		
		public Val(String v) {
			val = v;
			num = one;
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
	public void testCreateAndCount() {
		try (BufferedReader reader = getResource1()) {
			String line;
			AttrTreap<Integer, Val> root = null;
			int i=0;
			while ((line = reader.readLine()) != null) {
				AttrTreap<Integer, Val> node = new AttrTreap<>(i++, new Val(line));
				root = AttrTreap.insertNode(root, node);
			}
			//System.out.println(root.treeToString());
			assertEquals("root node must have correct count of members", root.value.getAttr(), Integer.valueOf(i));
		} catch(IOException ex) {
			fail(ex.toString());
		}
	}

	@Test
	public void testFindAll() {
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
	public void testDeleteAndNotFind() {
		try (BufferedReader reader = getResource1()) {
			String line;
			AttrTreap<Integer, Val> root = null;
			int i=0;
			while ((line = reader.readLine()) != null) {
				AttrTreap<Integer, Val> node = new AttrTreap<>(i++, new Val(line));
				root = AttrTreap.insertNode(root, node);
			}
			//System.out.println(root.treeToString());
			for (i--; i>0; i--) {
				AttrTreap<Integer, Val> node = AttrTreap.findNode(root, Integer.valueOf(i));
				assertNotNull("must find before deletion", node);
				root = AttrTreap.deleteKey(root, Integer.valueOf(i));
				assertEquals("total count must reduce", root.value.getAttr(), Integer.valueOf(i));
				node = AttrTreap.findNode(root, Integer.valueOf(i));
				assertNull("must not find after deletion", node);
			}
			root = AttrTreap.deleteKey(root, Integer.valueOf(i));
			assertNull("root must be null after we delete everything", root);
		} catch(IOException ex) {
			fail(ex.toString());
		}
	}
}
