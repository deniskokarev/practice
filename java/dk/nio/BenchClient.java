package dk.nio;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;
import java.util.concurrent.atomic.AtomicLong;

public class BenchClient implements Runnable {
	final static int PORT = 1111;
	final int SZ = 1024*1024;
	byte buffer[];
	Socket socket;
	OutputStream os;
	AtomicLong totalSz;
	BenchClient(String host) throws UnknownHostException, IOException {
		buffer = new byte[SZ];
		Random random = new Random();
		for (int i=0; i<SZ; i++)
			buffer[i] = (byte)random.nextInt(256);
		socket = new Socket(host, 1111);
		os = socket.getOutputStream();
		totalSz = new AtomicLong();
	}
	public long getTotal() {
		return totalSz.get();
	}
	public void run() {
		try {
			while (true) {
				os.write(buffer);
				totalSz.getAndAdd(SZ);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
	public static void main(String[] args) {
		int nth = 1;
		String host = "localhost";
		try {
			if (args.length > 0)
				nth = Integer.parseInt(args[0]);
			if (nth <= 0)
				throw new Exception("number of threads must be positive");
			if (args.length > 1)
				host = args[1];
			BenchClient bc[] = new BenchClient[nth];
			Thread clth[] = new Thread[nth];
			for (int i=0; i<nth; i++) {
				bc[i] = new BenchClient(host);
				clth[i] = new Thread(bc[i]);
				clth[i].start();
			}
			final int FREQ_SEC = 10;
			long lastTotal = 0;
			while (true) {
				Thread.sleep(FREQ_SEC * 1000);
				long total = 0;
				for (int i=0; i<nth; i++)
					total += bc[i].getTotal();
				System.out.format("%d MB/sec%n", (total-lastTotal)/1024/1024/FREQ_SEC);
				lastTotal = total;
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
