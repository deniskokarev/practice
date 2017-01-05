import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/*
 * 
Input

10

13 2 5 55 21 34 1 8 1 3

Output

3

Answer

6

Checker Log

wrong answer expected '6', found '3'


 */

public class CF545D {

	static <T extends Number> int place(int w, List<T> lst) {
		class Result {
			public int nHappy;
			public int leftTotal;
			public T n;
			public Result(T n) {
				this.n = n;
			}
		}
		Result res = lst.stream()
				.sorted()
				.map((el) -> new Result(el))
				.reduce(new Result(null), (s,el) -> {
					if (s.leftTotal <= el.n.intValue()) {
						s.nHappy++;
						s.leftTotal += el.n.intValue();
					}
					return s;
				});
		return res.nHappy;
	}

	static void solve(Scanner sc) {
		// read input
		int n = sc.nextInt();
		List<Integer> a = new LinkedList<>();
		for (int i=0; i<n; i++)
			a.add(new Integer(sc.nextInt()));
		// solve & output
		int nHappy = place(0, a);
		System.out.println(nHappy);
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			solve(sc);
		}
	}
}
