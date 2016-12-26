import java.io.PrintStream;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

public class CF747C {
	/**
	 * solution result
	 */
	public static class Answer {
		List<Integer> a;
		public Answer(List<Integer> a) {
			this.a = a;
		}

		@Override
		public String toString() {
			StringBuffer sb = new StringBuffer();
			for (int n:a) {
				sb.append(n);
				sb.append('\n');
			}
			return sb.toString();
		}
	};

	
	static class Task implements Comparable<Task> {
		int timeIn;
		int serversLoad;
		int timeWork;
		int timeEnd;
		long busySum;
		int servers[];
		Task(int ti, int sl, int tw) {
			timeIn = ti;
			serversLoad = sl;
			timeWork = tw;
			timeEnd = timeIn+timeWork;
			busySum = 0;
			servers = null;
		}
		@Override
		public int compareTo(Task o) {
			return timeEnd - o.timeEnd;
		}
	}
	
	/**
	 * input parser
	 */
	public static class Input {
		int nservers;
		int ntasks;
		Task task[];
		public Input(Scanner sc) {
			nservers = sc.nextInt();
			ntasks = sc.nextInt();
			task = new Task[ntasks];
			for (int i=0; i<ntasks; i++)
				task[i] = new Task(sc.nextInt(), sc.nextInt(), sc.nextInt());
		}
	};

	/**
	 * solver function
	 */
	public static Answer solve(Input in) {
		List<Integer> res = new LinkedList<>();
		PriorityQueue<Task> pt = new PriorityQueue<>();
		int timeNow;
		Task task[] = in.task;
		int nBusy = 0;
		boolean busy[] = new boolean[in.nservers];
		for (int i=0; i<task.length; i++) {
			timeNow = task[i].timeIn;
			while (!pt.isEmpty() && pt.peek().timeEnd <= timeNow) {
				Task head = pt.remove();
				nBusy -= head.serversLoad;
				for (int j=0; j<head.servers.length; j++)
					busy[head.servers[j]] = false;
			}
			if (in.nservers-nBusy >= task[i].serversLoad) {
				pt.add(task[i]);
				nBusy += task[i].serversLoad;
				int s[] = new int[task[i].serversLoad];
				int ns = 0;
				int cnt = 0;
				for (int j=0; j<busy.length && ns<s.length; j++) {
					if (!busy[j]) {
						s[ns++] = j;
						busy[j] = true;
						cnt += j+1;
					}
				}
				task[i].servers = s;
				res.add(cnt);
			} else {
				res.add(-1);
			}
		}
		Answer ans = new Answer(res);
		return ans;
	}

	/**
	 * standard CodeForces executable mantra
	 */
	public static void proc(Scanner sc, PrintStream out) {
		Input in = new Input(sc);
		out.println(solve(in));
	}

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc, System.out);
		}
	}
}
