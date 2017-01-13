package dk.mp;

import java.io.Closeable;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;


class Worker<T> extends Thread implements Work {
	T batch;
	int job;
	Workers<T> mgr;

	void setBatch(T b) {
		batch = b;
	}
	
	@Override
	public synchronized void startWork() {
		assert(batch != null);
		job++;
		notify();
	}
	
	synchronized void shutdown() {
		this.batch = null;
		job++;
		notify();
	}
	
	@Override
	public synchronized void run() {
		try {
			while (true) {
				while (job < 1)
					wait();
				if (batch == null)
					break;
				mgr.performWork(batch);
				job--;
				notify();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public synchronized void waitWork() {
		try {
			while (job > 1)
				wait();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public Worker(Workers<T> mgr) {
		this.mgr = mgr;
	}
	
	@Override
	public void close() {
		waitWork();
		mgr.free(this);
	}
}

/**
 * Thread pool manager - requires performWork() implementation to do actual computation
 * T - batch job type
 * 
 * Each Job is a persistent thread with life cycle:
 * createWork(batch) -> startWork() -> waitWork() -> close()
 * 
 * TODO: limit max number of concurrent works
 * 
 * @author kokarev
 *
 * @param <T>
 */
public abstract class Workers<T> implements Closeable {
	Set<Worker<T>> running;
	List<Worker<T>> ready;
	
	protected abstract void performWork(T batch);
	
	public Workers() {
		running = new HashSet<>();
		ready = new LinkedList<>();
	}
	
	public synchronized Work createWork(T batch) {
		Worker<T> w;
		if (ready.size() < 1) {
			w = new Worker<>(this);
			w.setBatch(batch);
			w.start();
		} else {
			w = ready.remove(0);
			w.setBatch(batch);
		}
		running.add(w);
		return w;
	}

	synchronized void free(Worker<T> w) {
		running.remove(w);
		ready.add(w);
	}
	
	@Override
	public synchronized void close() {
		for (Worker<T> w:running)
			w.waitWork();
		for (Worker<T> w:ready)
			w.shutdown();
		try {
			for (Worker<T> w:ready)
				w.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
