package dk.struct;

/**
 * A value that has an aggregate attribute, such as an Integer value and sum of total values underneath
 * @author kokarev
 *
 * @param <T> - attribute type
 */
public interface AttrValue<T> {
	/**
	 * @return node attribute
	 */
	public T getAttr();
	/**
	 * To be executed when either left or right node attr changes
	 * @param l - left node or null
	 * @param r - right node or null
	 */
	public void updateAttr(AttrValue<T> l, AttrValue<T> r);
}
