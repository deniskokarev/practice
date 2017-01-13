package dk.mp.test;

import dk.mp.*;
import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.Test;

class Batch {
	String in;
	String out;
	int cnt;
	int sum;
	Batch(String s) {
		in = s;
	}
}

class MyWorkers extends Workers<Batch> {
	@Override
	protected void performWork(Batch b) {
		b.out = b.in+":"+b.in;
		b.cnt++;
		b.sum += b.cnt;
	}
}

public class WorkersTest {

	@Test
	public void testOne() {
		Batch bb[] = new Batch[1];
		for (int i=0; i<bb.length; i++)
			bb[i] = new Batch("batch"+i);
		try (MyWorkers ws = new MyWorkers()) {
			for (int i=0; i<bb.length; i++)
				ws.createWork(bb[i]).startWork();
		}
		for (int i=0; i<bb.length; i++)
			assertEquals("batch output must match", bb[i].out, "batch"+i+":batch"+i);
	}
	
	@Test
	public void testMany() {
		final int PARALLEL = 177;
		Batch bb[] = new Batch[PARALLEL];
		for (int i=0; i<bb.length; i++)
			bb[i] = new Batch("batch"+i);
		try (MyWorkers ws = new MyWorkers()) {
			for (int i=0; i<bb.length; i++)
				ws.createWork(bb[i]).startWork();
		}
		for (int i=0; i<bb.length; i++)
			assertEquals("batch output must match", bb[i].out, "batch"+i+":batch"+i);
	}
	
	@Test
	public void testManyMany() throws IOException {
		final int LOOP = 17777;
		final int PARALLEL = 17;
		Batch bb[] = new Batch[PARALLEL];
		Work ww[] = new Work[bb.length];
		for (int i=0; i<bb.length; i++)
			bb[i] = new Batch("batch"+i);
		try (MyWorkers ws = new MyWorkers()) {
			for (int j=0; j<LOOP; j++) {
				for (int i=0; i<bb.length; i++) {
					ww[i] = ws.createWork(bb[i]);
					ww[i].startWork();
				}
				for (int i=0; i<bb.length; i++) {
					ww[i].waitWork();
					ww[i].close();
				}
			}
		}
		for (int i=0; i<bb.length; i++)
			assertEquals("batch output must match", bb[i].sum, LOOP*(LOOP+1)/2);
	}
}
