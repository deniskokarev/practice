package dk.nio;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.ArrayDeque;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicLong;

class ReaderWorker implements Runnable {
	class ChanStat {
		long vol;
		ChanStat() {
			vol = 0;
		}
		void inc(int sz) {
			vol += sz;
		}
		long get() {
			return vol;
		}
	};
	Selector readSelector;
	HashMap<SocketChannel,ChanStat> chan;
	ByteBuffer buffer;
	Queue<SocketChannel> newSockets;
	AtomicLong totalSz;
	ReaderWorker() throws IOException {
		readSelector = Selector.open(); // selector is open here
		chan = new HashMap<SocketChannel,ChanStat>();
		buffer = ByteBuffer.allocate(1024*1024);
		newSockets = new ArrayDeque<SocketChannel>();
		totalSz = new AtomicLong();
	}
	public long getTotal() {
		return totalSz.get();
	}
	public void close() throws IOException {
		readSelector.close();
		for (SocketChannel c:chan.keySet())
			c.close();
	}
	@Override
	public void run() {
		try {
			while (readSelector.isOpen()) {
				while (newSockets.size()>0) {
					SocketChannel client = newSockets.element();
					client.register(readSelector, SelectionKey.OP_READ);
					newSockets.remove();
				}
				readSelector.select(100);
				if (readSelector.isOpen()) {
					Iterator<SelectionKey> iter = readSelector.selectedKeys().iterator();
					while (iter.hasNext()) {
						SelectionKey key = iter.next();
		                if (key.isReadable()) {
		                	SocketChannel client = (SocketChannel)key.channel();
		                	buffer.clear();
		                	int sz = client.read(buffer);
		                	if (sz == -1) {
		                		System.err.format("closed channel with volume %d MB%n", chan.get(client).get()/1024/1024);
		                		chan.remove(client);
		                		client.close();
		                	} else {
		                		chan.get(client).inc(sz);
		                		totalSz.getAndAdd(sz);
		                	}
		                }
		                iter.remove();
					}
				}
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
        System.err.println("Done reader thread");
	}
	
	public void addChan(SocketChannel client) throws IOException {
    	client.configureBlocking(false);
    	chan.put(client, new ChanStat());
    	newSockets.add(client);
    	readSelector.wakeup();
	}
};

public class BenchServer implements Runnable {
	final static int PORT = 1111;
	class Stats {
		long lastStatTS;
		long lastTotal;
		Stats() {
			lastStatTS = (new Date()).getTime();
			lastTotal = 0;
		}
	}
	int nth;
	boolean shutdown = false;
	Selector acceptSelector;
	ServerSocketChannel socket;
	BenchServer(int nth) throws IOException {
		this.nth = nth;
		acceptSelector = Selector.open(); // selector is open here
		socket = ServerSocketChannel.open();
		InetSocketAddress addr = new InetSocketAddress("localhost", PORT);
		socket.bind(addr);
		socket.configureBlocking(false);
		socket.register(acceptSelector, SelectionKey.OP_ACCEPT);
	}
    public void run() {
        try {
            System.err.println("Shutting down ...");
            acceptSelector.close();
    		socket.close();
            shutdown = true;
        } catch (IOException e) {
            Thread.currentThread().interrupt();
			e.printStackTrace();
		}
    }
    private void update_stats(Stats stat, ReaderWorker rworker[]) {
    	final int FREQ_SEC = 10;
		long now = (new Date()).getTime();
		if (stat.lastStatTS + FREQ_SEC * 1000 < now) {
			long total = 0;
			for (int i=0; i<nth; i++)
				total += rworker[i].getTotal();
			System.out.format("%d MB/sec%n", (total-stat.lastTotal)/1024/1024/FREQ_SEC);
			stat.lastStatTS = now;
			stat.lastTotal = total;
		}
    }
	private void do_server() throws IOException {
		Stats stat = new Stats();
		ReaderWorker rworker[] = new ReaderWorker[nth];
		Thread rthread[] = new Thread[nth];
		for (int i=0; i<nth; i++) {
			rworker[i] = new ReaderWorker();
			rthread[i] = new Thread(rworker[i]);
			rthread[i].start();
		}
		int idx = 0;
		while (!shutdown) {
			// Selects a set of keys whose corresponding channels are ready for I/O operations
			acceptSelector.select(1000);
			if (acceptSelector.isOpen()) {
				Iterator<SelectionKey> iter = acceptSelector.selectedKeys().iterator();
				while (iter.hasNext()) {
					SelectionKey key = iter.next();
	                if (key.isAcceptable()) {
	                	SocketChannel client = ((ServerSocketChannel)key.channel()).accept();
	                	rworker[idx].addChan(client);
	                	idx++;
	                	idx %= nth;
	                }
	                iter.remove();
				}
			} else {
				break;
			}
			update_stats(stat, rworker);
		}
		for (int i=0; i<nth; i++) {
			rworker[i].close();
			try {
				rthread[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
        System.err.println("Finished shutdown ...");
	}
	public static void main(String[] args) {
		try {
			int nth = 1;
			if (args.length > 0)
				nth = Integer.parseInt(args[0]);
			if (nth <= 0)
				throw new Exception("number of threads must be positive");
			BenchServer server = new BenchServer(nth);
			Runtime.getRuntime().addShutdownHook(new Thread(server));
			server.do_server();
		} catch(Exception ex) {
			ex.printStackTrace();
		}
	}
}

/**
public class BenchServer {
	private static void log(String str) {
		System.out.println(str);
	}
	private static void do_server() throws IOException {
		Selector acceptSelector = Selector.open(); // selector is open here
		Selector readSelector = Selector.open(); // selector is open here

		// ServerSocketChannel: selectable channel for stream-oriented listening sockets
		ServerSocketChannel socket = ServerSocketChannel.open();
		InetSocketAddress addr = new InetSocketAddress("localhost", 1111);
 
		// Binds the channel's socket to a local address and configures the socket to listen for connections
		socket.bind(addr);
 
		// Adjusts this channel's blocking mode.
		socket.configureBlocking(false);
 
		socket.register(acceptSelector, SelectionKey.OP_ACCEPT);
		ByteBuffer buffer = ByteBuffer.allocate(1024*1024);
		HashMap<SocketChannel,MutableInt> chanVolume = new HashMap<SocketChannel,MutableInt>();
		while (true) {
			// Selects a set of keys whose corresponding channels are ready for I/O operations
			selector.select();
			Iterator<SelectionKey> iter = selector.selectedKeys().iterator();
			while (iter.hasNext()) {
				SelectionKey key = iter.next();
                if (key.isAcceptable()) {
                	SocketChannel client = ((ServerSocketChannel)key.channel()).accept();
                	client.configureBlocking(false);
                	client.register(selector, SelectionKey.OP_READ);
                	chanVolume.put(client, new MutableInt());
                }
                if (key.isReadable()) {
                	SocketChannel client = (SocketChannel)key.channel();
                	buffer.clear();
                	int sz = client.read(buffer);
                	if (sz == -1) {
                		System.err.format("closed channel with volume %d%n", chanVolume.get(client).get());
                		chanVolume.remove(client);
                		client.close();
                	} else {
                		chanVolume.get(client).inc(sz);
                	}
                }
                iter.remove();
			}
		}
		
	}
	public static void main(String[] args) {
		try {
			do_server();
		} catch(IOException ex) {
			ex.printStackTrace();
		}
	}
}
*/