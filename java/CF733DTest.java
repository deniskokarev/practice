import static org.junit.Assert.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

import org.junit.Test;

public class CF733DTest {

	static class IOPipe implements AutoCloseable {
		public Scanner sc;
		ByteArrayOutputStream baos;
		public PrintStream out;
		public IOPipe(String istr) {
			sc = new Scanner(istr);
			baos = new ByteArrayOutputStream();
			out = new PrintStream(baos);
		}
		@Override
		public String toString() {
			return baos.toString();
		}
		@Override
		public void close() {
			try {
				sc.close();
				out.close();
				baos.close();
			} catch(Throwable ignore) {
			}
		}
	}
	
	@Test
	public void test1() {
		String in = "6\n"+
				"5 5 5\n"+
				"3 2 4\n"+
				"1 4 1\n"+
				"2 1 3\n"+
				"3 2 4\n"+
				"3 3 4\n";
		String expectedOut = "1\n1\n";
		try (IOPipe pipe = new IOPipe(in)) {
			CF733D.proc(pipe.sc, pipe.out);
			assertEquals(expectedOut, pipe.toString());
		}
	}
	@Test
	public void test2() {
		String in = "7\n"+
				"10 7 8\n"+
				"5 10 3\n"+
				"4 2 6\n"+
				"5 5 5\n"+
				"10 2 8\n"+
				"4 2 1\n"+
				"7 7 7\n";
		String expectedOut = "2\n5 1\n";
		try (IOPipe pipe = new IOPipe(in)) {
			CF733D.proc(pipe.sc, pipe.out);
			assertEquals(expectedOut, pipe.toString());
		}
	}

}
