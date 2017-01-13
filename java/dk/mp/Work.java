package dk.mp;

import java.io.Closeable;

/**
 * Offline batch job abstract to be used on thread pool
 * @author kokarev
 *
 */
public interface Work extends Closeable {
	void startWork();
	public void waitWork();
}
