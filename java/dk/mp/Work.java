package dk.mp;

import java.io.Closeable;

public interface Work extends Closeable {
	void startWork();
	public void waitWork();
}
