/* https://www.hackerrank.com/challenges/java-dequeue */
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Scanner;
import java.lang.Math;

public class HrJavaDequeue {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			int n = sc.nextInt();
			int k = sc.nextInt();
			HashMap<Integer,Integer> mm = new HashMap<Integer,Integer>();
			Deque<Integer> qq = new ArrayDeque<Integer>();
			for (int i=0; i<k; i++) {
				int v = sc.nextInt();
				qq.add(v);
				mm.put(v, mm.getOrDefault(v, 0)+1);			
			}
			int mx = mm.size();
			for (int i=k; i<n; i++) {
				int v = sc.nextInt();
				qq.add(v);
				mm.put(v, mm.getOrDefault(v, 0)+1);
				int lst = qq.poll();
				int nv = mm.get(lst);
				if (nv == 1)
					mm.remove(lst);
				else
					mm.put(lst,  nv-1);
				mx = Math.max(mx, mm.size());
			}
			System.out.println(mx);
		}
	}
}
