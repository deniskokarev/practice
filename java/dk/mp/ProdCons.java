package dk.mp;

import java.util.LinkedList;
import java.util.Queue;

/**
 * producer/consumer simple example M->M via a single queue
 * @author kokarev
 *
 */
public class ProdCons {
	static class Item {
		final static Item END = new Item(-1);
		int n;
		public Item(int n) {
			this.n = n;
		}
		boolean isEnd() {
			return n < 0;
		}
	}
	static class Q<T> {
		Queue<T> queue;
		volatile int nProducers;
		volatile int nConsumers;
		public Q(Queue<T> q, int np, int nc) {
			queue = q;
			nProducers = np;
			nConsumers = nc;
		}
	}
	static class Producer implements Runnable {
		int from, to;
		Q<Item> queue;
		long sum;
		int maxQ;
		int nWait;
		public Producer(Q<Item> q, int f, int t, int m) {
			from = f;
			to = t;
			queue = q;
			sum = 0;
			maxQ = m;
			nWait = 0;
		}
		public void run() {
			int i = from;
			while (i < to) {
				synchronized(queue) {
					if (queue.queue.size() < maxQ) {
						queue.queue.add(new Item(i));
						sum += i;
						i++;
						queue.notifyAll();
					} else {
						try {
							nWait++;
							queue.wait();
						} catch (InterruptedException ignore) {}
					}
				}
			}
			synchronized(queue) {
				queue.nProducers--;
				queue.notifyAll();
			}
		}
	}
	static class Consumer implements Runnable {
		Q<Item> queue;
		long sum;
		int nWait;
		public Consumer(Q<Item> q) {
			queue = q;
			sum = 0;
			nWait = 0;
		}
		public void run() {
			while (true) {
				synchronized (queue) {
					if (queue.queue.isEmpty()) {
						if (queue.nProducers > 0) {
							try {
								nWait++;
								queue.wait();
							} catch (InterruptedException ignore) {}
						} else {
							break;
						}
					} else {
						sum += queue.queue.remove().n;
						queue.notifyAll();
					}
				}
			}
		}
	}
	public static void main(String argv[]) {
		Queue<Item> nestedQ = new LinkedList<>();
		Q<Item> q = new Q<>(nestedQ, 7, 7);
		int maxQ = 1000;
		int batch = 10000000;
		Producer producer[] = new Producer[] {
				new Producer(q, 0*batch+1, 1*batch, maxQ),
				new Producer(q, 1*batch+1, 2*batch, maxQ),
				new Producer(q, 2*batch+1, 3*batch, maxQ),
				new Producer(q, 3*batch+1, 4*batch, maxQ),
				new Producer(q, 4*batch+1, 5*batch, maxQ),
				new Producer(q, 5*batch+1, 6*batch, maxQ),
				new Producer(q, 6*batch+1, 7*batch, maxQ),
		};
		Thread producerThread[] = new Thread[] {
				new Thread(producer[0]),
				new Thread(producer[1]),
				new Thread(producer[2]),
				new Thread(producer[3]),
				new Thread(producer[4]),
				new Thread(producer[5]),
				new Thread(producer[6])
		};
		Consumer consumer[] = new Consumer[] {
				new Consumer(q),
				new Consumer(q),
				new Consumer(q),
				new Consumer(q),
				new Consumer(q),
				new Consumer(q),
				new Consumer(q)
		};
		Thread consumerThread[] = new Thread[] {
				new Thread(consumer[0]),
				new Thread(consumer[1]),
				new Thread(consumer[2]),
				new Thread(consumer[3]),
				new Thread(consumer[4]),
				new Thread(consumer[5]),
				new Thread(consumer[6])
		};
		for (Thread c:consumerThread)
			c.start();
		for (Thread p:producerThread)
			p.start();
		try {
			for (Thread c:consumerThread)
				c.join();
			for (Thread p:producerThread)
				p.join();
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}
		long psum = 0;
		long pwait = 0;
		for (Producer p:producer) {
			System.out.println("psum:"+p.sum);
			psum += p.sum;
			pwait += p.nWait;
		}
		System.out.println("pwait:"+pwait);
		long csum = 0;
		long cwait = 0;
		for (Consumer c:consumer) {
			System.out.println("csum:"+c.sum);
			csum += c.sum;
			cwait += c.nWait;
		}
		System.out.println("cwait:"+cwait);
		if (psum == csum) {
			System.out.println("OK");
		} else {
			System.out.println("ERROR");
			System.err.println("ERROR");
		}
	}
}
