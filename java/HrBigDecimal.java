/* https://www.hackerrank.com/challenges/java-bigdecimal */
import java.math.BigDecimal;
import java.util.*;

class HrBigDecimal {

    public static void main(String []args){
        //Input
        Scanner sc= new Scanner(System.in);
        int n=sc.nextInt();
        String []s=new String[n+2];
        for(int i=0;i<n;i++){
            s[i]=sc.next();
        }
      	sc.close();

        //Write your code here
      	class Pair implements Comparable<Pair> {
      		public BigDecimal d;
      		public String s;
      		public Pair(String s) {
      			this.d = new BigDecimal(s);
      			this.s = s;
      		}
			@Override
			public int compareTo(Pair o) {
				return o.d.compareTo(d);
			}
      	};
      	Pair srt[] = new Pair[n];
        for (int i=0; i<n; i++)
        	srt[i] = new Pair(s[i]);
        Arrays.sort(srt);
        for (int i=0; i<n; i++)
        	s[i] = srt[i].s;
      	
        //Output
        for(int i=0;i<n;i++)
        {
            System.out.println(s[i]);
        }
    }

}