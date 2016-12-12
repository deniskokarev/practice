import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/*
 * http://codeforces.com/problemset/problem/427/B
The prison of your city has n prisoners. As the prison can't accommodate all of them, the city mayor has decided to transfer c of the prisoners to a prison located in another city.

For this reason, he made the n prisoners to stand in a line, with a number written on their chests. The number is the severity of the crime he/she has committed. The greater the number, the more severe his/her crime was.

Then, the mayor told you to choose the c prisoners, who will be transferred to the other prison. He also imposed two conditions. They are,

The chosen c prisoners has to form a contiguous segment of prisoners.
Any of the chosen prisoner's crime level should not be greater then t. Because, that will make the prisoner a severe criminal and the mayor doesn't want to take the risk of his running away during the transfer.
Find the number of ways you can choose the c prisoners.

Input
The first line of input will contain three space separated integers n (1 ≤ n ≤ 2·105), t (0 ≤ t ≤ 109) and c (1 ≤ c ≤ n). The next line will contain n space separated integers, the ith integer is the severity ith prisoner's crime. The value of crime severities will be non-negative and will not exceed 109.

Output
Print a single integer — the number of ways you can choose the c prisoners.

Examples
input
4 3 3
2 3 1 1
output
2
input
1 1 1
2
output
0
input
11 4 2
2 2 0 7 3 2 2 4 9 1 4
output
6

 */
public class CF427B {

	static void proc(Scanner sc) {
		long n = sc.nextLong();
		long t = sc.nextLong();
		long c = sc.nextLong();
		List<Integer> l = new LinkedList<>();
		for (int i=0; i<n; i++)
			l.add(sc.nextInt());
		long res = 0;
		long cnt = 0;
		for (Integer i:l) {
			if (i>t) {
				if (cnt >= c)
					res += cnt-c+1;
				cnt = 0;
			} else {
				cnt++;
			}
		}
		if (cnt >= c)
			res += cnt-c+1;
		System.out.println(res);
	}
	
	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			proc(sc);
		}
	}

}
